
#ifndef _PSP2_KERNEL_SYSMEM_HEAP_H_
#define _PSP2_KERNEL_SYSMEM_HEAP_H_

#include <shared/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
          sceKernelCreateHeap: 0x9328E0E8
          sceKernelDeleteHeap: 0xD6437637
          sceKernelAllocHeapMemory: 0x7B4CB60A
          sceKernelAllocHeapMemoryFromGlobalHeap: 0x7750CEA7
          sceKernelAllocHeapMemoryFromGlobalHeapWithOpt: 0x0B4ED16A
          sceKernelAllocHeapMemoryWithOpt: 0xB415B5A8
          sceKernelAllocHeapMemoryWithOption: 0x49D4DD9B
          sceKernelFreeHeapMemory: 0x3EBCE343
          sceKernelFreeHeapMemoryFromGlobalHeap: 0xFB817A59
          sceKernelPrintHeapSegmentList: 0x2EE50533
          sceKernelAlloc: 0xC0A4D2F3
          sceKernelAllocWithOpt: 0xA2CD1697
          sceKernelFree: 0xABAB0FAB
          sceKernelGetHeapInfo: 0x91733EF4
          sceKernelGetHeapInfoByPtr: 0x68451777
*/


SceSize SceSysmemForKernel_60735311(void *ptr); // get memory size
int SceSysmemForKernel_0B36F7F9(SceUID heapid, int v); // HeapEnableDiableMode with 1
int SceSysmemForKernel_71869119(SceUID heapid, int v); // HeapEnableDiableMode with 0

int SceSysmemForKernel_FDC0EA11(SceUID heapid, int a2, int a3); // realloc?

int sceKernelShrinkHeap(SceUID heapid);

int sceKernelVerifyHeap(SceUID heapid, void *ptr);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_SYSMEM_HEAP_H_ */
