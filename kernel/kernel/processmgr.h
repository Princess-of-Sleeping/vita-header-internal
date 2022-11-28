
#ifndef _PSP2_KERNEL_PROCESSMGR_H_
#define _PSP2_KERNEL_PROCESSMGR_H_

#include <psp2kern/types.h>



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



#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */
