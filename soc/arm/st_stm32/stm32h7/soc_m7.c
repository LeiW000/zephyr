/*
 * Copyright (c) 2019 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief System/hardware module for STM32H7 CM7 processor
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <soc.h>
#include <arch/cpu.h>
#include <cortex_m/exc.h>


/**
 * @brief Perform basic hardware initialization at boot.
 *
 * This needs to be run from the very beginning.
 * So the init priority has to be 0 (zero).
 *
 * @return 0
 */
static int stm32h7_init(struct device *arg)
{
	u32_t key;

	ARG_UNUSED(arg);

	key = irq_lock();

	SCB_EnableICache();

	if (!(SCB->CCR & SCB_CCR_DC_Msk)) {
		SCB_EnableDCache();
	}

	/* Install default handler that simply resets the CPU
	 * if configured in the kernel, NOP otherwise
	 */
	NMI_INIT();

	irq_unlock(key);

	/* Update CMSIS SystemCoreClock variable (HCLK) */
	/* At reset, system core clock is set to 64 MHz from HSI */
	SystemCoreClock = 64000000;

	return 0;
}

SYS_INIT(stm32h7_init, PRE_KERNEL_1, 0);

