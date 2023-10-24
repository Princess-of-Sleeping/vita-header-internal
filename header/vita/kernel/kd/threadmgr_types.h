
#ifndef _PSP2KERNEL_KERNEL_THREADMGR_TYPES_H_
#define _PSP2KERNEL_KERNEL_THREADMGR_TYPES_H_

#include <psp2kern/types.h>


typedef struct _SceKernelThreadOptParam {
	SceSize   size;
	SceUInt32 attr;
	SceUInt32 kStackMemType;
	SceUInt32 uStackMemType;
	SceUInt32 uTLSMemType;
	SceUInt32 uStackMemid;
	SceUInt32 data_0x18;
} _SceKernelThreadOptParam;

typedef union SceKernelThreadVfpRegister { // size is 0x100-bytes
	union {
		SceFloat  value[0x40];
		SceUInt32 value_as_int[0x40];
	} s;
	union {
		SceDouble value[0x20];
		SceUInt64 value_as_int[0x20];
	} d;
} SceKernelThreadVfpRegister;

typedef struct _SceKernelVfpRegisterContext { // size is 0x120-bytes
	SceKernelThreadVfpRegister vfp_register;
	SceUInt32 fpscr;
	SceUInt32 fpexc;
	SceUInt32 unk_0x108;
	SceUInt32 unk_0x10C;
	SceUInt32 unk_0x110;
	SceUInt32 unk_0x114;
	SceUInt32 unk_0x118;
	SceUInt32 unk_0x11C;
} SceKernelVfpRegisterContext;

typedef struct SceKernelThreadRegisterInfo { // size is 0x60-bytes
	SceUInt32 reg[0xD];
	SceUInt32 unk_0x34;
	SceUInt32 unk_0x38; // ex:0xB90B45, lr?
	SceUInt32 fpscr;
	SceUInt32 unk_0x40;
	SceUInt32 unk_0x44;
	SceUInt32 unk_0x48;
	SceUInt32 unk_0x4C;
	SceUInt32 sp;
	SceUInt32 lr;
	SceUInt32 pc;
	SceUInt32 cpsr;
} SceKernelThreadRegisterInfo;

typedef struct _SceKernelRegisterContext { // size is 0x100
	SceUInt32 mode; // kernel:0, user:1
	SceUInt32 reg[0xF];
	SceUInt32 kCPSR;
	SceUInt32 uDACR;
	SceUInt32 kDACR;
	SceUInt32 CPACR;

	SceUInt32 TPIDRURW;
	SceUInt32 TPIDRURO;
	SceUInt32 TTBR1;
	SceUInt32 CONTEXTIDR;

	SceUInt32 PAR;
	SceUInt32 PMCR;
	SceUInt32 PMOVSR;
	SceUInt32 PMSELR;

	SceUInt32 PMUSERENR;
	SceUInt32 PMCCNTR;
	SceUInt32 PMXEVTYPER0;
	SceUInt32 PMXEVCNTR0;

	SceUInt32 PMXEVTYPER1;
	SceUInt32 PMXEVCNTR1;
	SceUInt32 PMXEVTYPER2;
	SceUInt32 PMXEVCNTR2;

	SceUInt32 PMXEVTYPER3;
	SceUInt32 PMXEVCNTR3;
	SceUInt32 PMXEVTYPER4;
	SceUInt32 PMXEVCNTR4;

	SceUInt32 PMXEVTYPER5;
	SceUInt32 PMXEVCNTR5;
	SceUInt32 DFSR; // ex:0x8F5
	SceUInt32 IFSR;

	SceUInt32 DFAR;
	SceUInt32 IFAR;
	SceUInt32 TEEHBR;
	SceUInt32 unk_0xBC; // ex:user(0xFF), kernel(0xF0)? maybe?

	SceUInt32 pc;
	SceUInt32 CPSR;
	SceUInt32 DBGDSCR;
	SceUInt32 unk_0xCC;

	SceUInt32 unk_0xD0;
	SceUInt32 unk_0xD4;
	SceUInt32 unk_0xD8;
	SceUInt32 unk_0xDC;

	SceUInt32 unk_0xE0;
	SceUInt32 unk_0xE4;
	SceUInt32 unk_0xE8;
	SceUInt32 unk_0xEC;

	SceUInt32 PMCNTEN;
	SceKernelVfpRegisterContext *unk_0xF4; // TODO: check data type
	SceUInt32 unk_0xF8;
	SceUInt32 unk_0xFC;
} SceKernelRegisterContext;

typedef struct _ThreadCB { // size is 0x1B0-bytes
	struct {
		struct ThreadCB *next;
		struct ThreadCB *prev;
	} readyQueue;
	SceUID threadId;
	SceKernelRegisterContext *pRegisterContext;
	SceKernelVfpRegisterContext *pVfpRegisterContext;
	int data_0x14;
	void *pProcess;
	void *data_0x1C; // some bkpt
	void *data_0x20; // some bkpt
	int data_0x24;
	int data_0x28;
	int data_0x2C;
	int data_0x30; // this ptr?
	void *ptr_0x34; // userland. TLS
	SceUID processId;
	int data_0x3C; // used by sceKernelCpuLockStoreLR
	int data_0x40;
	SceKernelThreadRegisterInfo *data_0x44; // In kernel stack. pSyscallFrame
	int data_0x48;
	int data_0x4C;
	int data_0x50;
	int data_0x54;
	int data_0x58;
	int data_0x5C;
	int data_0x60;
	int data_0x64;
	void *ptr_0x68; // this obj ptr_0x90 ptr?
	void *ptr_0x6C; // this obj ptr_0x90 ptr?
	int data_0x70; // some state
	void *stack_kern;
	SceSize stack_size_kern;
	int data_0x7C;
	int data_0x80;
	int data_0x84;
	int data_0x88;
	int data_0x8C;
	void *ptr_0x90; // pointer to SceUIDProcessObject->ptr2D0
	void *ptr_0x94; // pointer to SceUIDProcessObject->ptr2D4?
	SceUID uThreadId;
	int currentStatus; // ex: 0x80000100. maybe SceThreadStatus
	int exitStatus;
	SceUInt32 initialAttr;
	SceUInt32 currentAttr;
	int initialPriority;
	int currentPriority;
	int data_0xB4; // ex: 0xFE. some priority.
	int data_0xB8; // ex: 0xA0. some priority.
	int initialCpuAffinityMask;
	int currentCpuAffinityMask;
	int currentCpuId;
	int lastExecutedCpuId;
	void *stack_top;
	void *stack_bottom;
	SceSize stack_size;
	SceUID uStackMemblkId;
	SceUID kStackMemblkId;
	SceKernelThreadEntry entry;
	int data_0xE4;
	int data_0xE8;
	int data_0xEC;
	int data_0xF0;
	struct SceUIDAddressSpaceObject *pAddressSpace;
	void *pUIDEntryHeap;
	SceUID processId2;
	int data_0x100;
	SceUID uTLSMemblkId;
	SceUInt32 stack_mem_type; // for kernel.
	int data_0x10C;
	int data_0x110;
	int data_0x114;
	int data_0x118;
	int data_0x11C;
	int data_0x120;
	int data_0x124;
	int data_0x128;
	int data_0x12C;
	int data_0x130;
	int data_0x134;
	int data_0x138;
	int data_0x13C;
	int data_0x140;
	int data_0x144;
	void *ptr_0x148; // some tree?
	void *ptr_0x14C; // some tree?
	void *ptr_0x150; // some tree?
	void *ptr_0x154; // some tree?
	void *ptr_0x158; // some tree?
	void *ptr_0x15C; // some tree?
	void *ptr_0x160;
	void *ptr_0x164;
	void *ptr_0x168; // some tree?
	void *ptr_0x16C; // some tree?
	void *ptr_0x170;
	void *ptr_0x174;
	void *pExceptionList; // size is 0x28-bytes
	int data_0x17C;
	int data_0x180;
	int data_0x184;
	int data_0x188; // threadPreemptCount?
	int data_0x18C;
	SceKernelSysClock runClocks;
	int data_0x198;
	int data_0x19C;
	void *data_0x1A0; // size is 8-bytes
	void *data_0x1A4; // size is 0x28-bytes
	int data_0x1A8;
	SceUInt32 magic; // 0xE38B17A9
} __attribute__((packed)) ThreadCB;

typedef struct _SceUIDThreadObject { // size is 0x1D8-bytes
	ThreadCB threadCB;
	int data_0x1B0;
	int data_0x1B4;
	int data_0x1B8;
	int data_0x1BC;
	int data_0x1C0;
	int data_0x1C4;
	int data_0x1C8;
	int data_0x1CC;
	int data_0x1D0;
	int data_0x1D4;
} __attribute__((packed)) SceUIDThreadObject;

