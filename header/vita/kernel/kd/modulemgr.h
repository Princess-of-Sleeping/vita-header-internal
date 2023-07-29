
#ifndef _PSP2_KERNEL_MODULEMGR_H_
#define _PSP2_KERNEL_MODULEMGR_H_

#include <psp2kern/types.h>
#include "threadmgr_types.h"


#ifdef __cplusplus
extern "C" {
#endif


#define SCE_KERNEL_START_SUCCESS (0)


typedef struct SceLoadProcessParam { // size is 0x7C-bytes
	SceUInt32 sysver;
	char thread_name[0x20];
	SceUInt32 initial_thread_priority; // ex: 0x100000EC
	SceSize initial_thread_stack_size; // ex: 0x6000
	SceUInt32 unk_0x2C;
	SceUInt32 unk_0x30;
	_SceKernelThreadOptParam threadOptParam;
	int unk_0x50;
	char process_name[0x20]; // not titleid
	SceUInt32 preload_disabled;
	void *module_proc_param;
} SceLoadProcessParam;


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_MODULEMGR_H_ */
