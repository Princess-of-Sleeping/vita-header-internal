
#ifndef _PSP2_KERNEL_FIXEDHEAP_H_
#define _PSP2_KERNEL_FIXEDHEAP_H_

#include <shared/types.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceFixedHeapHook { // size is 0xC-bytes
	void *argp;
	void *(* funcAlloc)(void *argp, SceSize length);
	void (* funcFree)(void *argp, void *ptr);
} SceFixedHeapHook;

typedef struct SceFixedHeapCache { // size is 0x10-bytes
	SceUInt16 unk_0x00;
	SceUInt16 nCount;
	SceUInt32 unk_0x04;
	void *unk_0x08;
	void *unk_0x0C;
} SceFixedHeapCache;

typedef struct SceUIDFixedHeapObject { // size is 0xA4-bytes
	void *pUserdata;
	void *pClass;
	struct SceKernelObjectHeap *pObjectHeap;
	void *pItem;
	void *pItemEnd;
	int data_0x14;
	SceUInt32 attr;
	SceSize pageSize;
	SceUInt16 itemSize;
	SceUInt16 data_0x22;
	SceUInt16 data_0x24;
	SceUInt16 data_0x26;
	int lock;
	SceUInt32 magic;
	SceUInt32 nPageMax;
	int data_0x34; // nData_0x38
	void **pLineListVector;
	void *data_0x3C;
	void *data_0x40;
	SceUInt16 data_0x44;
	SceUInt16 nItemPerPage;
	SceFixedHeapHook *pHeapHook;
	void *pKernelHeapObject;
	int data_0x50;
	void *pPhyMemPart;
	char *name;
	SceFixedHeapCache cache[4];
	void *data_0x9C;
	SceUInt32 nItemInFifo;
} SceUIDFixedHeapObject;

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
