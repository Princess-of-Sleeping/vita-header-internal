
#ifndef _PSP2_KERNEL_PROCESSMGR_H_
#define _PSP2_KERNEL_PROCESSMGR_H_

#include <vita/shared/types.h>
#include <vita/kernel/kd/sysmem/phymempart.h>



#define SCE_KERNEL_PROCESS_CURRENT_PROCESS_BUDGET (0)



typedef struct SceKernelProcessInfo { // size is 0x24 or 0x4C on FW 0.931, 0xE8 on FW 3.60
	SceSize size;           // Size of this structure
	SceUID pid;             // Process ID
	SceUID addressSpaceId;
	int unk_C;              // processCreationFlags
	int status;             // Process status. ex: suspended = 0x11/0x10011, started = |2.
	SceUID ppid;            // Parent process ID
	SceUID budgetId;
	int cpuAffinity;        // CPU affinity. ex: 7
	int unk_20;             // might be initial priority. ex: 0x7F (127)
	SceUID modid;           // Module ID
	void *entrypoint;       // Process entry point
	SceUInt32 process_type;
	char name[0x20];        // Process name. ProcessObject->loadprocessparam.module_name if non-empty, else copy from sceGUIDGetName2ForDriver if not NULL, else \0
	void *unk_50;           // ?maxFHCount?
	void *unk_54;           // ?EntryHeap_uid?
	SceUID entryHeapId;     // GUID/PUID EntryHeap GUID
	int unk_5C;             // ex: -1
	int unk_60;             // ?module_inhibit_state?
	int unk_64;             // ex: 0x32
	void *KPLS_slots[0x20];
} SceKernelProcessInfo;

int sceKernelGetProcessInfo(SceUID pid, SceKernelProcessInfo *pInfo);


int sceKernelGetPidVector(SceUInt32 vis_level, SceUID *a2, SceSize a2_size, SceUInt32 *result);


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


typedef struct SceKernelBudgetInfoForDebugger { // size is 0x480-bytes
	SceSize size;
	SceUID budgetId;
	char name[0x20];
	int nInfo;
	struct {
		char name2[0x20];
		SceKernelPhyMemPartInfo pmp_info;
	} list[5];
	char unk_0x46C[0x44];
} SceKernelBudgetInfoForDebugger;

int sceKernelGetBudgetInfoForDebugger(SceUID budgetId, SceUInt32 level, SceKernelBudgetInfoForDebugger *info);


#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */
