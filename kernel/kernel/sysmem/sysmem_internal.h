
#ifndef _PSP2_SYSMEM_INTERNAL_H_
#define _PSP2_SYSMEM_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <psp2common/types.h>
#include <psp2kern/kernel/sysmem.h>


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
	SceKernelAllocMemBlockKernelOpt opt;
	SceKernelBlock *pBlock;
	int data_0x7C;
	int data_0x80;
	int data_0x84;
	int data_0x88;
	int data_0x8C;
} SceKernelAllocMemBlockCommand;


#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SYSMEM_INTERNAL_H_ */
