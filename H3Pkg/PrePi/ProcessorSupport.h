#pragma once
#ifndef _ARM_PROC_SUPPORT_H_
#define _ARM_PROC_SUPPORT_H_

#define CACHE_LINE 64

extern void ArmDeInitialize(void);
extern void ArmCleanInvalidateCacheRange(EFI_PHYSICAL_ADDRESS start, UINTN len);

#endif
