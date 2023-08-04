
#ifndef _PSP2_KERNEL_VFS_VNVOPS_H_
#define _PSP2_KERNEL_VFS_VNVOPS_H_


#include <psp2kern/types.h>
#include <psp2kern/io/stat.h>
#include "vfs.h"


typedef struct SceVfsNode SceVfsNode;
typedef struct SceVfsFileObject SceVfsFileObject;
typedef struct SceVfsPath SceVfsPath;

/* vop function */
int ksceVopOpen(SceVfsNode *pNode, SceVfsPath *file_info, int flags, SceVfsFileObject *pVfsFileObject);
int ksceVopCreate(SceVfsNode *pNode, SceVfsNode **ppNewNode, SceVfsPath *file_info, int flags, int mode);
int ksceVopClose(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject);
int ksceVopLookup(SceVfsNode *pNode, SceVfsNode **ppNewNode, SceVfsPath *path_info, SceUInt32 flags);
int ksceVopRead(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject, void *data, SceSize nbyte, SceSize *pResult);
int ksceVopWrite(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject, const void *data, SceSize nbyte, SceSize *pResult);
SceOff ksceVopLseek(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject, SceOff offset, int where);

int ksceVopIoctl(SceVfsNode *pNode, SceVfsFileObject *pVfsObject, int cmd, const void *indata, SceSize inlen, void *outdata, SceSize outlen);
int ksceVopRemove(SceVfsNode *pNode, SceVfsNode *pNode2, SceVfsPath *file_info, SceUInt32 flags); // SceIofilemgrForDriver_DC1E7EE4
int ksceVopMkdir(SceVfsNode *pNode,SceVfsNode **ppNewNode, SceVfsPath *file_info, int mode);
int ksceVopRmdir(SceVfsNode *pNode, SceVfsNode *pNode2, SceVfsPath *file_info);

int ksceVopDopen(SceVfsNode *pNode, SceVfsPath *file_info, SceVfsFileObject *pVfsFileObject);
int ksceVopDclose(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject);
int ksceVopDread(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject, SceIoDirent *dir);

int ksceVopGetstat(SceVfsNode *pNode, SceVfsPath *file_info, SceIoStat *stat);
int ksceVopChstat(SceVfsNode *pNode, SceVfsPath *file_info, SceIoStat *stat, int bit);

/*
 * pNode  - maybe old parent node
 * pNode2 - rename old node
 * pNode3 - unknown
 */
int ksceVopRename(SceVfsNode *pNode, SceVfsNode *pNode2, SceVfsPath *file_info_old, SceVfsNode *node3, SceVfsNode **ppNewNode, SceVfsPath *file_info_new);
int ksceVopPread(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject, void *data, SceSize nbyte, SceOff offset, SceSize *pResult);
int ksceVopPwrite(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject, const void *data, SceSize nbyte, SceOff offset, SceSize *pResult);
int ksceVopInactive(SceVfsNode *pNode);
int ksceVopSync(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject, int flags);
int ksceVopGetStateByFd(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject, SceIoStat *stat);
int ksceVopChstatByFd(SceVfsNode *pNode, SceVfsFileObject *pVfsFileObject, SceIoStat *stat, int bit);

int sceVopWhiteout(SceVfsNode *local_e4, SceVfsNode *local_e0, SceVfsPath *file_info_old, SceVfsPath *file_info_new);


#endif // _PSP2_KERNEL_VFS_VNVOPS_H_
