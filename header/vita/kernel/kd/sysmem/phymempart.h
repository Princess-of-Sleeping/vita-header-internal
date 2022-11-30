
#ifndef _PSP2_KERNEL_SYSMEM_PHYMEMPART_H_
#define _PSP2_KERNEL_SYSMEM_PHYMEMPART_H_

#include <vita/shared/types.h>


/*
          sceKernelGetPhyMemInfo: 0x89475192
          sceKernelCreatePhyMemPart: 0x2E36E0C4
          sceKernelCreatePhyMemPartByPbase: 0x63D83911
          sceKernelDeletePhyMemPart: 0x2AEA9E09
          sceKernelFreePhyPage: 0x00BC5B4A
          sceKernelGetGrownPhyMemPartSize: 0x4D809B47
          sceKernelGetPhyMemPartAll: 0x2F6F9C2C
          sceKernelGetPhyMemPartInfoByID: 0xF4FA0575
          sceKernelGetPhyMemPartInfoCore: 0x3650963F
          sceKernelGetPhyMemPartInfoForDebugger: 0x54E85275
          sceKernelGetPhyPageReset: 0xEB350679
          sceKernelGetPhyPartGame: 0xB60568F9
          sceKernelGetPhyPartKernel: 0x4D38F861
          sceKernelGetPhyPartTool: 0xF8E95A5A
          sceKernelGrowPhyMemPart: 0x6B3F4102
          sceKernelGrowPhyMemPartByPbase: 0x775AA5E3
          sceKernelPhyMemLowAlloc: 0x5E169FEF
          sceKernelPhyMemLowFree: 0x18B99FDD
          sceKernelPhyMemLowPA2VA: 0x0FD6B756
          sceKernelPhyMemPartAllocPhyPage: 0xD449547B
          sceKernelResetPhyMemPart: 0xEEB85560
          sceKernelSetPhyPartGame: 0x77876A8D
          sceKernelShowPhyMemPart: 0x5C257482
*/

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
