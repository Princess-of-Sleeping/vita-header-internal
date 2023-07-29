
#ifndef _PSP2_KERNEL_PROCESSMGR_H_
#define _PSP2_KERNEL_PROCESSMGR_H_

#include <psp2kern/types.h>
#include "sysmem/address_space.h"
#include "sysmem/phymempart.h"
#include "modulemgr.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef SceUInt32 SceProcessType;

typedef struct _SceKernelCallbackListEntry {
	struct _SceKernelCallbackListEntry* next;
	SceUID callback_uid;
} SceKernelCallbackListEntry;

typedef struct _SceUIDProcessObject { // size is 0x4E0 on FW 3.60
	void *process_kobj; // Comes from scePUIDKernelCreateWithAttrForKernel
	uint32_t unk4;
	uint32_t unk8;
	void *breakpoints_ctx; // pointer to 0x60 bytes structure - only present if dipsw 0xE4 is set
	int unk10;
	SceUID process_lock_sema;  // "SceKernelProcessmgrProcLock", semaphore created with attribute 0x8000, max count = init count = 1
	SceUID process_event_flag; // "SceKernelProcessmgrProc", event flag with attribute ATTR_MULTI | 0x8000, initial pattern = 0x10000 - LSB is set near the end of CreateProcess
	SceUID event_lock_sema;    // "SceKernelProcessEventLock", semaphore created with attribute 0x8000, max count = init count = 4
	SceKernelSysClock some_time_20;
	int cpu_intr;
	int32_t unk2C; // maybe unsigned
	int unk30;
	int unk34;
	int unk38;
	SceUInt32 status;                            // Set to 0x20001 if 0x80000000 is set in SceKernelCreateProcessOpt.flags, else ANDed with 0xFFFFFF00 then ORed with 1 - if (unk3C & 0xFF), added process object added to a "to be destroyed" linked list to be cleaned up by a resident thread on process deletion, else process object destructor is called
	SceProcessType process_type;                 // Value of the process_type argument passed to sceKernelCreateProcess
	uint32_t process_creation_flags;             // Value of the opt->flags value passed to sceKernelCreateProcess (0 if NULL)
	void *entry_heap_obj;                        // Result of sceUIDtoObject(entry_heap_uid);
	SceUID entry_heap_uid;                       // Result of sceUIDCreateEntryHeapForKernel
	SceUID unk50;
	uint32_t affinity_mask;                      // Seems to be bit X -> core X
	uint32_t unk58;                              // some atomic global variable related to affinity_mask
	SceUID address_space_uid;                    // Result of sceKernelCreateAddressSpaceForKernel
	SceUIDAddressSpaceObject *address_space_obj; // Result of sceGUIDGetObjectForDriver(address_space_uid)
	ScePID process_id;                           // Result of scePUIDKernelCreateWithAttrForKernel(SceUIDProcessClass, ...)
	ScePID parent_process_id;                    // PID of caller to sceKernelCreateProcess, can be overridden in SceKernelCreateProcessOpt
	SceUID main_thread_uid;                      // UID of the first thread created in process
	SceUID unk70;
	void* partition_budget_thing;                // Pointer to 0x74 structure related to budgets and partitions - depends on process type
	SceUID partition_budget_thing_uid;           // Comes from a field in struct above
	int32_t unk7C;                               // maybe unsigned
	SceUID unique_heap_uid;                      // "unique: %s", variable size, type SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RW_10C0D006
	SceUID kpls_heap_uid;                        // "kpls: %s", 0x40000 size, allocated in kpls memblock
	SceUID CDialog_heap_uid;                     // "CDialog: %s", 0x1000 size, type SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RW_CDIALOG
	SceUID tool_heap_uid;                        // "tool: %s", 0xF000/0x7F000 size, type SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_TOOL_RW, only created if dipsw 0xD2 is enabled
	SceUID kpls_memblock_uid;                    // "kpls: %s", 0x40000 size, type SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RW
	int32_t unk94;                               // maybe unsigned
	int32_t unk98;                               // maybe unsigned - set to 0x7F
	SceKernelLibraryDB *pLibraryDB;
	SceUInt32 unkA0;                             // Allowed minimum thread priority?
	int8_t random_data[0x10];                    // Filled using sceMt19937GlobalUIntInRangeForDriver, then SceKernelUtilsForDriver_B55C69B7 called on it
	uint32_t unkB4;
	SceSelfAuthInfo self_auth_info;              // klicensee is set to 0 unless specified in SceKernelCreateProcessOpt (in which case .Secret.SharedSecret3_0 is set to 0x10) - passed to sceKernelLoadProcessImageForKernel
	SceLoadProcessParam load_process_param;

	// 0x1C4
	struct _stdio {
		struct {
			SceUID stdin;  // result of IoOpen("tty0:")
			SceUID stdout; // result of IoOpen("tty0:")
			SceUID stderr; // result of IoOpen("tty1:")
			SceUID extra;  // result of IoOpen("tty7:") - needs dipsw 0xB8 set
		} guid;
		struct {
			SceUID stdin;  // result of scePUIDOpenByGUIDForDriver(pid, guid.stdin)
			SceUID stdout; // result of scePUIDOpenByGUIDForDriver(pid, guid.stdout)
			SceUID stderr; // result of scePUIDOpenByGUIDForDriver(pid, guid.stderr)
			SceUID extra;  // result of scePUIDOpenByGUIDForDriver(pid, guid.extra)
		} puid;
	} stdio;
	struct _LibKernelAddress {
		int (* sceKernelExitThread)(int a1);
		int (* sceKernelExitDeleteThread)(int a1);
		int (* _sceKernelExitCallback)();
		void *unk_cb_0x10;
		int *pStackGuard1;
		int *pStackGuard2;
	} LibKernelAddress;

	int syscallTraceFlag;
	int unk200;

	SceKernelSpinlock KPLSLock;
	void *KPLS_slots[0x20]; // Pointer to memory allocated for KPLS slots of this process - [3] is "display_info" (size maybe 0x1D0-0x1D8), [4] size may be 0x50-0x58, [23] size may be 0x24-0x28

	// bkpt
	void *bkpt_ctx_field58; // Pointer to breakpoints_ctx->unk58
	int unk28C;

	SceUInt32 initialPMCR;
	int32_t unk294; // maybe unsigned
	int32_t unk298; // maybe unsigned
	int32_t unk29C; // maybe unsigned
	int32_t unk2A0; // maybe unsigned
	int32_t unk2A4; // maybe unsigned
	void *destruction_ll_next; // pointer to next entry in "to be destroyed" process list?
	void *destruction_ll_prev; // pointer to previous entry in "to be destroyed" process list?

	SceKernelSpinlock statusLock;

	SceUInt32 powerLockChain;
	SceKernelSpinlock powerLockLock;
	int32_t unk2BC; // some ProcEventHandler state
	uint32_t __stack_chk_guard; // Filled using sceMt19937GlobalUIntInRangeForDriver
	SceKernelCallbackListEntry *process_delete_cb; // On object deletion, all callbacks in list are called - may be called at other moments
	SceUID preloadThreadId;

	// Thread DLink
	void *ptr2D0;
	void *ptr2D4; // pointer to SceKernelThreadObject->offset_0xb8

	SceUInt32 unk2D8; // maybe thread number (not have thread attr 0x4000)
	SceUInt32 unk2DC; // maybe thread number (not have thread attr 0x4000)
	SceUInt32 unk2E0; // maybe thread number (have thread attr 0x4000)
	SceUInt32 unk2E4; // maybe thread number (have thread attr 0x4000)
	void *unk2E8;
	void *unk2EC;
	int8_t unk2F0[0x40]; // memset to 0

	SceUID unk330;
	SceUID unk334;
	SceUID unk338;
	int32_t unk33C; // maybe unsigned or SceUID
	int32_t unk340; // maybe unsigned or SceUID
	int32_t unk344; // maybe unsigned or SceUID
	int32_t unk348; // maybe unsigned or SceUID
	int32_t unk34C; // sceKernelCallAbortHandlerForUser
	SceUID unk350;
	int32_t unk354;
	int32_t unk358;
	int32_t unk35C; // curr ctr
	int32_t unk360; // peak ctr
	int32_t unk364; // curr ctr with attr 0x4000
	int32_t unk368; // peak ctr with attr 0x4000

	int unk36C[0x20]; // some value list?

	// 0x36c callback
	// 0x370 callback peak
	// 0x374 ThreadEventHandler
	// 0x378 ThreadEventHandler peak
	// 0x37c cond
	// 0x380 cond peak
	// 0x384 evf
	// 0x388 evf peak
	// 0x38c lw_cond
	// 0x390 lw_cond peak
	// 0x394 lw mutex
	// 0x394 lw mutex peak
	// 0x39c msgpipe
	// 0x3a0 msgpipe peak
	// 0x3a4 mutex
	// 0x3a8 mutex peak
	// 0x3ac RWLock
	// 0x3b0 RWLock peak
	// 0x3b4 sema
	// 0x3b8 sema peak
	// 0x3bc simple event
	// 0x3c0 simple event peak
	// 0x3c4 timer
	// 0x3c8 timer peak
	// 0x3cc unk
	// 0x3e0 unk peak
	// 0x3e4 Open
	// 0x3e8 Open peak

	SceKernelSpinlock coredumpLock;
	void *coredump_handler;
	SceSize coredump_memblock_size;
	void *coredump_memblock_addr;
	SceUID coredump_memblock_id;

	int32_t unk400; // maybe unsigned
	uint32_t unk404; // From SceKernelCreateProcessOpt, ((uint16_t)opt.unk3C << 16) | ((uint16_t)opt.unk38)

	int unk408;

	// 3.60
	// int unk408;
	// int unk40A;
	int16_t unk40C; // maybe unsigned
	int16_t unk40E; // maybe unsigned
	uint32_t main_thread_fallback_affinity_mask; // Used if LoadProcessParam affinity mask is 0 - if this is also 0 then mask is taken from budget thing - init to 0x962E8D55 in constructor
	void *pPPM0_area;
	void *pPPM0_or_PPM1_area;
	uint32_t unk41C; // ?related to dipsw 0xD2?
	void *unk420;
	void *unk424;
	uint32_t max_fh_count;       // maximum number of file handles the process can have open
	uint32_t max_dir_open_level; // maximum depth a file can be opened at?
	int32_t unk430;              // maybe unsigned
	int32_t unk434;              // maybe unsigned
	struct _SceUIDProcessObjectListEntry {
		struct _SceUIDProcessObjectListEntry *next;
		struct _SceUIDProcessObjectListEntry *prev;
		struct _ProcessResourceInfo {
			SceUInt32 interrupt_mtx; // Mutex for SuspendInterrupt
			SceSize max_count;       // Maximum number of resources of this type allowed
			SceSize cur_count;       // Current number of resources of this type
			SceSize highwater;       // Not sure - highest number of resources of this type process had
		} process_resources[8];
		char TitleId[0x20];
	} list_entry;
} SceUIDProcessObject;


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
		char name[0x20];
		SceKernelPhyMemPartInfo pmp_info;
	} list[5];
	char unk_0x46C[0x44];
} SceKernelBudgetInfoForDebugger;

int sceKernelGetBudgetInfoForDebugger(SceUID budgetId, SceUInt32 level, SceKernelBudgetInfoForDebugger *info);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */
