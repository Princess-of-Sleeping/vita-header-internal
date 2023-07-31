
#ifndef _PSP2_KERNEL_SYSMEM_PHYMEMLOW_H_
#define _PSP2_KERNEL_SYSMEM_PHYMEMLOW_H_

#include <psp2kern/types.h>
#include "uid_class.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceKernelPhyMemLowMap { // size is 0x20-bytes
	int unk_0x00;
	SceUIntPtr pbase;
	SceSize psize;
	int unk_0x0C;
	SceUInt32 nBlockShift;
	SceUInt32 uAlignmentMask;
	SceUInt32 unk_0x18;
	int unk_0x1C;
} SceKernelPhyMemLowMap;


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_SYSMEM_PHYMEMLOW_H_ */
