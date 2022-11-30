
#ifndef _PSP2_KERNEL_SYSMEM_PARTITION_H_
#define _PSP2_KERNEL_SYSMEM_PARTITION_H_

#include <vita/shared/types.h>


typedef struct SceUIDAddressSpaceObject SceUIDAddressSpaceObject;


typedef struct SceKernelPartitionInfo { // size is 0x30-bytes
	SceSize size;
	SceUIDAddressSpaceObject *pPart;
	SceUIntPtr address;
	SceSize length;
	SceUInt32 nBlock;
	SceUInt32 unk_0x14;
	char *name;
	SceUInt32 unk_0x1C; // nBlock2
	SceUInt32 unk_0x20;
	SceUInt32 unk_0x24;
	SceUInt32 unk_0x28;
	SceUInt32 unk_0x2C;
} SceKernelPartitionInfo;

int sceKernelPartitionGetInfo(SceUID part_id, SceKernelPartitionInfo *info);


#endif /* _PSP2_KERNEL_SYSMEM_PARTITION_H_ */
