
#ifndef _PSP2_KERNEL_UID_ENTRY_HEAP_H_
#define _PSP2_KERNEL_UID_ENTRY_HEAP_H_

#include <shared/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceUIDEntryHeapObject { // size is 0xB0-bytes
	SceUIDFixedHeapObject fixedheap;
	int data_0xA4;
	int data_0xA8;
	int data_0xAC;
} SceUIDEntryHeapObject;

/*
          sceUIDCreateEntryHeap: 0x19CAEF35
          sceUIDDeleteEntryHeap: 0xF0C3FCFC
          sceUIDEntryHeapCloseAllPUID: 0xFAF96C1F
          sceUIDEntryHeapGetInfo: 0x686AA15C
          sceUIDEntryHeapSetHook: 0xCD985AEB
*/


typedef struct SceUIDEntryHeapInfo { // size is 0x18-bytes
	SceSize size;
	SceSize objectSize;
	SceSize totalHeapSize;
	SceUInt32 totalItemCount;
	SceUInt32 unk_0x10;
	SceUInt32 unk_0x14;
} SceUIDEntryHeapInfo;

int sceUIDEntryHeapGetInfo(SceUID entry_id, SceUIDEntryHeapInfo *info);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_UID_ENTRY_HEAP_H_ */
