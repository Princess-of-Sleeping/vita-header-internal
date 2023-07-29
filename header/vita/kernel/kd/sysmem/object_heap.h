
#ifndef _PSP2_KERNEL_OBJECT_HEAP_H_
#define _PSP2_KERNEL_OBJECT_HEAP_H_

#include <shared/types.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceKernelObjectHeap { // size is 0xC4-bytes
	int unk_0x00;
	void *pPhyMemPart;
	SceUInt32 nFixedHeap;
	void *unk_0x0C;
	SceFixedHeapHook *pHeapHook;
	void *pKernelHeapObject;
	void *pL2PageTableHeap;
	struct {
		SceInt32 unk_0x1C;
		SceInt32 unk_0x20;
		SceInt32 unk_0x24;
		SceInt32 unk_0x28;
		SceInt32 unk_0x2C;
		SceInt32 unk_0x30;
		SceInt32 unk_0x34;
	} List[6];
} SceKernelObjectHeap;


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_OBJECT_HEAP_H_ */
