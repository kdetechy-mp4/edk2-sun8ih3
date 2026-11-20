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
STATIC CONST UINT32  mUsbPorts[] = { 0, 1, 2 };

STATIC EFI_HANDLE  mEhciHandles[ARRAY_SIZE (mUsbPorts)];
STATIC UINTN       mEhciHandleCount = 0;

STATIC
VOID
Sun4iUsbPhyWrite (
    IN UINT32  Port,
    IN UINT32  Addr,
    IN UINT32  Data,
    IN UINT32  Len
)
{
    UINTN   PhyCtl  = USB_PHY_CTRL_BASE + REG_PHYCTL_A33;
    UINT32  UsbcBit = (1U << (Port * 2U));
    UINT32  Temp;
    UINT32  i;

    MmioWrite32 (PhyCtl, 0);

    for (i = 0; i < Len; i++) {
        Temp  = MmioRead32 (PhyCtl);
        Temp &= ~(0xFFU << 8);
        Temp |= ((Addr + i) << 8);
        MmioWrite32 (PhyCtl, Temp);

        Temp = MmioRead8 (PhyCtl);
        if (Data & 0x1U) {
            Temp |= PHYCTL_DATA;
        } else {
            Temp &= ~PHYCTL_DATA;
        }
        Temp &= ~UsbcBit;
        MmioWrite8 (PhyCtl, Temp);

        Temp = MmioRead8 (PhyCtl);
        Temp |= UsbcBit;
        MmioWrite8 (PhyCtl, Temp);

        Temp = MmioRead8 (PhyCtl);
        Temp &= ~UsbcBit;
        MmioWrite8 (PhyCtl, Temp);

        Data >>= 1;
    }
}

//
// Init USB port clock (H3 requires both EHCI and OHCI bus clocks/resets)
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

    if (Port == 0) {
        // Put U-Boot's MUSB OTG controller into reset before handing Port 0 to EHCI0
        CcmResetAssert (RST_BUS_OTG);
        CcmClkDisable  (CLK_BUS_OTG);
    }

    CcmClkEnable  (C->PhyClk);
    CcmClkEnable  (C->OhciClk);
    CcmClkEnable  (C->OhciBus);
    CcmClkEnable  (C->EhciBus);
    MicroSecondDelay (10);

    // Pulse PhyRst cleanly so devices active in U-Boot re-link at USB 2.0 High-Speed
    CcmResetAssert   (C->PhyRst);
    MicroSecondDelay (10);
    CcmResetDeassert (C->PhyRst);
    CcmResetDeassert (C->OhciRst);

    CcmResetAssert (C->EhciRst);
    MicroSecondDelay (10);
    CcmResetDeassert (C->EhciRst);
    MicroSecondDelay (50);
}

/**
 * Take one port's PHY out of powerdown, tune it, and route it to the HCI.
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

    if (Port == 0) {
        // Route PHY0 from MUSB OTG to EHCI0/OHCI0 (Host mode)
        Val  = MmioRead32 (USB_PHY_CTRL_BASE + REG_PHY_OTGCTL);
        Val &= ~(UINT32)OTGCTL_ROUTE_MUSB;
        MmioWrite32 (USB_PHY_CTRL_BASE + REG_PHY_OTGCTL, Val);

        Sun4iUsbPhyWrite (Port, PHY_RES45_CAL_EN, PHY_RES45_CAL_DATA, PHY_RES45_CAL_LEN);
    }

    Sun4iUsbPhyWrite (Port, PHY_TX_AMPLITUDE_TUNE, PHY_TX_MAGNITUDE | PHY_TX_RATE, PHY_TX_AMPLITUDE_LEN);
    Sun4iUsbPhyWrite (Port, PHY_DISCON_TH_SEL, H3_DISC_THRESH, PHY_DISCON_TH_LEN);

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

        Status = RegisterNonDiscoverableMmioDevice (
            NonDiscoverableDeviceTypeEhci,
            NonDiscoverableDeviceDmaTypeNonCoherent,
            NULL,
            &mEhciHandles[mEhciHandleCount],
            1,
            (UINTN)mUsbEhciBase[Port],
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
