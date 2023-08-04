
#ifndef _PSP2_KERNEL_VFS_SUBR_H_
#define _PSP2_KERNEL_VFS_SUBR_H_


#include <psp2kern/types.h>
#include "vfs.h"
#include "vop.h"



SceUID sceVfsAllocateFile(SceVfsNode *pNode, SceVfsFileObject **ppObject, const char *name);
int sceVfsFreeFile(SceVfsNode *pNode, SceUID fd);

/*
 * Add new vfs
 */
int ksceVfsAddVfs(SceVfsAddParam *pParam);

/*
 * Delete registered vfs
 */
int ksceVfsDeleteVfs(const char *fs, SceVfsAddParam **pParam);

int sceVfsLockVnodeForDriver(SceVfsNode *vp);
int sceVfsUnlockVnodeForDriver(SceVfsNode *vp);

int ksceVfsGetNewNode(SceVfsMount *mount, const SceVopTable *pTable, int a3, SceVfsNode **ppNode);
int ksceVfsFreeVnode(SceVfsNode *pNode);


SceVfsAddParam *vfs_get_param(const char *name);


#endif // _PSP2_KERNEL_VFS_SUBR_H_
