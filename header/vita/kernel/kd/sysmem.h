
#ifndef _PSP2_KERNEL_SYSMEM_H_
#define _PSP2_KERNEL_SYSMEM_H_

#include <vita/shared/types.h>


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
*/


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


SceInt32 sceKernelCountFillValue64FromUser(const void *ptr, SceUInt64 value, SceSize range);
SceInt32 sceKernelCountFillValue64FromUserProc(SceUID pid, const void *ptr, SceUInt64 value, SceSize range);
SceInt32 sceKernelCountFillValueFromUser(const void *ptr, SceUInt32 value, SceSize range);
SceInt32 sceKernelCountFillValueFromUserProc(SceUID pid, const void *ptr, SceUInt32 value, SceSize range);


SceUID sceKernelUserMap(const char *name, int permission, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);
SceUID sceKernelUserMapWithFlags(const char *name, int permission, int type, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);
SceUID sceKernelProcUserMap(SceUID pid, const char *name, int permission, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);
int sceKernelUserUnmap(SceUID umap);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_SYSMEM_H_ */
