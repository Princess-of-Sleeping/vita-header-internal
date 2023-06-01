
#ifndef _PSP2_KERNEL_AS_H_
#define _PSP2_KERNEL_AS_H_

#include <shared/types.h>
#include <kernel/kd/sysmem/uid_class.h>
#include <kernel/kd/sysmem/partition.h>
#include <kernel/kd/sysmem/phymempart.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceUIDAddressSpaceObject SceUIDAddressSpaceObject;


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
	SceUIntPtr TTBR1;
	SceUInt32 DACR;
	SceUInt32 CONTEXTIDR;
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

typedef struct _SceKernelAddressSpaceInfo { // size is 0x654-bytes
	SceSize size;
	SceUID asid;
	SceUInt32 context_id;
	SceUInt32 nInfo;
	SceKernelPartitionInfo part[0x20];
	char data_0x610[0x44];
} _SceKernelAddressSpaceInfo;

typedef struct SceKernelAddressSpaceInfo { // size is 0x654-bytes
	SceSize size;
	SceUID asid;
	SceUInt8 CONTEXTID;
	SceUInt8 paddinf[3];
	SceUInt32 nList;
	struct {
		SceSize size;
		SceUIDPartitionObject *pPart;
		SceUIntPtr vbase;
		SceSize vsize;
		SceUInt32 unk_0x10; // nBlock?
		SceSize vsizeRemain;
		const char *name;
		SceUInt32 unk_0x1C;
		SceUInt32 unk_0x20;
		SceUInt32 unk_0x24;
		SceUInt32 unk_0x28;
		SceUInt32 unk_0x2C;
	} list[0x20];
	SceUInt32 nPhyMemPart;
	SceUIDPhyMemPartObject *pPhyMemPart[0x10];
} SceKernelAddressSpaceInfo;

typedef struct SceSysmemAddressSpaceInfo {
	uintptr_t base;
	SceSize total;
	SceSize free;
	SceSize unkC;
} SceSysmemAddressSpaceInfo;


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
          sceKernelAddressSpaceGetPhyMemPartByIndex: 0x3F74E45C
          sceKernelAddressSpaceSetName: 0x7BD56D6D
          sceKernelAddressSpaceSetPhyMemPart: 0x67955EE9
          sceKernelAddressSpaceSetProcess: 0x2476B90F
          sceKernelAddressSpaceUnmap: 0xCE72839E
          sceKernelAddressSpaceVARangeToPAVector: 0xF7250E6C
          sceKernelAddressSpaceVAtoPA: 0xF2179820
*/


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_AS_H_ */
