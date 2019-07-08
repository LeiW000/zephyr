/*
 * Copyright (c) 2018 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STM32WBX_PINMUX_H_
#define _STM32WBX_PINMUX_H_

/**
 * @file Header for STM32WBX pin multiplexing helper
 */

/* Port A */
#define STM32WBX_PINMUX_FUNC_PA2_LPUART1_TX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)
#define STM32WBX_PINMUX_FUNC_PA3_LPUART1_RX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA9_USART1_TX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32WBX_PINMUX_FUNC_PA10_USART1_RX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUPDR_NO_PULL)
#define STM32WBX_PINMUX_FUNC_PA12_LPUART1_RX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

/* SPI1 */
#define STM32WBX_PINMUX_FUNC_PA1_SPI1_SCK \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA4_SPI1_NSS \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA5_SPI1_SCK \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA6_SPI1_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA7_SPI1_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA11_SPI1_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA12_SPI1_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA15_SPI1_NSS \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

 /* SPI2 */
#define STM32WBX_PINMUX_FUNC_PA9_SPI2_SCK \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

/* Port B */
#define STM32WBX_PINMUX_FUNC_PB5_LPUART1_TX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)
#define STM32WBX_PINMUX_FUNC_PB6_USART1_TX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32WBX_PINMUX_FUNC_PB7_USART1_RX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUPDR_NO_PULL)
#define STM32WBX_PINMUX_FUNC_PB8_I2C1_SCL  \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32WBX_PINMUX_FUNC_PB9_I2C1_SDA  \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32WBX_PINMUX_FUNC_PB10_LPUART1_RX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB11_LPUART1_TX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

/* SPI1 */
#define STM32WBX_PINMUX_FUNC_PB2_SPI1_NSS  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB3_SPI1_SCK  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB4_SPI1_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB5_SPI1_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

 /* SPI2 */
#define STM32WBX_PINMUX_FUNC_PB9_SPI2_NSS   \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB10_SPI2_SCK  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB12_SPI2_NSS  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB13_SPI2_SCK  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB14_SPI2_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB15_SPI2_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

/* Port C */
#define STM32WBX_PINMUX_FUNC_PC0_LPUART1_RX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PC1_LPUART1_TX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)
#define STM32WBX_PINMUX_FUNC_PC0_I2C3_SCL  \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32WBX_PINMUX_FUNC_PC1_I2C3_SDA  \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

/* SPI2 */
#define STM32WBX_PINMUX_FUNC_PC1_SPI2_MOSI \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PC2_SPI2_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PC3_SPI2_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

/* Port D */
/* SPI2 */
#define STM32WBX_PINMUX_FUNC_PD0_SPI2_NSS \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PD1_SPI2_SCK \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PD3_SPI2_SCK \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PD3_SPI2_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PD4_SPI2_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

/* Port E */

/* Port H */

#endif /* _STM32WBX_PINMUX_H_ */
