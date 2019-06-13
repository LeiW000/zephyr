/*
 * Copyright (c) 2017 RnDity Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32F3_H_
#define ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32F3_H_

/**
 * @file Header for STM32F3 pin multiplexing helper
 */

/*
 * Note:
 * The SPIx_SCK pin speed must be set to HIGH ('11') to avoid last data bit
 * corruption which is a known issue of STM32F3 SPI peripheral (see errata
 * sheets).
 */

#define STM32F3_PINMUX_FUNC_PA9_USART1_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PA10_USART1_RX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32F3_PINMUX_FUNC_PC4_USART1_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PC5_USART1_RX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32F3_PINMUX_FUNC_PA2_USART2_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PA3_USART2_RX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#ifdef CONFIG_SOC_STM32F302X8
#define STM32F3_PINMUX_FUNC_PA0_PWM2_CH1    \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#endif

#ifndef CONFIG_SOC_STM32F334X8
#define STM32F3_PINMUX_FUNC_PD5_USART2_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PD6_USART2_RX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#endif

#if CONFIG_SOC_STM32F302X8 || CONFIG_SOC_STM32F303XC
#define STM32F3_PINMUX_FUNC_PA9_I2C2_SCL    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PA10_I2C2_SDA   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PB6_I2C1_SCL    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PB7_I2C1_SDA    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PB10_USART3_TX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PB11_USART3_RX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PC10_USART3_TX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PC11_USART3_RX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PF0_I2C2_SDA    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PF1_I2C2_SCL    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#elif CONFIG_SOC_STM32F334X8
#define STM32F3_PINMUX_FUNC_PB8_USART3_RX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PB9_USART3_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PB10_USART3_TX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PB11_USART3_RX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#elif CONFIG_SOC_STM32F373XC
#define STM32F3_PINMUX_FUNC_PB8_USART3_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PB9_USART3_RX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PB10_USART3_TX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#endif

#define STM32F3_PINMUX_FUNC_PA4_SPI1_NSS    \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PA5_SPI1_SCK    \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)
#define STM32F3_PINMUX_FUNC_PA6_SPI1_MISO   \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PA7_SPI1_MOSI   \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PA8_PWM1_CH1    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL)

#if CONFIG_SOC_STM32F302X8
#define STM32F3_PINMUX_FUNC_PA11_USB_DM	    \
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PA12_USB_DP     \
	STM32_MODER_ANALOG_MODE
#else
#define STM32F3_PINMUX_FUNC_PA11_USB_DM	    \
	(STM32_PINMUX_ALT_FUNC_14 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PA12_USB_DP     \
	(STM32_PINMUX_ALT_FUNC_14 | STM32_PUSHPULL_NOPULL)
#endif

#define STM32F3_PINMUX_FUNC_PB8_I2C1_SCL    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PB9_I2C1_SDA    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32F3_PINMUX_FUNC_PB12_SPI2_NSS   \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PB13_SPI2_SCK   \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)
#define STM32F3_PINMUX_FUNC_PB14_SPI2_MISO  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PB15_SPI2_MOSI  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

#if CONFIG_SOC_STM32F302X8 || CONFIG_SOC_STM32F303XC || CONFIG_SOC_STM32F373XC
#define STM32F3_PINMUX_FUNC_PA15_SPI3_NSS   \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PB3_SPI3_SCK    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)
#define STM32F3_PINMUX_FUNC_PB4_SPI3_MISO   \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PB5_SPI3_MOSI   \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL)
#endif

#define STM32F3_PINMUX_FUNC_PF2_ADC12_IN10	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PF4_ADC1_IN5	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PC0_ADC12_IN6	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PC1_ADC12_IN7	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PC2_ADC12_IN8	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PC3_ADC12_IN9	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PA0_ADC1_IN1	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PA1_ADC1_IN2	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PA2_ADC1_IN3	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PA3_ADC1_IN4	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PA4_ADC2_IN1	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PA5_ADC2_IN2	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PA6_ADC2_IN3	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PA7_ADC2_IN4	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PC4_ADC2_IN5	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PC5_ADC2_IN11	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PB0_ADC3_IN12	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PB1_ADC3_IN1	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PB2_ADC2_IN12	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PE7_ADC3_IN13	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PE8_ADC34_IN6	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PE9_ADC3_IN2	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PE10_ADC3_IN14	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PE11_ADC3_IN15	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PE12_ADC3_IN16	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PE13_ADC3_IN3	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PE14_ADC4_IN1	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PE15_ADC4_IN12	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PB11_ADC12_IN14	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PB12_ADC4_IN3	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PB13_ADC3_IN5	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PB14_ADC4_IN4	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PB15_ADC4_IN5	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PD8_ADC4_IN12	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PD9_ADC4_IN13	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PD10_ADC34_IN7	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PD11_ADC12_IN8	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PD12_ADC34_IN9	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PD13_ADC34_IN10	\
	STM32_MODER_ANALOG_MODE
#define STM32F3_PINMUX_FUNC_PD14_ADC34_IN11	\
	STM32_MODER_ANALOG_MODE

#endif /* ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32F3_H_ */
