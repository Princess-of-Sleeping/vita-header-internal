
#ifndef _PSP2_KERNEL_AS_H_
#define _PSP2_KERNEL_AS_H_

#include <vita/shared/types.h>
#include <vita/kernel/kd/sysmem/uid_class.h>
#include <vita/kernel/kd/sysmem/partition.h>

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

typedef struct SceUIDPhyMemPartObject { // size is 0xAC-bytes
	void *pUserdata;
	SceClass *pClass;
	int data_0x08; // for cpu function
	int data_0x0C;

	SceUID data_0x10;
	int data_0x14;
	int data_0x18;
	void *data_0x1C;

	void *data_0x20;
	int data_0x24;
	int data_0x28;
	void *data_0x2C;

	void *data_0x30;

	struct {
		int id;
		void *data;
	} vector_0x34[9];

	void *data_0x7C; // size is 0x30-bytes

	int data_0x80;
	SceSize free_size;
	SceSize free_size_internal;
	char name[0x20];
} SceUIDPhyMemPartObject;

typedef struct SceKernelProcessTTBR { // size is 0x14-bytes
	SceUInt32 unk_0x00;
	SceUIntPtr *pTTBR0;
	SceUIntPtr *pTTBR1;
	SceSize ttbr0_mgmt_size;
	SceSize ttbr1_mgmt_size;
} SceKernelProcessTTBR;

typedef struct SceKernelPTV { // size is 0x40-bytes
	SceUInt32 unk_0x00;
	SceInt32  unk_0x04;
	SceUInt32 unk_0x08;
	SceUInt32 unk_0x0C; // some flags
	SceUInt32 unk_0x10; // maybe some number
	SceUInt32 targetPA;
	SceUInt32 *pSecondLevelDescription;
	SceUInt32 unk_0x1C;
	SceUInt32 secondLevelDescriptionPA;
	SceUInt32 unk_0x24;
	void *unk_0x28;
	SceUInt32 unk_0x2C;
	SceInt32  unk_0x30;
	SceInt32  unk_0x34;
	SceInt32  unk_0x38;
	SceUInt32 magic;
} SceKernelPTV;

typedef struct SceKernelPTVVector { // size is 0x4000-bytes
	SceUInt32 vector[0x1000];
} SceKernelPTVVector;

typedef struct SceKernelAddressSpaceMMUContext { // size is 0x28-bytes
	SceKernelProcessContext cpu_ctx;
	SceKernelProcessTTBR *pProcessTTBR;
	SceKernelPTVVector *unk_0x10;
	int unk_0x14;
	int unk_0x18;
	int unk_0x1C;
	int unk_0x20;
	int unk_0x24;
} SceKernelAddressSpaceMMUContext;

typedef struct SceUIDAddressSpaceObject { // size is 0x170-bytes
	void *pUserdata;
	SceClass *pClass;
	int unk_0x08;		// for cpu function
	int unk_0x0C;
	int flag;		// kernel:0x30000002, user:0x10000001
	SceUID pid;
	SceKernelAddressSpaceMMUContext *unk_0x18;
	SceUIDPartitionObject *pPart[0x20];
	SceUID unk_uid[0x20];	// pPart object guid
	int unk_0x11C;
	int unk_0x120[3];
	SceUIDPhyMemPartObject *unk_0x12C;
	SceUIDPhyMemPartObject *unk_0x130;
	SceUIDPhyMemPartObject *unk_0x134;
	SceUIDPhyMemPartObject *unk_0x138;

	SceUIDPhyMemPartObject *unk_0x13C;
	SceUIDPhyMemPartObject *unk_0x140;
	SceUIDPhyMemPartObject *unk_0x144;
	SceUIDPhyMemPartObject *unk_0x148;

	SceUIDPhyMemPartObject *unk_0x14C;
	SceUIDPhyMemPartObject *unk_0x150;
	SceUIDPhyMemPartObject *unk_0x154;
	SceUIDPhyMemPartObject *unk_0x158;
	SceUID unk_0x15C; // for user process? it guid
	SceUID unk_0x160; // for user process? it guid
	int unk_0x164;
	uint32_t unk_0x168;	// kernel:0x511389B0
	SceUInt32 magic;		// 0x4D95AEEC
} SceUIDAddressSpaceObject;


typedef struct SceKernelAddressSpaceInfo { // size is 0x654-bytes
	SceSize size;
	SceUID asid;
	SceUInt32 context_id;
	SceUInt32 nInfo;
	SceKernelPartitionInfo part[0x20];
	char data_0x610[0x44];
} SceKernelAddressSpaceInfo;


int SceSysmemForKernel_46A5CB84(SceUID pid, int a2, int a3, void *info); // get part info by addr
int SceSysmemForKernel_4492421F(SceUID asid, SceKernelAddressSpaceInfo *info);
SceUIDPartitionObject *SceSysmemForKernel_210DB518(void *pAS, int pindex);

SceUIDAddressSpaceObject *sceKernelGetKernelAddressSpace(void);

/*
          sceKernelCreateAddressSpace: 0x4A3737F0
          sceKernelDeleteAddressSpace: 0xF2D7FE3A
          sceKernelAddressSpaceChangeMMUContext: 0x653B0849
          sceKernelAddressSpaceCtrSetObjectHeap: 0xFC74A355
          sceKernelAddressSpaceFreeAllMemBlock: 0x89CE1F31
          sceKernelAddressSpaceGetMMUContext: 0x9894B9E1
          sceKernelAddressSpaceGetMemoryType: 0xCC7BB240
          sceKernelAddressSpaceGetTimerVbase: 0x7D92B2D3
          sceKernelAddressSpaceRefer: 0x3F74E45C
          sceKernelAddressSpaceSetName: 0x7BD56D6D
          sceKernelAddressSpaceSetPhyMemPart: 0x67955EE9
          sceKernelAddressSpaceSetProcess: 0x2476B90F
          sceKernelAddressSpaceUnmap: 0xCE72839E
          sceKernelAddressSpaceVARangeToPAVector: 0xF7250E6C
          sceKernelAddressSpaceVAtoPA: 0xF2179820
*/

#endif /* _PSP2_KERNEL_AS_H_ */