typedef struct _SceUIDCacheObject { // size is 0x10-bytes
	int sce_rsvd[2];
	int data_0x08;
	void *ptr_0x0C; // this obj data_0x08 ptr
} __attribute__((packed)) SceUIDCacheObject;

typedef struct _SceUIDWaitableObject { // size is 0x28-bytes
	SceUIDCacheObject uidCacheObject;
	void *ptr_0x10; // this obj ptr_0x10 ptr
	void *ptr_0x14; // this obj ptr_0x10 ptr
	int data_0x18;
	int data_0x1C;
	int data_0x20; // attr mask value by 0xA000
	int data_0x24;
} __attribute__((packed)) SceUIDWaitableObject;

typedef struct _SceUIDThreadObjectEx { // size is 0x200-bytes
	SceUIDWaitableObject uidWaitableObject;
	SceUIDThreadObject uidThreadObject;
} __attribute__((packed)) SceUIDThreadObjectEx;

typedef struct SceKernelThreadInfoInternal { // size is 0x128-bytes
	SceSize size;
	SceUID thid_user;
	SceUID processId;

	// offset:0xC
	char name[0x20];
	int pad_0x2C;

	// offset:0x30
	SceUInt attr;
	int status;
	SceKernelThreadEntry entry;
	void *stack;

	// offset:0x40
	SceSize         stackSize;
	int unk_0x44;
	int unk_0x48;
	void *kernel_stack;

	// offset:0x50
	SceSize kernel_stack_size;
	int unk_0x54;
	int unk_0x58;
	int unk_0x5C;

	// offset:0x60
	int unk_0x60;
	int unk_0x64;
	int unk_0x68;
	SceKernelVfpRegisterContext *ptr_0x6C; // kernel tls? from uidobject + 0x58

	// offset:0x70
	int unk_0x70;
	int unk_0x74;
	int initPriority;
	int currentPriority;

	// offset:0x80
	int initCpuAffinityMask;
	int currentCpuAffinityMask;
	int unk_0x88;
	int currentCpuId;

	// offset:0x90
	int lastExecutedCpuId;
	int waitType; // maybe
	int unk_0x98;
	SceKernelSysClock runClocks;

	int exitStatus;
	int unk_0xA8; // IsThreadDebugSuspended
	SceUInt     intrPreemptCount;

	// offset:0xB0
	SceUInt     threadPreemptCount;
	SceUInt     threadReleaseCount;
	SceUID      fNotifyCallback;
	int         reserved; // from SceUIDThreadObject->unk_0x4C bit30

	SceKernelRegisterContext *pRegisterContext;
	SceKernelVfpRegisterContext *pVfpRegisterContext;
	SceKernelThreadRegisterInfo *pUserRegisterInfo; // Is it set only when cause (0x1000X)
	int unk_0xCC;

	void *pUserTLS;
	int unk_0xD4;
	int unk_0xD8;
	void *ptr_0xDC; // size is 0x18

	int unk_0xE0;
	int unk_0xE4;
	int unk_0xE8;
	int unk_0xEC;

	int unk_0xF0;
	int unk_0xF4;
	int unk_0xF8; // from SceUIDThreadObject->unk_0x4C bit27
	int unk_0xFC;

	ThreadCB *pThreadCB;
	int unk_0x104;
	int unk_0x108;
	int unk_0x10C;

	int unk_0x110;
	int unk_0x114;
	int unk_0x118;
	int unk_0x11C;

	int unk_0x120;
	int unk_0x124;
} __attribute__((packed)) SceKernelThreadInfoInternal;


typedef struct IntrRequest {
	struct IntrRequest *next;
	int type;       // In 0-3, 8-0x14, 0x18-0x19
	int from_cache; // 0 = alloc from heap, otherwise comes from Threadmgr link list
	int padding;
	int arguments[4];
} IntrRequest;

