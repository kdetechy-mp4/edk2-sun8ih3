#ifndef __GPIO_DXE_H__
#define __GPIO_DXE_H__

#include <Protocol/Gpio.h>

// GPIO base addresses
#define H3_PIO_BASE           0x01C20800
#define H3_R_PIO_BASE         0x01F02C00
#define H3_PIO_BANK_SIZE      0x24
#define H3_PIO_DAT_OFF        0x10
#define H3_PIO_PULL_OFF       0x1C

// Helpers to decode banks and pin numbers
#define GPIO_BANK(pin)        ((pin) >> 5)
#define GPIO_NUM(pin)         ((pin) & 0x1F)

// Bank base address resolver (handles Main PIO vs R_PIO Bank L)
#define GPIO_BANK_BASE(bank)  (((bank) == SUNXI_GPIO_L) ? H3_R_PIO_BASE : (H3_PIO_BASE + (bank) * H3_PIO_BANK_SIZE))

// Pin validation check
#define ASSERT_PIN(Pin)       ASSERT ((GPIO_BANK (Pin) <= SUNXI_GPIO_G) || (GPIO_BANK (Pin) == SUNXI_GPIO_L))

// GPIO register addresses and bit positions (exact names matching reference)
#define GPIO_CFG0_BASE(bank)  (GPIO_BANK_BASE(bank))
#define GPIO_CFG1_BASE(bank)  (GPIO_BANK_BASE(bank) + 0x4)
#define GPIO_CFG2_BASE(bank)  (GPIO_BANK_BASE(bank) + 0x8)
#define GPIO_CFG3_BASE(bank)  (GPIO_BANK_BASE(bank) + 0xC)
#define GPIO_CFG_BIT(pin)     ((GPIO_NUM(pin) & 0x7) << 2)

#define GPIO_MDR0_BASE(bank)  (GPIO_BANK_BASE(bank) + 0x14)
#define GPIO_MDR1_BASE(bank)  (GPIO_BANK_BASE(bank) + 0x18)
#define GPIO_MDR_BIT(pin)     ((GPIO_NUM(pin) & 0xF) * 2)

#define GPIO_PULL_BASE(bank)  (GPIO_BANK_BASE(bank) + H3_PIO_PULL_OFF)
#define GPIO_PULL_INDEX(pin)  (GPIO_NUM(pin) >> 4)
#define GPIO_PULL_OFFSET(pin) ((GPIO_NUM(pin) & 0xF) << 1)

#define GPIO_DAT_BASE(bank)   (GPIO_BANK_BASE(bank) + H3_PIO_DAT_OFF)

#endif // __GPIO_DXE_H__
