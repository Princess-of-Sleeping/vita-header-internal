
#ifndef _PSP2_KERNEL_DEBUG_H_
#define _PSP2_KERNEL_DEBUG_H_

#include <vita/shared/types.h>


#ifdef __cplusplus
extern "C" {
#endif


int sceKernelGetDebugPADramRange(SceUIntPtr *address, SceSize *length);
int sceKernelIsVAWithinDebugPADramRange(const void *pVA);


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

/*
          SceSysmemForDriver_8C43B052: 0x8C43B052
          SceSysmemForDriver_987EE587: 0x987EE587
*/



/*
          sceKernelLockRange: 0x59A4402F
          sceKernelLockRangeProc: 0x659586BF
          sceKernelLockRangeWithPerm: 0xBC0A1D60
          sceKernelUnlockRange: 0x75C70DE0
          sceKernelUnlockRangeProc: 0xA8525B06
          sceKernelUnlockRangeWithPerm: 0x22CBE925

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

          sceKernelCountFillValue64FromUser: 0xBB3B02C2
          sceKernelCountFillValue64FromUserProc: 0xE83855FD
          sceKernelCountFillValueFromUser: 0xBDA6E42B
          sceKernelCountFillValueFromUserProc: 0x8334454F

          sceKernelProcessGetContext: 0x2ECF7944
          sceKernelProcessSwitchContext: 0x2D711589

          sceKernelCopyFromUser: 0xBC996A7A
          sceKernelCopyFromUserProc: 0x605275F8
          sceKernelCopyToUser: 0x6D88EF8A
          sceKernelCopyToUserProc: 0x6B825479
          sceKernelProcStrncpyFromUser: 0x75AAF178
          sceKernelProcStrncpyToUser: 0xFED82F2D
          sceKernelProcStrnlenUser: 0x9929EB07
          sceKernelProcUserCopy: 0x8E086C33
          sceKernelStrncpyFromUser: 0xDB3EC244
          sceKernelStrncpyToUser: 0x80BD6FEB
          sceKernelStrnlenUser: 0xB429D419
          sceKernelUserCopy: 0x1BD44DD5
*/

SceUID sceKernelUserMap(const char *name, int permission, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);
SceUID sceKernelUserMapWithFlags(const char *name, int permission, int type, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);
SceUID sceKernelProcUserMap(SceUID pid, const char *name, int permission, const void *user_buf, SceSize size, void **kernel_page, SceSize *kernel_size, SceUInt32 *kernel_offset);
int sceKernelUserUnmap(SceUID umap);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_DEBUG_H_ */
