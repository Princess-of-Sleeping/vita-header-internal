
#ifndef _PSP2_KERNEL_SYSMEM_UID_PUID_H_
#define _PSP2_KERNEL_SYSMEM_UID_PUID_H_

#include <shared/types.h>


#ifdef __cplusplus
extern "C" {
#endif



int SceSysmemForKernel_BF04FC83(); // PUIDGetPUIDVectorByGUID
int SceSysmemForKernel_9C53F457(SceUID pid, SceUID puid, void *class, void **ppObject); // PUIDReferObject2
int SceSysmemForKernel_53A2E272(SceUID pid, SceUID guid, void *opt); // UIDCreateOptCheckForPUID
int SceSysmemForKernel_22F79E82(SceUID pid, const char *name, void *opt);
/*
          scePUIDClose: 0x84A4AF5E
          scePUIDGetClass: 0xE9728A12
          scePUIDGetEntryHeapName: 0x09896EB7
          scePUIDGetObject: 0xFE6D7FAE
          scePUIDOpenByGUID: 0xBF209859
          scePUIDOpenByGUIDWithFlags: 0xCED1547B
          scePUIDOpenByName: 0x513B9DDD
          scePUIDOpenByNameWithClass: 0x8DA0BCA5
          scePUIDSetName: 0x12624884
          scePUIDtoGUID: 0x45D22597
          scePUIDtoGUIDWithClass: 0x184172B1
          scePUIDGetAttr: 0x86E83C0D
          scePUIDGetEntryInfoAll: 0x2770A7D7
          scePUIDGetInfo: 0x12ED88AE
          scePUIDGetUIDVectorByClass: 0xB16D5136
          scePUIDReferObject: 0x620E00E7
          scePUIDReleaseObject: 0x3FCA782B
*/


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_SYSMEM_UID_PUID_H_ */
