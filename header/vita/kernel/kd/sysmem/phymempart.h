
#ifndef _PSP2_KERNEL_SYSMEM_PHYMEMPART_H_
#define _PSP2_KERNEL_SYSMEM_PHYMEMPART_H_

#include <shared/types.h>
#include <kernel/kd/sysmem/uid_class.h>


#ifdef __cplusplus
extern "C" {
#endif


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


int sceKernelGetPhyMemInfo(SceUInt32 pindex, void *info);

/*
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
	SceUInt32 unk_0x14; // orignal size?
	SceUInt32 unk_0x18;
	SceUInt32 unk_0x1C;
	SceUInt32 nList;
	struct {
		SceUIntPtr base;
		SceSize length;
	} list[0x10];
	SceUInt32 unk_0xA4;
	SceUInt32 unk_0xA8;
	SceUInt32 unk_0xAC;
} SceKernelPhyMemPartInfo;

int sceKernelGetPhyMemPartInfoForDebugger(void *pPhyMemPart, SceKernelPhyMemPartInfo *info);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_SYSMEM_PHYMEMPART_H_ */