typedef struct ThreadMgrCpuCB { // size is 0x880-bytes
	ThreadCB *pRunningThreadCB;
	ThreadCB *pNextRunningThreadCB;
	int data_0x08;
	struct {
		SceUID pid;
		SceUID thid;
	} current[2];
	SceUInt32 currentThreadPriority;
	struct {
		ThreadCB *next;
		ThreadCB *prev;
	} standbyList;
	SceKernelSpinlock lock;
	int unk_2C[2];
	ThreadCB *pIdleThreadCB; // idle thread for this CPU
	SceUInt64 unk_38;
	IntrRequest *intrRequestQueue;
	int unk_44;
	void *SwitchStackBlock_base; // 0x1000 size - idk what for
	SceUInt8 unk_4C[0x14];
	SceUInt32 readyQueueBitmap[0x20 / sizeof(SceUInt32)];
	struct {
		ThreadCB *next;
		ThreadCB *prev;
	} readyQueue[0x100];
} ThreadMgrCpuCB;

typedef struct SceKernelThreadmgrPrivate { // size is 0x28C8-bytes
	ThreadMgrCpuCB cpuCB[4];
	int threadMgrCBLock;
	unsigned int allowCpuMask;
	int data_0x00;
	int data_0x04_lock;
	int data_0x08_counter;
	int data_0x0C;

	void *data_0x10;
	void *data_0x14;
	int data_0x18;
	int data_0x1C_lock;

	void *data_0x20;
	void *data_0x24;

	struct {
		void *next;
		void *prev;
	} ThreadDLink;

	void *data_0x30;
	void *data_0x34;
	void *data_0x38;
	void *data_0x3C;
	void *data_0x40;
	void *data_0x44;

	void *data_0x48;
	void *data_0x4C;
	void *data_0x50;
	void *data_0x54;

	int data_0x58;

	struct {
		int registered;
		int data_0x04;
		int size;
		void *freeCb;
		void *pUserdata;
	} KTLS[8]; // used by SceThreadmgrForDriver_B645C7EF
	int threadMgrCBHeapId;

	// Related to timer
	int SceLT5_memid;
	void *SceLT5_base;
	int data2_0x00_lock;
	int data2_0x04;
	int data2_0x08;
	int data2_0x0C;
	void *data2_0x10;
	void *data2_0x14;
	unsigned long long data2_0x18;

	void *pUIDThreadClassEx;
	void *pUIDSemaphoreClassEx;
	void *pUIDEventFlagClassEx;
	void *pUIDMutexClassEx;
	void *pUIDCondClassEx;
	void *pUIDTimerClassEx;
	void *pUIDMsgPipeClassEx;
	void *pUIDCallbackClass;
	void *pUIDThreadEventClass;
	void *pUIDLwMutexClassEx;
	void *pUIDLwCondClassEx;
	void *pUIDRWLockClassEx;
	void *pUIDSimpleEventClassEx;
	void *pUIDExceptionClassEx;
	void *pUIDFastMutexClassEx;
	void *pUIDDelayClassEx;
	void *pUIDAlarmClassEx;
	void *pUIDWorkQueueClassEx;
	void *pUIDWorkTaskClassEx;
	void *pUIDCacheClass;
	void *pUIDWaitableClassEx;
	void *pUIDRegisterCallbackClassEx;
	void *pUIDEventClassEx;
	void *pUIDCpuTimerClassEx;
	void *pUIDProcessClass; // SceThreadmgrForKernel_766028E7
	int uidSignalObject_guid;
	void *pUIDSignalObject;
	void *threadmgrIntrHandler[0x10];
	int data2_0x40[3]; // SceThreadmgrForDriver_1378F6EF

	// SceThreadmgrForDriver_5311CFB5
	int data2_0x4C;
	int data2_0x50;

	int threadmgrCBBlockId;
	int currentRunningThreadId[4];

	unsigned char data3[0x24];

	// Related to uidThreadEvent
	void *data3_0x24_next;
	void *data3_0x24_prev;

	// Related to something thread ready
	int data4_0x00;
	int threadmgrTestMode;
	int data4_0x08;
	int data4_0x0C; // lock
	int data4[0xFC];

	int msgPipeAsyncThreadId[8];
	int msgPipeAsyncMutexId;
	int msgPipeAsyncCondId;
	int data5[8];
	int msgPipeAsyncReqCompCondId[8];
	void *data6_next;
	void *data6_prev;
	unsigned char data7[0x8];

	int syslibtraceThreadCBInitFlag;
	int dtraceThreadCBInitFlag;
	int data8_heapid; // syslibtraceThreadCB/dtraceThreadCB
	unsigned char data8_0x04[0xC];
	int data8_atomic;
	int data8_0x14;
} SceKernelThreadmgrPrivate;


#endif /* _PSP2KERNEL_KERNEL_THREADMGR_TYPES_H_ */
