
#ifndef _PSP2_KERNEL_SYSMEM_HEAP_H_
#define _PSP2_KERNEL_SYSMEM_HEAP_H_

#include <vita/shared/types.h>


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
*/

int sceKernelShrinkHeap(SceUID heapid);

int sceKernelVerifyHeap(SceUID heapid, void *ptr);


#endif /* _PSP2_KERNEL_SYSMEM_HEAP_H_ */
