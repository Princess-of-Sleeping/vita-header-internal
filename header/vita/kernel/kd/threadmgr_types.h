
#ifndef _PSP2KERNEL_KERNEL_THREADMGR_TYPES_H_
#define _PSP2KERNEL_KERNEL_THREADMGR_TYPES_H_

#include <psp2kern/types.h>
#include <psp2kern/kernel/threadmgr.h>
#include "sysmem/address_space.h"


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

typedef struct SceKernelThreadVfpInfo { // size is 0x120-bytes
	SceKernelThreadVfpRegister vfp_register;
	SceUInt32 fpscr;
	SceUInt32 fpexc;
	SceUInt32 unk_0x108;
	SceUInt32 unk_0x10C;
	SceUInt32 unk_0x110;
	SceUInt32 unk_0x114;
	SceUInt32 unk_0x118;
	SceUInt32 unk_0x11C;
} SceKernelThreadVfpInfo;

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

typedef struct SceKernelThreadRegisters { // size is 0x100
	int mode; // kernel:0, user:1

	unsigned int reg[0xF];

	unsigned int cpsr_kern;
	int uDACR;
	int kDACR;
	int CPACR;

	int TPIDRURW;
	void *TPIDRURO;
	SceUInt32 TTBR1;
	SceUInt32 CONTEXTIDR;

	int PAR;
	unsigned int PMCR;
	int PMOVSR;
	int PMSELR;

	int PMUSERENR;
	int PMCCNTR;
	int PMXEVTYPER0;
	int PMXEVCNTR0;

	int PMXEVTYPER1;
	int PMXEVCNTR1;
	int PMXEVTYPER2;
	int PMXEVCNTR2;

	int PMXEVTYPER3;
	int PMXEVCNTR3;
	int PMXEVTYPER4;
	int PMXEVCNTR4;

	int PMXEVTYPER5;
	int PMXEVCNTR5;
	unsigned int DFSR; // ex:0x8F5
	unsigned int IFSR;

	unsigned int DFAR;
	int IFAR;
	int TEEHBR;
	int unk_0xBC; // ex:user(0xFF), kernel(0xF0)? maybe?

	const void *pc;
	unsigned int cpsr;
	unsigned int DBGDSCR;
	int unk_0xCC;

	int unk_0xD0;
	int unk_0xD4;
	int unk_0xD8;
	int unk_0xDC;

	int unk_0xE0;
	int unk_0xE4;
	int unk_0xE8;
	int unk_0xEC;

	int PMCNTEN;
	SceKernelThreadVfpInfo *unk_0xF4; // TODO: check data type
	int unk_0xF8;
	int unk_0xFC;
} SceKernelThreadRegisters;

