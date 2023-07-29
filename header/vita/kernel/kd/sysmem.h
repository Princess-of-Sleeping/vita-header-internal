
#ifndef _PSP2_KERNEL_SYSMEM_H_
#define _PSP2_KERNEL_SYSMEM_H_

#include <psp2kern/types.h>


#ifdef __cplusplus
extern "C" {
#endif


int sceKernelGetDebugPADramRange(SceUIntPtr *address, SceSize *length);
int sceKernelIsVAWithinDebugPADramRange(const void *pVA);


int sceKernelLockRange(const void *base, SceSize range);
int sceKernelLockRangeProc(SceUID pid, const void *base, SceSize range);
int sceKernelLockRangeWithMode(SceUInt32 mode, const void *base, SceSize size);
int sceKernelUnlockRange(const void *base, SceSize range);
int sceKernelUnlockRangeProc(SceUID pid, void *base, SceSize range);
int sceKernelUnlockRangeWithMode(SceUInt32 mode, void *base, SceSize range);

#define SCE_KERNEL_MEMBLOCK_PARTIAL_CHECK_ALLOCATED  (0x1)
#define SCE_KERNEL_MEMBLOCK_PARTIAL_CHECK_FREE       (0x2)
#define SCE_KERNEL_MEMBLOCK_PARTIAL_CHECK_MAPPED     (0x4)
#define SCE_KERNEL_MEMBLOCK_PARTIAL_CHECK_ALLOCNOMAP (0x8)
#define SCE_KERNEL_MEMBLOCK_PARTIAL_CHECK_MAPPED_RW  (0x10)
#define SCE_KERNEL_MEMBLOCK_PARTIAL_CHECK_MAPPED_RO  (0x20)

/*
 * Alloed flags is SCE_KERNEL_MEMBLOCK_PARTIAL_CHECK_ALLOCATED|SCE_KERNEL_MEMBLOCK_PARTIAL_CHECK_FREE|SCE_KERNEL_MEMBLOCK_PARTIAL_CHECK_ALLOCNOMAP
 */
int SceSysmemForDriver_13805CA8(SceUID memid, void *vbase, SceSize vsize, int flags);

/*
 * Alloed flags is SCE_KERNEL_MEMBLOCK_PARTIAL_CHECK_FREE
 */
int SceSysmemForDriver_16713BE8(SceUID memid, void *vbase, SceSize vsize, int flags);

int SceSysmemForDriver_4C584B29(SceUID memid, void *vbase, SceSize vsize, int flags);
int SceSysmemForDriver_6C76AD89(SceUID memid, void *vbase, SceSize vsize, int flags);
int SceSysmemForDriver_8C43B052(SceUID memid, void *vbase, SceSize vsize, int flags);

int sceKernelMemBlockGetVirPage(SceUID memid, void *a2);
int sceKernelMemBlockToPAVector(SceUID memid, void *pPAV);

int SceSysmemForKernel_A88F6D88(SceUID memid, void *a2);
int SceSysmemForKernel_64133268(SceUID uid);
int SceSysmemForKernel_61C2AA52(SceUInt32 memtype); // get code

/*
          sceKernelAllocMemBlockForKernel: 0xC94850C9
          sceKernelAllocMemBlockWithInfoForKernel: 0xD44F464D
          sceKernelFreeMemBlock: 0x009E1C61
          sceKernelGetMemBlockBase: 0xA841EDDA
          sceKernelGetMemBlockInfo: 0xA73CFFEF
          sceKernelGetMemBlockInfoEx: 0x24A99FFF
          sceKernelGetMemBlockMappedBase: 0x0B1FD5C3
          sceKernelGetMemBlockMemtypeByAddr: 0xF3BBE2E1
          sceKernelGetMemBlockPARange: 0x98C15666
          sceKernelGetMemBlockPAVector: 0x19A51AC7
          sceKernelGetMemBlockProcess: 0x1EFC96EA
          sceKernelGetMemBlockVBase: 0xB81CF0A3
          sceKernelIncRefCountMemBlock: 0xEAF3849B
          sceKernelDecRefCountMemBlock: 0xF50BDC0C
          sceKernelFindMemBlockByAddr: 0x8A1742F6
          sceKernelFindProcMemBlockByAddr: 0x857F1D5A
          sceKernelGetPhysicalMemoryType: 0x0AAA4FDD
          sceKernelIsAccessibleRange: 0x9C78064C
          sceKernelIsAccessibleRangeProc: 0x9F6E45E3
          sceKernelIsEqualAccessibleRangeProcBySW: 0xF4AD89D8
          sceKernelMapBlockUserVisibleWithFlag: 0x04059C4B
          sceKernelMemBlockGetSomeSize: 0x78337B62
          sceKernelMemBlockType2Memtype: 0x20C811FA
          sceKernelMemBlockTypeGetPrivileges: 0x6A0792A3
          sceKernelMemBlockTypeGetUnknown: 0xCB0F3A33
          sceKernelPartialRemapMemBlock: 0xDFE2C8CB
          sceKernelPartitionMapMemBlock: 0x58D21746
          sceKernelUnmapMemBlock: 0xFFCD9B60

          sceKernelProcessGetContext: 0x2ECF7944
          sceKernelProcessSwitchContext: 0x2D711589


          SceSysmemForKernel_01DE3AB7: 0x01DE3AB7
          SceSysmemForKernel_07FEBBCA: 0x07FEBBCA
          SceSysmemForKernel_080BA2F3: 0x080BA2F3
          SceSysmemForKernel_114E6476: 0x114E6476
          SceSysmemForKernel_131CEF52: 0x131CEF52
          SceSysmemForKernel_153A08A0: 0x153A08A0


          sceKernelAllocMemBlockByCommand: 0xCA91B9D5

          sceKernelAllocPartitionMemBlock: 0x5FFE4B79

          sceKernelGetMemBlockInfoAll: 0xFEF54604
          sceKernelGetMemBlockType: 0x289BE3EC

          sceKernelAllocSimpleMemBlock: 0xF81F4672
          sceKernelFreeSimpleMemBlock: 0xA1FFA2C9
          sceKernelGetSimpleMemBlockBase: 0x0A8D14EC
          sceKernelGetMemBlockInfoSimple: 0x2364A170
          int SceSysmemForKernel_43DFCE89(void *info); // get fifo?

          sceKernelFindClassByName: 0x62989905
          sceKernelGetUIDAddressSpaceClass: 0xAF180A3F
          sceKernelGetUIDDLinkClass: 0xC105604E
          sceKernelGetUIDHeapClass: 0x4CCA935D
          sceKernelGetUIDMemBlockClass: 0xAF729575

          sceKernelNameHeapGetInfo: 0xE443253B
          sceKernelNameHeapInsert: 0x08AB3DAE

          sceKernelCreateObjectHeap: 0x36830F46
          sceKernelObjectHeapSetResourceLimit: 0x98E6905B
          sceKernelObjectHeapSetResourceLimitAll: 0x5409397F
          int SceSysmemForKernel_7FDF483A(); // sceKernelObjectHeapAlloc
          int SceSysmemForKernel_571660AA(void *ctx, void *obj); // free

          sceKernelSysmemCleaner: 0x43E81C4B
          sceKernelSysmemModuleStartAfterProcessmgr: 0xE7938BFB
*/


int sceKernelVSlotMapProcMemory(SceUID pid, int a2, int a3, int a4, void *a5, void *a6);
int sceKernelVSlotUnmapProcMemory();


int sceKernelCopyFromUser(void *dst, const void *src, SceSize length);
int sceKernelCopyToUser(void *dst, const void *src, SceSize length);
int sceKernelCopyFromUserProc(SceUID pid, void *dst, const void *src, SceSize length);
int sceKernelCopyToUserProc(SceUID pid, void *dst, const void *src, SceSize length);
SceSSize sceKernelStrncpyFromUser(char *dst, const char *src, SceSize length);
SceSSize sceKernelStrncpyToUser(char *dst, const char *src, SceSize length);
SceSSize sceKernelStrnlenUser(const char *s, SceSize length);
SceSSize sceKernelProcStrncpyFromUser(SceUID pid, char *dst, const char *src, SceSize length);
SceSSize sceKernelProcStrncpyToUser(SceUID pid, char *dst, const char *src, SceSize length);
SceSSize sceKernelProcStrnlenUser(SceUID pid, const char *s, SceSize length);
int sceKernelUserCopy(void *dst, const char *src, SceSize length);
int sceKernelProcUserCopy(SceUID pid, void *dst, const char *src, SceSize length);
int sceKernelCopyToUserDomain(void *dst, const void *src, SceSize length);
int sceKernelCopyToUserTextDomain(void *dst, const void *src, SceSize length);
int sceKernelCopyToUserProcTextDomain(SceUID pid, void *dst, const void *src, SceSize length);
int sceKernelCopyToUserProcTextDomainForDBGP(SceUID pid, void *dst, const void *src, SceSize length);
int SceSysmemForKernel_FCB5745A(void *dst, SceUInt32 value, SceInt32 nwords);


SceInt32 sceKernelCountFillValue64FromUser(const void *ptr, SceUInt64 value, SceSize range);
SceInt32 sceKernelCountFillValue64FromUserProc(SceUID pid, const void *ptr, SceUInt64 value, SceSize range);
SceInt32 sceKernelCountFillValueFromUser(const void *ptr, SceUInt32 value, SceSize range);
SceInt32 sceKernelCountFillValueFromUserProc(SceUID pid, const void *ptr, SceUInt32 value, SceSize range);


SceUID sceKernelUserMap(const char *name, int permission, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);
SceUID sceKernelUserMapWithFlags(const char *name, int permission, int type, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);
SceUID sceKernelProcUserMap(SceUID pid, const char *name, int permission, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);
int sceKernelUserUnmap(SceUID umap);



void *SceSysmemForKernel_68CB9266(int a1); // get fixedheap context?
void *SceSysmemForKernel_C8672A3D(void *a1); // AllocFixedHeap

// sysroot?
int SceSysmemForKernel_ECC68E7B(SceUID guid, void *a2); // get something


// nameheap
int SceSysmemForKernel_EC1293D2(int a1, int a2, void *a3);
int SceSysmemForKernel_B543A23C();
int SceSysmemForKernel_9C7B62AB(char *name, int a2); // delete name?


// unknown
int SceSysmemForKernel_E68A9F1B(int a1, void *a2); // get something
int SceSysmemForKernel_C6F04370(void); // init something
int SceSysmemForKernel_C0BF149E(int a1, int a2, void *a3); // get something
int SceSysmemForKernel_BF0294E4(void); // get something
int SceSysmemForKernel_BC2E2B2B(void *a1); // set something
int SceSysmemForKernel_B8D769C6(void *a1, void *pInfo); // get something
int SceSysmemForKernel_B339A865(void);
int SceSysmemForKernel_AD5A83E3(SceUID guid, int level, void *a3, void *a4); // get something
int SceSysmemForKernel_A504BA60();
SceUInt32 SceSysmemForKernel_942D15FC(const char *name, SceSize namelen, int a3); // get namehash?
int SceSysmemForKernel_8B07BB52(void); // checks some state?
int SceSysmemForKernel_7FD757FE();
int SceSysmemForKernel_7DC46969(void);
int SceSysmemForKernel_72E7BFAC(int a1); // set something
int SceSysmemForKernel_6427560F(int index, int a2);
int SceSysmemForKernel_48D87E17(); // get some info vector
SceBool SceSysmemForKernel_48750A5A(void *a1, void *a2); // search a2 obj from a1
int SceSysmemForKernel_3EC2345B(void *a1, int a2);
int SceSysmemForKernel_3B75CBED(void); // get something
int SceSysmemForKernel_3203AE64();
int SceSysmemForKernel_2791F109(void); // get something
int SceSysmemForKernel_2658EE0A(int a1); // beta only
int SceSysmemForKernel_22A26637();
void *SceSysmemForKernel_22708F14();
int SceSysmemForKernel_21285F40(); // createclass
int SceSysmemForKernel_1E11F41D(void);
int SceSysmemForKernel_17F1AA22(int a1); // beta only


// VM
int SceSysmemForKernel_D514BB56(void); // get GetVMState


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_SYSMEM_H_ */
