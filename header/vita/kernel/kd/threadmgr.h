
#ifndef _PSP2_KERNEL_THREADMGR_H_
#define _PSP2_KERNEL_THREADMGR_H_

#include <psp2kern/types.h>
#include "threadmgr/delay.h"
#include "threadmgr/workqueue.h"
#include "threadmgr/gpu_exception.h"


#ifdef __cplusplus
extern "C" {
#endif


/*
          SceThreadmgrForDriver_032E8F73: 0x032E8F73
          SceThreadmgrForDriver_09346D1A: 0x09346D1A
          SceThreadmgrForDriver_0A4AD37A: 0x0A4AD37A
          SceThreadmgrForDriver_0D0644DA: 0x0D0644DA
          SceThreadmgrForDriver_0EB0ABF0: 0x0EB0ABF0
          SceThreadmgrForDriver_1096042E: 0x1096042E
          SceThreadmgrForDriver_1378F6EF: 0x1378F6EF
          SceThreadmgrForDriver_154F2C2A_waitWorkQueue: 0x154F2C2A
          SceThreadmgrForDriver_19F3E92A: 0x19F3E92A
          SceThreadmgrForDriver_20C228E4: 0x20C228E4
          SceThreadmgrForDriver_25AB8F6B: 0x25AB8F6B
          SceThreadmgrForDriver_2828F884: 0x2828F884
          SceThreadmgrForDriver_2E95B628: 0x2E95B628
          SceThreadmgrForDriver_2F9F75AA: 0x2F9F75AA
          SceThreadmgrForDriver_2FC0FFF6: 0x2FC0FFF6
          SceThreadmgrForDriver_36F8E58A: 0x36F8E58A
          SceThreadmgrForDriver_3A72C6D8: 0x3A72C6D8
          SceThreadmgrForDriver_3C297724: 0x3C297724
          SceThreadmgrForDriver_3F5E1D56: 0x3F5E1D56
          SceThreadmgrForDriver_419E6736: 0x419E6736
          SceThreadmgrForDriver_477F7C8A: 0x477F7C8A
          SceThreadmgrForDriver_47F26712: 0x47F26712
          SceThreadmgrForDriver_48C06CD6_waitWorkQueue: 0x48C06CD6
          SceThreadmgrForDriver_4A038803: 0x4A038803
          SceThreadmgrForDriver_4DE77569: 0x4DE77569
          SceThreadmgrForDriver_5311CFB5: 0x5311CFB5
          SceThreadmgrForDriver_54566860: 0x54566860
          SceThreadmgrForDriver_555CA6BB: 0x555CA6BB
          SceThreadmgrForDriver_56C18B11: 0x56C18B11
          SceThreadmgrForDriver_5870C73A: 0x5870C73A
          SceThreadmgrForDriver_5D8F88B1: 0x5D8F88B1
          SceThreadmgrForDriver_6657429E: 0x6657429E
          SceThreadmgrForDriver_67022B18: 0x67022B18
          SceThreadmgrForDriver_6C2E3A49: 0x6C2E3A49
          SceThreadmgrForDriver_6D4C1EB7: 0x6D4C1EB7
          SceThreadmgrForDriver_738FF63D: 0x738FF63D
          SceThreadmgrForDriver_767CA30C: 0x767CA30C
          SceThreadmgrForDriver_7D12344A: 0x7D12344A
          SceThreadmgrForDriver_7E280B69: 0x7E280B69
          SceThreadmgrForDriver_84EB1EA4: 0x84EB1EA4
          SceThreadmgrForDriver_85F4DC8C: 0x85F4DC8C
          SceThreadmgrForDriver_86DAE59B: 0x86DAE59B
          SceThreadmgrForDriver_88206D29: 0x88206D29
          SceThreadmgrForDriver_89CA5698: 0x89CA5698
          SceThreadmgrForDriver_8C3C1F78: 0x8C3C1F78
          SceThreadmgrForDriver_8C48E53B: 0x8C48E53B
          SceThreadmgrForDriver_91A8F38B: 0x91A8F38B
          SceThreadmgrForDriver_995F32E1: 0x995F32E1
          SceThreadmgrForDriver_A64B00F6: 0xA64B00F6
          SceThreadmgrForDriver_A90B1E01: 0xA90B1E01
          SceThreadmgrForDriver_AB977C72: 0xAB977C72
          SceThreadmgrForDriver_AF302193: 0xAF302193
          SceThreadmgrForDriver_B4A05763: 0xB4A05763
          SceThreadmgrForDriver_B6DA4669: 0xB6DA4669
          SceThreadmgrForDriver_C03799E2: 0xC03799E2
          SceThreadmgrForDriver_C2DA6286: 0xC2DA6286
          SceThreadmgrForDriver_C327CA7C: 0xC327CA7C
          SceThreadmgrForDriver_C4456EC9: 0xC4456EC9
          SceThreadmgrForDriver_C6741986: 0xC6741986
          SceThreadmgrForDriver_C7F5FFE0: 0xC7F5FFE0
          SceThreadmgrForDriver_CA704239: 0xCA704239
          SceThreadmgrForDriver_CBA7FAAA: 0xCBA7FAAA
          SceThreadmgrForDriver_CFA2FFAF: 0xCFA2FFAF
          SceThreadmgrForDriver_D0262C55: 0xD0262C55
          SceThreadmgrForDriver_D1FBDFA6: 0xD1FBDFA6
          SceThreadmgrForDriver_D26BFF26: 0xD26BFF26
          SceThreadmgrForDriver_D7455187: 0xD7455187
          SceThreadmgrForDriver_D74F66BD: 0xD74F66BD
          SceThreadmgrForDriver_D7AF2E58: 0xD7AF2E58
          SceThreadmgrForDriver_DBB77032: 0xDBB77032
          SceThreadmgrForDriver_E0C7BCBB: 0xE0C7BCBB
          SceThreadmgrForDriver_E2B57231: 0xE2B57231
          SceThreadmgrForDriver_E6D80698: 0xE6D80698
          SceThreadmgrForDriver_E938FB20: 0xE938FB20
          SceThreadmgrForDriver_E9E50096: 0xE9E50096
          SceThreadmgrForDriver_F2C9DC97: 0xF2C9DC97
          SceThreadmgrForDriver_F5074173: 0xF5074173
          SceThreadmgrForDriver_F8A6013B: 0xF8A6013B
          SceThreadmgrForDriver_F96FE0D5: 0xF96FE0D5
          SceThreadmgrForDriver_FD6150D5: 0xFD6150D5
          SceThreadmgrForDriver_FD87586C: 0xFD87586C
          SceThreadmgrForDriver_FDC044AC: 0xFDC044AC
          SceThreadmgrForDriver_FF8DA217: 0xFF8DA217
          SceThreadmgrForKernel_33E85E9E: 0x33E85E9E
          sceKernelAllocateKTLS: 0xB645C7EF
          sceKernelCancelAlarm: 0x44CCF310
          sceKernelCancelCallback: 0xC040EC1C
          sceKernelCancelEvent: 0xB6FA8305
          sceKernelCancelEventFlag: 0xEA211225
          sceKernelCancelEventWithSetPattern: 0xE5CAD3E2
          sceKernelCancelMsgPipe: 0x9D6A2311
          sceKernelCancelMutex_089: 0x7204B846
          sceKernelCancelRWLock: 0x7A4EF925
          sceKernelCancelSema: 0x8760C8ED
          sceKernelCancelTimer: 0xF285C94F
          sceKernelChangeActiveCpuMask: 0x001173F8
          sceKernelChangeCurrentThreadAttr: 0x751C9B7A
          sceKernelChangeThreadCpuAffinityMask: 0x6D0733A8
          sceKernelChangeThreadPriority: 0xDA1544D1
          sceKernelChangeThreadPriority2: 0x63DAB420
          sceKernelChangeThreadPriorityAndCpuAffinityMask: 0x3857C94E
          sceKernelChangeThreadSuspendStatus: 0x04C6764B
          sceKernelChangeThreadVfpException: 0xF4C81683
          sceKernelCheckCallback: 0xE53E41F6
          sceKernelCheckWaitableStatus: 0xD9BD74EB
          sceKernelClearEvent: 0x9C335818
          sceKernelClearEventFlag: 0x4F1DA3BE
          sceKernelCloseEventFlag: 0x71ECB352
          sceKernelCountWaitingThreadsProc: 0x54E1AF04
          sceKernelCreateCallback: 0x1C41614C
          sceKernelCreateCond: 0xDB6CD34A
          sceKernelCreateEventFlag: 0x4336BAA4
          sceKernelCreateMsgPipe: 0xBF631145
          sceKernelCreateMutex: 0xFBAA026E
          sceKernelCreateRWLock: 0x04150799
          sceKernelCreateRemoteThread: 0xC8E57BB4
          sceKernelCreateSema: 0x30E93C31
          sceKernelCreateSimpleEvent: 0x357A8177
          sceKernelCreateThread: 0xC6674E7D
          sceKernelCreateTimer: 0x90656C98
          sceKernelDebugResumeThread: 0xEC8343DF
          sceKernelDebugSuspendThread: 0xFB3706CB
          sceKernelDeleteCallback: 0x3A7E17F6
          sceKernelDeleteCond: 0xAEE0D27C
          sceKernelDeleteMsgPipe: 0xB3453F88
          sceKernelDeleteMutex: 0x0A912340
          sceKernelDeleteRWLock: 0x32452017
          sceKernelDeleteSema: 0x16A35E58
          sceKernelDeleteSimpleEvent: 0x2BDE3B40
          sceKernelDeleteThread: 0xAC834F3F
          sceKernelExitDeleteThread: 0x1D17DECF
          sceKernelExitThread: 0x0C8A38E1
          sceKernelGetCallbackCount: 0x0892D8DF
          sceKernelGetCurrentThreadUnkInfo: 0x332E127C
          sceKernelGetCurrentThreadVfpException: 0x14F8167C
          sceKernelGetEventFlagInfo: 0x612277C9
          sceKernelGetEventPattern: 0x0C6BCB8C
          sceKernelGetLwCondInfo: 0xC2AFFBD0
          sceKernelGetLwMutexInfo: 0x15287EF6
          sceKernelGetLwMutexInfoAllProc: 0x069D8A20
          sceKernelGetMsgPipeInfo: 0x207E0E18
          sceKernelGetMutexInfoAllProc: 0x2322A2F3
          sceKernelGetMutexInfo_089: 0x69B78A12
          sceKernelGetProcWorkqueueInfoVector: 0x8C8A76EF
          sceKernelGetProcWorktaskInfoVector: 0xB4CED111
          sceKernelGetProcessId: 0x9DCB4B7A
          sceKernelGetProcessIdFromTLS: 0xFA54D49A
          sceKernelGetRWLockInfo: 0x374C3267
          sceKernelGetRWLockInfoAllProc: 0x6624E612
          sceKernelGetSemaInfo: 0xC99DCF0D
          sceKernelGetTHBP: 0x453B764A
          sceKernelGetThreadCpuAffinityMask: 0x83DC703D
          sceKernelGetThreadCpuRegisters: 0x5022689D
          sceKernelGetThreadCurrentPriority: 0x01414F0B
          sceKernelGetThreadExitStatus: 0x70131EA5
          sceKernelGetThreadId: 0x59D06540
          sceKernelGetThreadIdList: 0xEA7B8AEF
          sceKernelGetThreadInfo: 0x283807E2
          sceKernelGetThreadInfoInternal: 0xDD8D9429
          sceKernelGetThreadStackFreeSize: 0x7B278A0B
          sceKernelGetThreadTLSAddr: 0x66EEA46A
          sceKernelGetThreadmgrUIDClass: 0x0A20775A
          sceKernelGetTimerBase: 0xD41F53D4
          sceKernelGetTimerBaseWide: 0xA6D11DD3
          sceKernelGetTimerEventRemainingTime: 0x3634FFE6
          sceKernelGetTimerTime: 0xCB795E13
          sceKernelGetTimerTimeWide: 0xC1286004
          sceKernelGetUserThreadId: 0xF311808F
          sceKernelGetVfpRegisterForDebugger: 0x5CDE387A
          sceKernelGetWaitingThreadList: 0xB5C782A3
          sceKernelGetWorkqueueCreateInfo: 0xB92709C4
          sceKernelGetWorkqueueInfoVector: 0x920EA1CA
          sceKernelGetWorktaskCreateInfo: 0x0B604A3C
          sceKernelGetWorktaskInfoVector: 0xE605ED7A
          sceKernelIsThreadDebugSuspended: 0xA0B1AB21
          sceKernelIsUserModeThread: 0x91382762
          sceKernelLockMutexCB_089: 0xD06F2886
          sceKernelLockMutex_089: 0x16AC80C5
          sceKernelNotifyCallback: 0xC3E00919
          sceKernelPMonSetControlRegister: 0x1AAFA818
          sceKernelPMonSetUserEnableRegister: 0x5053B005
          sceKernelPollEvent: 0xD08C71C6
          sceKernelPollEventFlag: 0x76C6555B
          sceKernelPollSema: 0x4FDDFE24
          sceKernelPulseEvent: 0x2427C81B
          sceKernelPulseEventWithNotifyCallback: 0x714A107A
          sceKernelReceiveMsgPipeVector: 0xDA1F256B
          sceKernelReceiveMsgPipeVectorCB: 0xDA5C9AC6
          sceKernelRegisterCallbackToEvent: 0x832A7E0C
          sceKernelRegisterTimer: 0xC58DF384
          sceKernelRegisterTimerWithOpt: 0x10517330
          sceKernelSendMsgPipeVector: 0x67DD3BAD
          sceKernelSetCpuRegisterForDebugger: 0x64E89DE9
          sceKernelSetEvent: 0x9EA3A45C
          sceKernelSetEventFlag: 0xD4780C3E
          sceKernelSetEventWithNotifyCallback: 0xB7DF3EDF
          sceKernelSetProcessIdToTLS: 0x0486F239
          sceKernelSetTHBP: 0x385831A1
          sceKernelSetThreadAccessLevel: 0x02EEDF17
          sceKernelSetTimerEvent: 0x92A3DCDD
          sceKernelSetTimerTime: 0xD978D16F
          sceKernelSetTimerTimeWide: 0x85195A16
          sceKernelSetVfpRegisterForDebugger: 0x49A0B679
          sceKernelSignalCond: 0xAC616150
          sceKernelSignalCondAll: 0x6EC78CD0
          sceKernelSignalCondTo: 0x61533DA9
          sceKernelSignalSema: 0xD270498B
          sceKernelStartThread_089: 0x21F5419B
          sceKernelStartTimer: 0x84C4CE4D
          sceKernelStopTimer: 0x474F214B
          sceKernelTryLockFastMutex: 0x741F4707
          sceKernelTryLockMutex_089: 0x270993A6
          sceKernelTryLockReadRWLock: 0xFC2B5A50
          sceKernelTryLockWriteRWLock: 0xA96F2E5A
          sceKernelTryReceiveMsgPipeVector: 0xCE09221A
          sceKernelTrySendMsgPipeVector: 0x4CF1BE58
          sceKernelUnlockMutex_089: 0x1E82E5D0
          sceKernelUnlockReadRWLock: 0xDE1B9EEE
          sceKernelUnlockWriteRWLock: 0x94A73797
          sceKernelUnregisterCallbackFromEvent: 0x2E48D81C
          sceKernelUnregisterCallbackFromEventAll: 0x8DADBD16
          sceKernelUnregisterThreadEventHandler: 0x2C8ED6F0
          sceKernelWaitCond: 0xCC7E027D
          sceKernelWaitEvent: 0xC529EA32
          sceKernelWaitEventCB: 0x360C655C
          sceKernelWaitEventFlag: 0x0C1D3F20
          sceKernelWaitEventFlagCB: 0x8A35F714
          sceKernelWaitSema: 0x3C8B55A9
          sceKernelWaitSemaCB: 0xF55E4D86
          sceKernelWaitThreadEnd: 0x3E20216F
          sceKernelWaitThreadEndCB: 0x9EF4F62C
          sceKernelWaitWorktask: 0x12FC0FAB
          sceKernelWaitWorktask2: 0xB247EC4B
*/

int _sceKernelExtendKernelStackWide(SceSize stackSize, int (* f)(void *argp), void *argp);
int sceKernelExtendKernelStackWide(SceSize stackSize, int (* f)(void *argp), void *argp);


typedef struct SceKernelFastMutex {
	char data[0x40];
} SceKernelFastMutex;

int sceKernelInitializeFastMutex(SceKernelFastMutex *mutex, const char* name, SceUInt32 attr, void *opt);
int sceKernelFinalizeFastMutex(SceKernelFastMutex *mutex);
int sceKernelLockFastMutex(SceKernelFastMutex *mutex);
int sceKernelUnlockFastMutex(SceKernelFastMutex *mutex);


SceUInt32 sceKernelGetSystemTimeLow(void);
SceUInt64 sceKernelGetSystemTimeWide(void);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_THREADMGR_H_ */
