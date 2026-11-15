//
//  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
//  Copyright (c) 2019, RUIKAI LIU and MR TUNNEL. All rights reserved.
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at
//  http://opensource.org/licenses/bsd-license.php
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//
//

#include <AsmMacroLib.h>
#include <Library/PcdLib.h>
.syntax unified
.arch armv7-a
.text
.align 3

#define LoadConstantToReg(Data, Reg) \
    ldr Reg, =Data


GCC_ASM_IMPORT (ArmDeInitialize)
GCC_ASM_IMPORT (CEntryPoint)
GCC_ASM_EXPORT (_ModuleEntryPoint)
GCC_ASM_IMPORT (ArmEnableInstructionCache)

.global _StackBase
.global _StackSize

_StackBase:
  .long FixedPcdGet32(PcdPrePiStackBase)

_StackSize:
  .long FixedPcdGet32(PcdPrePiStackSize)

_ModuleEntryPoint:
  /* Clear r0 for function calls below */
  mov r0, #0

  /* Clean & invalidate U-Boot's dirty caches, disable MMU/caches/interrupts, flush TLB */
  bl ASM_PFX(ArmDeInitialize)

_SetupExceptionVector:
  LoadConstantToReg (0x402C0000, r0)
  ldr r1, dead
  mov r2, #0

_FillVectors:
  str     r1, [r0, r2]
  adds    r2, r2, #4      /* Fill every 4 bytes (all 8 ARMv7 exception vectors) */
  cmp     r2, #0x40       /* Vector Table Size */
  bne     _FillVectors

  mcr     p15, 0, r0, c12, c0, 0  /* Write VBAR so CPU uses this vector table */
  isb

_SetupPrimaryCoreStack:
  ldr r0, _StackBase      /* Stack base arg0 */
  ldr r1, _StackSize      /* Stack size arg1 */

  add r4, r0, r1
  bic r4, r4, #7          /* Enforce 8-byte boundary alignment */
  mov sp, r4


_EnableCache:
  /* Only enable I-Cache here; MemoryPeim() will enable MMU + D-Cache together */
  bl ASM_PFX(ArmEnableInstructionCache)

_PrepareArguments:
  /* r0 = _StackBase and r1 = _StackSize */
  ldr   r0, _StackBase    /* Stack base arg0 */
  ldr   r1, _StackSize    /* Stack size arg1 */

  // Jump to PrePiCore C code
  ldr   r4, =ASM_PFX(CEntryPoint)
  blx   r4

_NeverReturn:
  b _NeverReturn

.align 3
dead:
  b dead
