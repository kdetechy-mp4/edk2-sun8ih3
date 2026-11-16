#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#include <Library/ClockLib.h>
#include <Library/NonDiscoverableDeviceRegistrationLib.h>

#include <Protocol/Gpio.h>

#include <Guid/EventGroup.h>

#include "UsbHost.h"

// Ports 1, 2, 3 are the 3 Type-A USB host ports on OrangePi PC Plus
STATIC CONST UINT32  mUsbPorts[] = { 1, 2 };

STATIC EFI_HANDLE  mEhciHandles[ARRAY_SIZE (mUsbPorts)];
STATIC UINTN       mEhciHandleCount = 0;

//
// Init USB port clock
//
STATIC
VOID
UsbPortClockInit (
    IN UINT32  Port
)
{
    CONST USB_PORT_CLOCKS  *C;

    ASSERT (Port < ARRAY_SIZE (mUsbClocks));
    C = &mUsbClocks[Port];

    CcmClkEnable  (C->PhyClk);
    CcmClkDisable (C->OhciClk);

    CcmResetAssert (C->OhciRst);
    CcmClkDisable  (C->OhciBus);
    CcmClkEnable   (C->EhciBus);
    MicroSecondDelay (10);

    CcmResetDeassert (C->PhyRst);

    CcmResetAssert (C->EhciRst);
    MicroSecondDelay (10);
    CcmResetDeassert (C->EhciRst);
    MicroSecondDelay (50);
}

/**
 * Take one port's PHY out of powerdown and route it to the HCI.
 **/
STATIC
VOID
UsbPortPhyInit (
    IN UINT32  Port
)
{
    UINTN   Pmu = USB_PMU_BASE (Port);
    UINT32  Val;

    // Clear H3 SIDDQ (BIT1) to power up the PHY
    Val  = MmioRead32 (Pmu + USB_HCI_PHY_CTL_OFFSET);
    Val &= ~(UINT32)PHY_CTL_H3_SIDDQ;
    MmioWrite32 (Pmu + USB_HCI_PHY_CTL_OFFSET, Val);

    // Enable AHB burst & passby
    Val  = MmioRead32 (Pmu + USB_PMU_CTRL_OFFSET);
    Val |= PMU_AHB_ICHR8_EN | PMU_AHB_INCR4_BURST_EN |
    PMU_AHB_INCRX_ALIGN_EN | PMU_ULPI_BYPASS_EN;
    MmioWrite32 (Pmu + USB_PMU_CTRL_OFFSET, Val);
}

EFI_STATUS
EFIAPI
UsbHostDxeEntry (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
)
{
    EFI_STATUS     Status;
    UINTN          Index;
    UINT32         Port;
    GPIO_PROTOCOL  *Gpio;

    // Optional: If GpioProtocol is available, enable Port 0 VBUS (PL2)
    Status = gBS->LocateProtocol (&gGpioProtocolGuid, NULL, (VOID **)&Gpio);
    if (!EFI_ERROR (Status)) {
        Gpio->ConfigurePin (SUNXI_GPL (2), SUNXI_GPIO_OUTPUT);
        Gpio->SetPinState (SUNXI_GPL (2), 1);
        DEBUG ((DEBUG_INFO, "UsbHostDxe: Port 0 VBUS (PL2) enabled\n"));
    }

    for (Index = 0; Index < ARRAY_SIZE (mUsbPorts); Index++)
    {
        Port = mUsbPorts[Index];

        UsbPortClockInit (Port);
        UsbPortPhyInit (Port);

        // Standard EDK2 NonDiscoverableDevice signature:
        // Type, DmaType, DmaTranslation, Handle, Count, BaseAddress, Length
        Status = RegisterNonDiscoverableMmioDevice (
            NonDiscoverableDeviceTypeEhci,
            NonDiscoverableDeviceDmaTypeNonCoherent,
            NULL,
            &mEhciHandles[mEhciHandleCount],
            1,
            (EFI_PHYSICAL_ADDRESS)mUsbEhciBase[Port],
                                                    (UINTN)0x100
        );
        if (EFI_ERROR (Status)) {
            DEBUG ((DEBUG_ERROR, "EHCI%u register failed: %r\n", Port, Status));
            continue;
        }

        DEBUG ((DEBUG_WARN, "EHCI%u @ 0x%lx registered\n", Port, (UINT64)mUsbEhciBase[Port]));
        mEhciHandleCount++;
    }

    return EFI_SUCCESS;
}
