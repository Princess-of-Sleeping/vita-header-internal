
#ifndef _PSP2_KERNEL_SYSMEM_UID_CLASS_H_
#define _PSP2_KERNEL_SYSMEM_UID_CLASS_H_

#include <vita/shared/types.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef int (* SceClassCallback)(void *item);

typedef struct SceClass { // size is 0x2C-bytes
	struct SceClass *next;
	struct SceClass *root;
	struct SceClass *prev;
	const char *name;
	struct SceClass *subclass;
	unsigned int attributes;
	SceUInt16 itemsize;
	SceUInt16 itemsize_aligned;
	unsigned int unk1C;
	SceClassCallback create_cb;
	SceClassCallback destroy_cb;
	SceUInt32 magic; // 0xABCE9DA5
} SceClass;

/*
          sceKernelCreateClass: 0x61317102
          sceKernelGetUIDClass: 0x85336A1C
*/


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_SYSMEM_UID_CLASS_H_ */
