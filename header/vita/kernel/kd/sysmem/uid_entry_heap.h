
#ifndef _PSP2_KERNEL_UID_ENTRY_HEAP_H_
#define _PSP2_KERNEL_UID_ENTRY_HEAP_H_

#include <vita/shared/types.h>


typedef struct SceUIDEntryHeapInfo { // size is 0x18-bytes
	SceSize size;
	SceSize objectSize;
	SceSize totalHeapSize;
	SceUInt32 totalItemCount;
	SceUInt32 unk_0x10;
	SceUInt32 unk_0x14;
} SceUIDEntryHeapInfo;

int sceUIDEntryHeapGetInfo(SceUID entry_id, SceUIDEntryHeapInfo *info);


#endif /* _PSP2_KERNEL_UID_ENTRY_HEAP_H_ */
