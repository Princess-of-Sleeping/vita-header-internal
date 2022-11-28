
#ifndef _PSP2_KERNEL_THREAD_WORKQUEUE_H_
#define _PSP2_KERNEL_THREAD_WORKQUEUE_H_

#include <psp2kern/types.h>


#define SCE_KERNEL_WORKQUEUE_HAS_THREAD_NUMBER     (1 << 0)
#define SCE_KERNEL_WORKQUEUE_HAS_PRIORITY          (1 << 1)
#define SCE_KERNEL_WORKQUEUE_HAS_STACK_SIZE        (1 << 2)
#define SCE_KERNEL_WORKQUEUE_HAS_CPU_AFFINITY_MASK (1 << 3)

typedef struct SceKernelCreateWorkQueueParam {
	SceSize size;
	SceUInt32 nThread;
	SceUInt32 initPriority;
	SceSize stackSize;
	SceUInt32 cpuAffinityMask;
} SceKernelCreateWorkQueueParam;

SceUID sceKernelCreateWorkQueue(const char *name, SceUInt32 flags, const SceKernelCreateWorkQueueParam *opt);
SceUID sceKernelScheduleWorkTask(SceUID wqueue_id, const char *name, const void *wtask_func, void *argp);


#endif /* _PSP2_KERNEL_THREAD_WORKQUEUE_H_ */
