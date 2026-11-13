/**
 SPDX-License-Identifier: GPL-2.0-only

 Copyright (c) 2021 Artur Kowalski. <arturkow2000@gmail.com>

 Based on:
  - EDKII ARM Generic timer driver
    Copyright (c) 2011-2013 ARM Ltd. All rights reserved.<BR>

  - Linux sun4i clocksource driver
    Copyright (C) 2012 Maxime Ripard <maxime.ripard@free-electrons.com>
    Allwinner Technology Co., Ltd. <www.allwinnertech.com>
    Benn Huang <benn@allwinnertech.com>

**/

#include <Uefi.h>

#include <Library/IoLib.h>
#include <Library/TimerLib.h>

#include "Timer.h"

/*
 * When we disable a timer, we need to wait at least for 2 cycles of
 * the timer source clock. We will use for that the delay timer
 * that is already setup and runs at the same frequency than the other
 * timers, and we never will be disabled.
 */
VOID Sun8iTimerSync(VOID)
{
  // delay 1us (24 ticks)
  MicroSecondDelay(1);
}

VOID Sun8iTimerStop(VOID)
{
  MmioAnd32(
    SUNXI_TIMER_BASE + SUNXI_TIMER_CTL(INTERRUPT_TIMER),
    ~SUNXI_TIMER_CTL_EN
  );
}

UINT32 Sun8iTimerGetCounter(VOID)
{
  return MmioRead32(SUNXI_TIMER_BASE + SUNXI_TIMER_VAL(INTERRUPT_TIMER));
}

VOID Sun8iTimerStart(UINT32 Interval)
{
  MmioWrite32(
    SUNXI_TIMER_BASE + SUNXI_TIMER_INTERVAL(INTERRUPT_TIMER),
    Interval
  );
  MmioWrite32(
    SUNXI_TIMER_BASE + SUNXI_TIMER_CTL(INTERRUPT_TIMER),
    SUNXI_TIMER_CTL_EN
    | SUNXI_TIMER_CTL_RELOAD
    | SUNXI_TIMER_CTL_SRC_OSC24M
    | SUNXI_TIMER_CTL_DIV1
  );
}

BOOLEAN Sun8iTimerGetIsInterruptActive(VOID)
{
  return !!(MmioRead32(SUNXI_TIMER_BASE + SUNXI_TIMER_IRQSTA) & (1 << INTERRUPT_TIMER));
}

VOID Sun8iTimerClearInterruptStatus(VOID)
{
  MmioWrite32(SUNXI_TIMER_BASE + SUNXI_TIMER_IRQSTA, 1 << INTERRUPT_TIMER);
}
