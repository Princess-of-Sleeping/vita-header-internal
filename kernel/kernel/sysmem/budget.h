
#ifndef _PSP2_KERNEL_SYSMEM_BUDGET_H_
#define _PSP2_KERNEL_SYSMEM_BUDGET_H_

#include <psp2kern/types.h>
#include <kernel/kernel/sysmem/phymempart.h>


typedef struct SceKernelBudgetInfo { // size is 0x88-bytes
	SceSize size;
	SceUInt32 count;
	ScePhyMemPartInfoCore unk_0x08;
	ScePhyMemPartInfoCore unk_0x18;
	ScePhyMemPartInfoCore unk_0x28;
	SceUInt32 unk_0x38;
	SceUInt32 unk_0x3C;
	SceUInt32 unk_0x40;
	SceUInt32 unk_0x44;
	SceUInt32 unk_0x48;
	SceUInt32 unk_0x4C;
	SceUInt32 unk_0x50;
	SceUInt32 unk_0x54;
	ScePhyMemPartInfoCore unk_0x58;
	SceUInt32 unk_0x68;
	SceUInt32 unk_0x6C;
	SceUInt32 unk_0x70;
	SceUInt32 unk_0x74;
	ScePhyMemPartInfoCore unk_0x78;
} SceKernelBudgetInfo;


int sceKernelGetBudgetInfo(SceUID budgetId, SceKernelBudgetInfo *pInfo);


#endif /* _PSP2_KERNEL_SYSMEM_BUDGET_H_ */
