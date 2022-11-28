
#ifndef _PSP2_KERNEL_SYSMEM_PHYMEMPART_H_
#define _PSP2_KERNEL_SYSMEM_PHYMEMPART_H_

#include <shared/types.h>


typedef struct ScePhyMemPartInfoCore { // size is 0x10 on FWs 0.990-3.60
	SceUIntPtr pbase; // same as SceKernelPhyMemPart field 0x1C
	SceSize totalSize;
	SceSize freeSize;
	SceUInt32 unk_C; // maybe some counter
} ScePhyMemPartInfoCore;


void *sceKernelGetPhyPartTool(SceVoid);
void *sceKernelGetPhyPartGame(SceVoid);
void *sceKernelGetPhyPartKernel(SceVoid);


typedef struct SceKernelPhyMemPartInfo { // size is 0xB0-bytes
	SceSize size;
	SceUID part_id;
	const char *name;
	SceUInt32 type;
	SceSize freeSize;
	SceUInt32 unk_0x14;
	SceUInt32 unk_0x18;
	SceUInt32 unk_0x1C;
	SceUInt32 unk_0x20;
	SceUIntPtr base;
	SceSize length;
	SceUInt32 unk_0x2C;
	SceUInt32 unk_0x30;
	SceUInt32 unk_0x34;
	SceUInt32 unk_0x38;
	SceUInt32 unk_0x3C;
	SceUInt32 unk_0x40;
	SceUInt32 unk_0x44;
	SceUInt32 unk_0x48;
	SceUInt32 unk_0x4C;
	SceUInt32 unk_0x50;
	SceUInt32 unk_0x54;
	SceUInt32 unk_0x58;
	SceUInt32 unk_0x5C;
	SceUInt32 unk_0x60;
	SceUInt32 unk_0x64;
	SceUInt32 unk_0x68;
	SceUInt32 unk_0x6C;
	SceUInt32 unk_0x70;
	SceUInt32 unk_0x74;
	SceUInt32 unk_0x78;
	SceUInt32 unk_0x7C;
	SceUInt32 unk_0x80;
	SceUInt32 unk_0x84;
	SceUInt32 unk_0x88;
	SceUInt32 unk_0x8C;
	SceUInt32 unk_0x90;
	SceUInt32 unk_0x94;
	SceUInt32 unk_0x98;
	SceUInt32 unk_0x9C;
	SceUInt32 unk_0xA0;
	SceUInt32 unk_0xA4;
	SceUInt32 unk_0xA8;
	SceUInt32 unk_0xAC;
} SceKernelPhyMemPartInfo;

int sceKernelGetPhyMemPartInfoForDebugger(void *pPhyMemPart, SceKernelPhyMemPartInfo *info);


#endif /* _PSP2_KERNEL_SYSMEM_PHYMEMPART_H_ */
