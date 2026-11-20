#include <Protocol/Gpio.h>

#ifndef _USB_HOST_H_
#define _USB_HOST_H_

#define USB_PMU_BASE(n)          (mUsbPmuBase[(n)])
#define USB_PMU_CTRL_OFFSET      0x00
#define USB_HCI_PHY_CTL_OFFSET   0x10

// On Allwinner H3, SIDDQ is BIT1 (on H616 it was BIT3)
#define PHY_CTL_H3_SIDDQ         BIT1

// Shared USB PHY control register (sun8i-h3 uses A33 layout)
#define USB_PHY_CTRL_BASE        0x01C19400U
#define REG_PHYCTL_A33           0x10U
#define REG_PHY_OTGCTL           0x20U
#define OTGCTL_ROUTE_MUSB        BIT0
#define PHYCTL_DATA              BIT7
#define PHY_RES45_CAL_EN         0x0CU
#define PHY_RES45_CAL_DATA       BIT0
#define PHY_RES45_CAL_LEN        1
#define PHY_TX_AMPLITUDE_TUNE    0x20U
#define PHY_TX_RATE              BIT4
#define PHY_TX_MAGNITUDE         BIT2
#define PHY_TX_AMPLITUDE_LEN     5
#define PHY_DISCON_TH_SEL        0x2AU
#define H3_DISC_THRESH           3
#define PHY_DISCON_TH_LEN        2

#define PMU_AHB_ICHR8_EN         BIT10
#define PMU_AHB_INCR4_BURST_EN   BIT9
#define PMU_AHB_INCRX_ALIGN_EN   BIT8
#define PMU_ULPI_BYPASS_EN       BIT0

typedef struct {
    UINT32  PhyClk;
    UINT32  PhyRst;
    UINT32  OhciClk;
    UINT32  OhciBus;
    UINT32  EhciBus;
    UINT32  OhciRst;
    UINT32  EhciRst;
} USB_PORT_CLOCKS;

// H3 PMU0..3 base addresses from sun8i-h3.dtsi
STATIC CONST UINTN  mUsbPmuBase[4] = {
    0x01C1A800, 0x01C1B800, 0x01C1C800, 0x01C1D800
};

// H3 EHCI0..3 base addresses from sun8i-h3.dtsi
STATIC CONST UINTN  mUsbEhciBase[4] = {
    0x01C1A000, 0x01C1B000, 0x01C1C000, 0x01C1D000
};

STATIC CONST USB_PORT_CLOCKS  mUsbClocks[4] = {
    { CLK_USB_PHY0, RST_USB_PHY0, CLK_USB_OHCI0, CLK_BUS_OHCI0, CLK_BUS_EHCI0, RST_BUS_OHCI0, RST_BUS_EHCI0 },
    { CLK_USB_PHY1, RST_USB_PHY1, CLK_USB_OHCI1, CLK_BUS_OHCI1, CLK_BUS_EHCI1, RST_BUS_OHCI1, RST_BUS_EHCI1 },
    { CLK_USB_PHY2, RST_USB_PHY2, CLK_USB_OHCI2, CLK_BUS_OHCI2, CLK_BUS_EHCI2, RST_BUS_OHCI2, RST_BUS_EHCI2 },
    { CLK_USB_PHY3, RST_USB_PHY3, CLK_USB_OHCI3, CLK_BUS_OHCI3, CLK_BUS_EHCI3, RST_BUS_OHCI3, RST_BUS_EHCI3 },
};

#endif // _USB_HOST_H_
