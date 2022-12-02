
#ifndef _PSP2_KERNEL_FIXEDHEAP_H_
#define _PSP2_KERNEL_FIXEDHEAP_H_

#include <vita/shared/types.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceKernelFixedHeapInfo { // size is 0x90-bytes
	SceSize size;
	SceSize objectSize;
	SceSize totalHeapSize;
	SceUInt32 totalItemCount;

	SceUInt32 totalFreeCount;
	SceUInt32 nUsedMax;
	SceUInt32 unk_0x18;
	SceUInt16 nItemInPage;
	SceUInt16 nMaxItemInPage;

	SceUInt32 nListCount;
	struct {
		SceUInt16 unk_0x00;
		SceUInt16 nCount;
		SceUInt32 unk_0x04;
		SceUInt32 unk_0x08;
		SceUInt32 unk_0x0C;
	} cpuCache[4];
	SceUInt32 unk_0x64;
	SceUInt32 unk_0x68;
	SceUInt32 unk_0x6C;
	SceUInt32 unk_0x70;
	SceUInt16 nItem;
	SceUInt16 unk_0x76;
	SceUInt32 unk_0x78;
	SceUInt32 nPage;
	SceUInt32 unk_0x80;
	SceUInt32 unk_0x84;
	SceUInt32 unk_0x88;
	SceUInt32 unk_0x8C;
} SceKernelFixedHeapInfo;


/*
          sceKernelFixedHeapSetHook: 0x8C8E2DD1
          sceKernelGetFixedHeapInfo: 0x4FA4A624
          sceKernelGetFixedHeapInfoByPointer: 0x219E90FD
*/


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_FIXEDHEAP_H_ */
