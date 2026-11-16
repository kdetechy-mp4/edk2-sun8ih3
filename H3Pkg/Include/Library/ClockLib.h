#ifndef __CLOCK_LIB_H__
#define __CLOCK_LIB_H__

#define H3_CCM_BASE             0x01C20000

// PLL registers
#define CCM_PLL_VIDEO0_REG        (H3_CCM_BASE + 0x0010)
#define CCM_PLL_DE_REG            (H3_CCM_BASE + 0x0048)

// Module clock register fields
#define CCM_CLK_ENABLE_BIT        (1 << 31)
#define CCM_CLK_MUX_SHIFT         24
#define CCM_CLK_DIV_N_SHIFT       16
#define CCM_CLK_DIV_M_SHIFT       0
#define CCM_CLK_MUX_MASK          0x3
#define CCM_CLK_DIV_M_MASK        0xF
#define CCM_CLK_DIV_N_MASK        0x3

// PLL control bits
#define CCM_PLL_ENABLE_BIT        (1 << 31)
#define CCM_PLL_LDO_EN_BIT        0
#define CCM_PLL_LOCK_ENABLE_BIT   0
#define CCM_PLL_LOCK_STATUS_BIT   (1 << 28)
#define CCM_PLL_OUT_EN_BIT        0

// Clock IDs
#define CLK_PLL_VIDEO		6
#define CLK_PLL_PERIPH0		9
#define CLK_BUS_MMC0		22
#define CLK_BUS_MMC1		23
#define CLK_BUS_MMC2		24
#define CLK_BUS_NAND		25
#define CLK_BUS_DRAM		26
#define CLK_BUS_EMAC		27
#define CLK_BUS_SPI0		30
#define CLK_BUS_SPI1		31
#define CLK_BUS_OTG		32
#define CLK_BUS_EHCI0		33
#define CLK_BUS_EHCI1		34
#define CLK_BUS_EHCI2		35
#define CLK_BUS_EHCI3		36
#define CLK_BUS_OHCI0		37
#define CLK_BUS_OHCI1		38
#define CLK_BUS_OHCI2		39
#define CLK_BUS_OHCI3		40
#define CLK_BUS_TCON0		42
#define CLK_BUS_TCON1		43
#define CLK_BUS_CSI		45
#define CLK_BUS_HDMI		47
#define CLK_BUS_DE		48
#define CLK_BUS_MSGBOX		50
#define CLK_BUS_SPINLOCK	51
#define CLK_BUS_CODEC		52
#define CLK_BUS_SPDIF		53
#define CLK_BUS_PIO		54
#define CLK_BUS_I2S0		56
#define CLK_BUS_I2S1		57
#define CLK_BUS_I2S2		58
#define CLK_BUS_I2C0		59
#define CLK_BUS_I2C1		60
#define CLK_BUS_I2C2		61
#define CLK_BUS_UART0		62
#define CLK_BUS_UART1		63
#define CLK_BUS_UART2		64
#define CLK_BUS_UART3		65
#define CLK_BUS_SCR0		66
#define CLK_BUS_EPHY		67
#define CLK_NAND		70
#define CLK_MMC0		71
#define CLK_MMC0_SAMPLE		72
#define CLK_MMC0_OUTPUT		73
#define CLK_MMC1		74
#define CLK_MMC1_SAMPLE		75
#define CLK_MMC1_OUTPUT		76
#define CLK_MMC2		77
#define CLK_MMC2_SAMPLE		78
#define CLK_MMC2_OUTPUT		79
#define CLK_SPI0		82
#define CLK_SPI1		83
#define CLK_I2S0		84
#define CLK_I2S1		85
#define CLK_I2S2		86
#define CLK_USB_PHY0		88
#define CLK_USB_PHY1		89
#define CLK_USB_PHY2		90
#define CLK_USB_PHY3		91
#define CLK_USB_OHCI0		92
#define CLK_USB_OHCI1		93
#define CLK_USB_OHCI2		94
#define CLK_USB_OHCI3		95
#define CLK_DRAM		96
#define CLK_DRAM_VE		97
#define CLK_DRAM_CSI		98
#define CLK_DRAM_DEINTERLACE	99
#define CLK_DRAM_TS		100
#define CLK_DE			101
#define CLK_TCON0		102
#define CLK_CSI_MISC		105
#define CLK_CSI_SCLK		106
#define CLK_CSI_MCLK		107
#define CLK_AC_DIG		109
#define CLK_HDMI		111
#define CLK_HDMI_DDC		112
#define CLK_MBUS		113
#define CLK_BUS_SCR1		115
 
// Reset IDs
#define RST_USB_PHY0		0
#define RST_USB_PHY1		1
#define RST_USB_PHY2		2
#define RST_USB_PHY3		3
#define RST_BUS_MMC0		7
#define RST_BUS_MMC1		8
#define RST_BUS_MMC2		9
#define RST_BUS_NAND		10
#define RST_BUS_EMAC		12
#define RST_BUS_SPI0		15
#define RST_BUS_SPI1		16
#define RST_BUS_OTG		17
#define RST_BUS_EHCI0		18
#define RST_BUS_EHCI1		19
#define RST_BUS_EHCI2		20
#define RST_BUS_EHCI3		21
#define RST_BUS_OHCI0		22
#define RST_BUS_OHCI1		23
#define RST_BUS_OHCI2		24
#define RST_BUS_OHCI3		25
#define RST_BUS_TCON0		27
#define RST_BUS_TCON1		28
#define RST_BUS_CSI		30
#define RST_BUS_TVE		31
#define RST_BUS_HDMI0		32
#define RST_BUS_HDMI1		33
#define RST_BUS_DE		34
#define RST_BUS_MSGBOX		36
#define RST_BUS_SPINLOCK	37
#define RST_BUS_EPHY		39
#define RST_BUS_CODEC		40
#define RST_BUS_I2S0		43
#define RST_BUS_I2S1		44
#define RST_BUS_I2S2		45
#define RST_BUS_I2C0		46
#define RST_BUS_I2C1		47
#define RST_BUS_I2C2		48
#define RST_BUS_UART0		49
#define RST_BUS_UART1		50
#define RST_BUS_UART2		51
#define RST_BUS_UART3		52
#define RST_BUS_SCR0		53
/* New resets imported in H5 */
#define RST_BUS_SCR1		54

VOID CcmClkEnable  (IN UINT32 ClkId);
VOID CcmClkDisable (IN UINT32 ClkId);
VOID CcmClkConfigure (IN UINT32 ClkId, IN UINT32 Mux, IN UINT32 DivM, IN UINT32 DivN);
VOID CcmResetAssert   (IN UINT32 RstId);
VOID CcmResetDeassert (IN UINT32 RstId);
VOID CcmResetPulse    (IN UINT32 RstId);
VOID CcmBusEnable (IN UINT32 ClkId, IN UINT32 RstId);
VOID CcmBusUngate (IN UINT32 ClkId, IN UINT32 RstId);
BOOLEAN CcmPllEnableAndLock (IN UINTN Reg);

#endif // __CLOCK_LIB_H__
