
#ifndef _PSP2_SYSMEM_INTERNAL_H_
#define _PSP2_SYSMEM_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <shared/types.h>


typedef struct SceKernelAllocMemBlockOptKernel { // size is 0x58 on FW 3.60
	SceSize size;			// Size of this structure
	SceUInt32 unk_4;                // Never used?
	SceUInt32 attr;
	void *vbase;                    // Virtual address memblock should be mapped at
	void *pbase;			// Physical address to use as base
	SceSize alignment;
	SceSize extraLow;               // Size of extra area starting from memblock vbase
	SceSize extraHigh;              // Size of extra area starting "after" memblock - extra area is ?not mapped?
	SceUID baseMemBlock;            // UID of memblock this one is based on
	SceUID pid;
	SceKernelPAVector *pPAV;
	SceSize roundupUnitSize;        // Used to roundup memblock vsize
	SceUInt8 domain;
	SceUInt32 unk_34; // Related to SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_0x20
	SceUInt32 unk_38; // Related to SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_0x20
	SceUInt32 unk_3C; // Related to SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_0x20
	SceUInt32 unk_40; // Related to SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_0x20
	SceUInt32 unk_44; // Related to SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_0x20
	SceUInt32 unk_48; // Related to SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_0x20
	SceUInt32 unk_4C; // Related to SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_0x20
	SceUInt32 unk_50; // Related to SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_0x20
	SceUInt32 unk_54; // Related to SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_0x20
} SceKernelAllocMemBlockOptKernel;


typedef struct SceKernelBlock { // size is 0x40-bytes
	struct SceKernelBlock *unk_0x00; // mixed alloc and free
	void *unk_0x04;
	struct SceKernelBlock *unk_0x08; // mixed alloc and free
	int state;
	SceUInt32 memtype;
	int unk_0x14;
	SceUIntPtr vbase;
	SceSize length;
	int unk_0x20;
	void *unk_0x24; // link root?
	struct SceKernelBlock *unk_0x28; // maybe next on same group
	const char *name;
	void *unk_0x30;
	int unk_0x34;
	int unk_0x38;
	SceUID guid;
} SceKernelBlock;

typedef struct SceKernelAllocMemBlockCommand {
	int data_0x00;
	int memtype;
	int data_0x08;
	char *name;
	int size;
	int data_0x14;
	int data_0x18;
	int data_0x1C;
	SceKernelAllocMemBlockOptKernel opt;
	SceKernelBlock *pBlock;
	int data_0x7C;
	int data_0x80;
	int data_0x84;
	int data_0x88;
	int data_0x8C;
} SceKernelAllocMemBlockCommand;

// ModulePrivate3
typedef struct SceKernelSystemMemory { // size is 0xDC-bytes
	SceSize size;
	int data_0x04;
	SceUIDEntryHeapObject *pUIDEntryHeap;
	void *data_0x0C; // size is 0x8-bytes.
	SceUIDPhyMemPartObject *pPhyMemPartKD;
	SceUIDPhyMemPartObject *pPhyMemPartTool;
	SceUIDFixedHeapObject *pFixedHeap16B;
	SceUIDFixedHeapObject *pFixedHeap32B;
	SceUIDFixedHeapObject *pFixedHeap48B;
	SceUIDFixedHeapObject *pFixedHeap64B;
	SceUIDFixedHeapObject *pFixedHeap128B;
	SceUIDFixedHeapObject *pFixedHeap256B;
	SceUIDFixedHeapObject *pFixedHeap512B;
	SceUIDFixedHeapObject *pFixedHeapForL2Object;
	void *nameheap_cb;
	void *data_0x3C; // smb stuff
	void *pKernelPatitionObject;
	void *pKernelHeapObject;
	SceKernelObjectHeap *pObjectHeap;
	SceSize number_of_memory_base_list;
	struct {
		SceUIntPtr base;
		SceSize length;
	} address_base[4];
	int data_0x70; // ex:0
	SceUIntPtr ttbr0_vbase;
	SceUIntPtr ttbr1_vbase;
	SceSize ttbr0_size;
	SceSize ttbr1_size;
	SceKernelPhyMemLowMap *pPhy;
	SceKernelPhyMemLowMap *pPAPhy;
	void *pPageKernelReset;
	int data_0x90; // allocate result of pPhyMemPartKD
	int data_0x94; // allocate result of pPhyMemPartKD
	SceClass *pUIDClass;
	SceClass *pUIDDLinkClass;
	SceKernelUIDHeapClass      *pKernelUIDHeapClass;
	SceKernelUIDFixedHeapClass *pKernelUIDFixedHeapClass;
	SceKernelUIDFixedHeapClass *pKernelUIDEntryHeapClass;
	SceClass *pUIDSimpleMemBlockClass;
	SceClass *pUIDMemBlockClass;
	SceClass *pUIDTinyPartitionClass;
	SceClass *pUIDPartitionClass;
	void *pKernelUIDpKernelHeapClass;
	void *data_0xC0; // size is 0xC-bytes
	void *data_0xC4; // size is 0x18-bytes. Related to partition
	void *data_0xC8; // size is 0x28-bytes. Related to partition
	SceUID kernelHeapUncachedId;
	void *data_0xD0; // SceAS object pointer
	void *pAddressSpaceCB; // size is 0xC-bytes.
	int data_0xD8;
} SceKernelSystemMemory;


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SYSMEM_INTERNAL_H_ */
