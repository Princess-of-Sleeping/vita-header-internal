
#ifndef _PSP2_KERNEL_THREAD_DELAY_H_
#define _PSP2_KERNEL_THREAD_DELAY_H_

#include <vita/shared/types.h>


#ifdef __cplusplus
extern "C" {
#endif


int sceKernelDelayThread(SceUInt32 nsec);
int sceKernelDelayThreadCB(SceUInt32 nsec);
int sceKernelDelayThreadUnk(SceUInt32 nsec, SceUInt32 *a2);
int sceKernelDelayThreadUnkCB(SceUInt32 nsec, SceUInt32 *a2);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_THREAD_DELAY_H_ */