typedef struct SceKernelThreadObject { // size is 0x1B0-bytes
	struct {
		struct SceKernelThreadObject *next;
		struct SceKernelThreadObject *prev;
	} readyQueue;
	SceUID thread_id; // this object guid
	SceKernelThreadRegisters *pRegisterContext;

	// 0x10
	SceKernelThreadVfpInfo *pVfpRegisterContext;
	int data_0x3C;
	void *ptr_0x40; // SceProcessmgrInfoInternal ptr
	void *data_0x44; // some bkpt

	// 0x20
	void *data_0x48; // some bkpt
	int data_0x4C;
	int data_0x50;
	int data_0x54;

	// 0x30
	int data_0x58; // this ptr?
	void *ptr_0x5C; // userland. TLS
	SceUID processId;
	int data_0x64; // used by sceKernelCpuLockStoreLR
	int data_0x68;
	SceKernelThreadRegisterInfo *data_0x6C; // In kernel stack.
	int data_0x70;
	int data_0x74;
	int data_0x78;
	int data_0x7C;
	int data_0x80;
	int data_0x84;
	int data_0x88;
	int data_0x8C;

	void *ptr_0x90; // this obj ptr_0x90 ptr?
	void *ptr_0x94; // this obj ptr_0x90 ptr?
	int data_0x98; // some state
	void *stack_kern;
	SceSize stack_size_kern;
	int data_0xA4;
	int data_0xA8;
	int data_0xAC;
	int data_0xB0;
	int data_0xB4;

	void *ptr_0xB8; // pointer to SceUIDProcessObject->ptr2D0
	void *ptr_0xBC; // pointer to SceUIDProcessObject->ptr2D4?
	SceUID thread_id_user;
	int currentStatus; // ex: 0x80000100. maybe SceThreadStatus
	int exitStatus;
	SceUInt32 initialAttr;
	SceUInt32 currentAttr;
	int initialPriority;
	int currentPriority;
	int data_0xDC; // ex: 0xFE. some priority.
	int data_0xE0; // ex: 0xA0. some priority.
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
	int data_0x10C;
	int data_0x110;
	int data_0x114;
	int data_0x118;
	SceUIDAddressSpaceObject *ptr_0x11C;
	void *pUIDEntryHeap;
	SceUID processId2;
	int data_0x128;
	SceUID uTLSMemblkId;
	SceUInt32 stack_mem_type; // for kernel.
	int data_0x134;
	int data_0x138;
	int data_0x13C;
	int data_0x140;
	int data_0x144;
	int data_0x148;
	int data_0x14C;
	int data_0x150;
	int data_0x154;
	int data_0x158;
	int data_0x15C;
	int data_0x160;
	int data_0x164;
	int data_0x168;
	int data_0x16C;
	void *ptr_0x170; // some tree?
	void *ptr_0x174; // some tree?

	void *ptr_0x178; // some tree?
	void *ptr_0x17C; // some tree?

	void *ptr_0x180; // some tree?
	void *ptr_0x184; // some tree?
	void *ptr_0x188;
	void *ptr_0x18C;

	void *ptr_0x190; // some tree?
	void *ptr_0x194; // some tree?
	void *ptr_0x198;
	void *ptr_0x19C;
	void *pExceptionList; // size is 0x28-bytes
	int data_0x1A4;
	int data_0x1A8;
	int data_0x1AC;
	int data_0x1B0; // threadPreemptCount?
	int data_0x1B4;
	SceKernelSysClock runClocks;
	int data_0x1C0;
	int data_0x1C4;
	void *data_0x1C8; // size is 8-bytes
	void *data_0x1CC; // size is 0x28-bytes
	int data_0x1D0;
	SceUInt32 magic; // 0xE38B17A9
} SceKernelThreadObject;

typedef struct SceUIDThreadObject { // size is 0x200-bytes
	int sce_rsvd[2];
	int data_0x08;
	void *ptr_0x0C; // this obj data_0x08 ptr

	void *ptr_0x10; // this obj ptr_0x10 ptr
	void *ptr_0x14; // this obj ptr_0x10 ptr
	int data_0x18;
	int data_0x1C;
	int data_0x20; // attr mask value by 0xA000
	int data_0x24;
	SceKernelThreadObject kernel_thread_object;
	int data_0x1D8;
	int data_0x1DC;
	int data_0x1E0;
	int data_0x1E4;
	int data_0x1E8;
	int data_0x1EC;
	int data_0x1F0;
	int data_0x1F4;
	int data_0x1F8;
	int data_0x1FC;
} SceUIDThreadObject;

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
	SceKernelThreadVfpInfo *ptr_0x6C; // kernel tls? from uidobject + 0x58

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

	SceKernelThreadRegisters *pRegisters;
	SceKernelThreadVfpInfo *pVfpInfo;
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

	SceKernelThreadObject *pThreadObject;
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
	SceKernelThreadObject *pRunningThreadCB;
	SceKernelThreadObject *pNextRunningThreadCB;
	int data_0x08;
	struct {
		SceUID pid;
		SceUID thid;
	} current[2];
	SceUInt32 currentThreadPriority;
	struct {
		SceKernelThreadObject *next;
		SceKernelThreadObject *prev;
	} standbyList;
	SceKernelSpinlock lock;
	int unk_2C[2];
	SceKernelThreadObject *pIdleThreadCB; // idle thread for this CPU
	SceUInt64 unk_38;
	IntrRequest *intrRequestQueue;
	int unk_44;
	void *SwitchStackBlock_base; // 0x1000 size - idk what for
	SceUInt8 unk_4C[0x14];
	SceUInt32 priorityQueueBitmap[0x20 / sizeof(SceUInt32)];
	struct {
		SceKernelThreadObject *next;
		SceKernelThreadObject *prev;
	} priorityQueue[0x100];
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
