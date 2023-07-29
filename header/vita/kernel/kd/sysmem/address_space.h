
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
	SceUIDFixedHeapObject *unk_0x18;
	SceUIDFixedHeapObject *unk_0x1C;
	void *pL2PageTableHeap;
	int unk_0x24;
} SceKernelAddressSpaceMMUContext;

typedef struct SceUIDAddressSpaceObject { // size is 0x170-bytes
	void *pUserdata;
	SceClass *pClass;
	int unk_0x08;                          // for cpu function
	int unk_0x0C;
	int flag;                              // kernel:0x30000002, user:0x10000001
	SceUID pid;
	SceKernelAddressSpaceMMUContext *unk_0x18;
	SceUIDPartitionObject *pPart[0x20];
	SceUID unk_uid[0x20];                  // pPart object guid
	SceUIDPhyMemPartObject *pmpList[0x10];
	SceUID unk_0x15C;                      // for user process? it guid
	SceUID unk_0x160;                      // for user process? it guid
	int unk_0x164;
	SceUInt32 unk_0x168;                   // kernel:0x511389B0
	SceUInt32 magic;                       // 0x4D95AEEC
} SceUIDAddressSpaceObject;

#define SCE_KERNEL_ADDRESS_SPACE_MAGIC (0x4D95AEEC)

#define SCE_KERNEL_PARTITION_KERNEL_ROOT_INDEX                  (1) /* Official name */
#define SCE_KERNEL_PARTITION_KERNEL_IO_INDEX                    (2)
#define SCE_KERNEL_PARTITION_KERNEL_ROOT_UNCACHE_INDEX          (3)
#define SCE_KERNEL_PARTITION_KERNEL_CDRAM_INDEX                 (4)
#define SCE_KERNEL_PARTITION_KERNEL_ROOT_UNCACHE_INDEX_2        (5)
#define SCE_KERNEL_PARTITION_KERNEL_TMP_INDEX                   (6)
// #define SCE_KERNEL_PARTITION_UNKNOWN_7_INDEX                    (7)
#define SCE_KERNEL_PARTITION_USER_TOOL_INDEX                    (8)
#define SCE_KERNEL_PARTITION_USER_CDRAM_INDEX                   (9)
#define SCE_KERNEL_PARTITION_USER_SHARED_INDEX                  (10)
#define SCE_KERNEL_PARTITION_USER_IO_INDEX                      (11)
#define SCE_KERNEL_PARTITION_USER_MAIN_INDEX                    (12)
#define SCE_KERNEL_PARTITION_USER_UNCACHE_INDEX                 (13)
#define SCE_KERNEL_PARTITION_USER_CDIALOG_INDEX                 (14)
#define SCE_KERNEL_PARTITION_USER_CDIALOG_NC_INDEX              (15)
// #define SCE_KERNEL_PARTITION_UNKNOWN_16_INDEX                   (16)
#define SCE_KERNEL_PARTITION_KERNEL_ROOT_UNCACHE_GPU_GAME_INDEX (17)
#define SCE_KERNEL_PARTITION_KERNEL_TMP_FS_GAME_INDEX           (18)
#define SCE_KERNEL_PARTITION_KERNEL_TMP_FS_GAME_INDEX_2         (19)
#define SCE_KERNEL_PARTITION_KERNEL_TOOL_INDEX                  (20)
#define SCE_KERNEL_PARTITION_KERNEL_TOOL_UNCACHE_INDEX          (21)

#define SCE_KERNEL_PHYMEMPART_GAME_INDEX         (5)
#define SCE_KERNEL_PHYMEMPART_KD_INDEX           (6)
#define SCE_KERNEL_PHYMEMPART_PHYCONT_INDEX      (8)
#define SCE_KERNEL_PHYMEMPART_SHARED_INDEX       (9)
#define SCE_KERNEL_PHYMEMPART_GAME_CDIALOG_INDEX (10)
#define SCE_KERNEL_PHYMEMPART_MAIN_INDEX         (11)
#define SCE_KERNEL_PHYMEMPART_CDRAM_INDEX        (12)
#define SCE_KERNEL_PHYMEMPART_TOOL_INDEX         (15)
#define SCE_KERNEL_PHYMEMPART_SHELL_INDEX        SCE_KERNEL_PHYMEMPART_MAIN_INDEX
#define SCE_KERNEL_PHYMEMPART_SHELL_CDRAM_INDEX  SCE_KERNEL_PHYMEMPART_CDRAM_INDEX


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
