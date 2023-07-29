
#ifndef _PSP2_KERNEL_SYSMEM_PARTITION_H_
#define _PSP2_KERNEL_SYSMEM_PARTITION_H_

#include <psp2kern/types.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceUIDAddressSpaceObject SceUIDAddressSpaceObject;


typedef struct SceUIDTinyPartitionObject { // size is 0x38-bytes
	void *pUserdata;
	SceClass *pClass;
	const char *name;
	int cpu_intr;
	void *unk_0x10;
	void *base_vaddr;
	SceSize base_size;
	void *unk_0x1C; // proc cpu ctx
	int unk_0x20; // some flag?
	SceSize remain_size;
	int unk_0x28; // -1
	int unk_0x2C;
	int unk_0x30; // -1
	SceUInt32 magic; // 0xD946F262
} SceUIDTinyPartitionObject;

typedef struct SceUIDPartitionObject { // size is 0x80-bytes
	SceUIDTinyPartitionObject tiny;
	int unk_0x38;
	int unk_0x3C;
	int unk_0x40;
	void *unk_0x44;
	int unk_0x48;
	int unk_0x4C; // ex:8
	int unk_0x50;
	SceUIDAddressSpaceObject *unk_0x54;
	int unk_0x58;
	int unk_0x5C;
	int unk_0x60; // some bit mask
	SceUID pid;
	SceUID this_object_guid;
	int unk_0x6C;
	void *unk_0x70;
	int unk_0x74;
	int unk_0x78;
	int unk_0x7C;
} SceUIDPartitionObject;


typedef struct SceKernelPartitionInfo { // size is 0x30-bytes
	SceSize size;
	SceUIDPartitionObject *pPart;
	SceUIntPtr address;
	SceSize length;
	SceUInt32 nBlock;
	SceUInt32 freeSize;
	char *name;
	SceUInt32 unk_0x1C; // nBlock2
	SceUInt32 unk_0x20;
	SceUInt32 unk_0x24;
	SceUInt32 unk_0x28;
	SceUInt32 unk_0x2C;
} SceKernelPartitionInfo;

int sceKernelPartitionGetInfo(SceUID part_id, SceKernelPartitionInfo *info);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_SYSMEM_PARTITION_H_ */
