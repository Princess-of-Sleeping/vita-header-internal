
#ifndef _PSP2_KERNEL_IOFILEMGR_VOP_H_
#define _PSP2_KERNEL_IOFILEMGR_VOP_H_


#include <psp2kern/types.h>
#include <psp2kern/io/stat.h>
#include "vfs.h"


typedef struct SceVfsNode SceVfsNode;
typedef struct SceVfsFileObject SceVfsFileObject;
typedef struct SceVfsPath SceVfsPath;


typedef struct SceVopOpenArgs { // size is 0x10-bytes
	SceVfsNode *node;
	SceVfsPath *file_info;
	int flags;
	SceVfsFileObject *pVfsFileObject;
} SceVopOpenArgs;

typedef struct SceVopCreateArgs { // size is 0x14-bytes
	SceVfsNode *pNode;
	SceVfsNode **ppNewNode;
	SceVfsPath *file_info;
	int flags;
	int mode;
} SceVopCreateArgs;

typedef struct SceVopCloseArgs { // size is 0x8-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
} SceVopCloseArgs;

typedef struct SceVopLookupArgs { // size is 0x10-bytes
	SceVfsNode  *node;
	SceVfsNode **new_node; // result
	SceVfsPath *path_info;
	SceUInt32 flags;
} SceVopLookupArgs;

typedef struct SceVopReadArgs { // size is 0x10-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
	void *data;
	SceSize nbyte;
} SceVopReadArgs;

typedef struct SceVfsWrite { // size is 0x10-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
	const void *data;
	SceSize nbyte;
} SceVfsWrite;

typedef struct SceVopLseekArgs { // size is 0x14-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
	SceOff offset;
	int where;
} SceVopLseekArgs;

typedef struct SceVopIoctlArgs { // size is 0x1C-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
    int cmd;
    const void *indata;
    SceSize inlen;
    void *outdata;
    SceSize outlen;
} SceVopIoctlArgs;

typedef struct SceVopRemoveArgs { // size is 0x10-bytes
	SceVfsNode *node;
	SceVfsNode *node2;
	SceVfsPath *file_info;
	SceUInt32 flags;
} SceVopRemoveArgs;

typedef struct SceVopMkdirArgs { // size is 0x10-bytes
	SceVfsNode  *node;
	SceVfsNode **pNewNode;
	SceVfsPath *file_info;
	int mode;
} SceVopMkdirArgs;

typedef struct SceVopRmdirArgs { // size is 0xC-bytes
	SceVfsNode *node;
	SceVfsNode *node2;
	SceVfsPath *file_info;
} SceVopRmdirArgs;

typedef struct SceVopDopenAgrs { // size is 0xC-bytes
	SceVfsNode *node;
	SceVfsPath *file_info;
	SceVfsFileObject *pVfsFileObject;
} SceVopDopenAgrs;

typedef struct SceVopDcloseArgs { // size is 0x8-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
} SceVopDcloseArgs;

typedef struct SceVopDreadArgs { // size is 0xC-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
	SceIoDirent *dir;
} SceVopDreadArgs;

typedef struct SceVopStatArgs { // size is 0xC-bytes
	SceVfsNode *node;
	SceVfsPath *file_info;
	SceIoStat *stat;
} SceVopStatArgs;

typedef struct SceVopChstatArgs { // size is 0x10-bytes
	SceVfsNode *node;
	SceVfsPath *file_info;
	SceIoStat *stat;
	int bit;
} SceVopChstatArgs;

typedef struct SceVopChstatByFdArgs { // size is 0x10-bytes
	SceVfsNode *pNode;
	SceVfsFileObject *pVfsFileObject;
	SceIoStat *stat;
	SceUInt32 bit;
} SceVopChstatByFdArgs;

typedef struct SceVopStatByFdArgs { // size is 0xC-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
	SceIoStat *stat;
} SceVopStatByFdArgs;

typedef struct SceVopInactiveArgs { // size is 0x4-bytes
	SceVfsNode *node;
} SceVopInactiveArgs;

typedef struct SceVopLinkArgs { // size is 0x8-bytes
	SceVfsNode *vp;
	int a2;
} SceVopLinkArgs;

typedef struct SceVopUnlinkArgs { // size is 0x8-bytes
	SceVfsNode *vp;
	int a2;
} SceVopUnlinkArgs;

typedef struct SceVopSyncArgs { // size is 0xC-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
	int flags;
} SceVopSyncArgs;

typedef struct SceVopRenameArgs { // size is 0x18-bytes
	SceVfsNode *node;
	SceVfsNode *node2;
	SceVfsPath *file_info_old;
	SceVfsNode *node3;
	SceVfsNode **ppNewNode;
	SceVfsPath *file_info_new;
} SceVopRenameArgs;

typedef struct SceVopPreadArgs { // size is 0x18-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
    void *data;
    SceSize nbyte;
    SceOff offset;
} SceVopPreadArgs;

typedef struct SceVopPwriteArgs { // size is 0x18-bytes
	SceVfsNode *node;
	SceVfsFileObject *pVfsFileObject;
    const void *data;
    SceSize nbyte;
    SceOff offset;
} SceVopPwriteArgs;

typedef struct SceVopWhiteoutArgs { // size is 0x10-bytes
	SceVfsNode *pNode;
	SceVfsNode *pNode2;
	SceVfsPath *file_info_old;
	SceVfsPath *file_info_new;
} SceVopWhiteoutArgs;

typedef struct SceVopTable { // size is 0x74-bytes
	int (* vop_open)(SceVopOpenArgs *argp);
	int (* vop_create)(SceVopCreateArgs *argp);
	int (* vop_close)(SceVopCloseArgs *argp);
	int (* vop_lookup)(SceVopLookupArgs *argp);

	SceSSize (* vop_read)(SceVopReadArgs *argp);
	SceSSize (* vop_write)(SceVfsWrite *argp);
	SceOff (* vop_lseek)(SceVopLseekArgs *argp);
	int (* vop_ioctl)(SceVopIoctlArgs *argp);

	int (* vop_remove)(SceVopRemoveArgs *argp);
	int (* vop_mkdir)(SceVopMkdirArgs *argp);
	int (* vop_rmdir)(SceVopRmdirArgs *argp);
	int (* vop_dopen)(SceVopDopenAgrs *argp);

	int (* vop_dclose)(SceVopDcloseArgs *argp);
	int (* vop_dread)(SceVopDreadArgs *argp);
	int (* vop_get_stat)(SceVopStatArgs *argp);
	int (* vop_chstat)(SceVopChstatArgs *argp);

	int (* vop_rename)(SceVopRenameArgs *argp);
	const void *func44;                                              // sdstor op
	SceSSize (* vop_pread)(SceVopPreadArgs *argp);
	SceSSize (* vop_pwrite)(SceVopPwriteArgs *argp);
	int (* vop_inactive)(SceVopInactiveArgs *argp);
	int (* vop_link)(SceVopLinkArgs *argp);
	int (* vop_unlink)(SceVopUnlinkArgs *argp);
	int (* vop_sync)(SceVopSyncArgs *argp);
	int (* vop_fgetstat)(SceVopStatByFdArgs *argp);
	int (* vop_fchstat)(SceVopChstatByFdArgs *argp);
	int (* vop_whiteout)(SceVopWhiteoutArgs *argp);
	const void *vop_cleanup;                                         // SceIofilemgrForDriver_0F7E1718
	const void *func70;                                              // SceIofilemgrForDriver_EEAE8B51
} SceVopTable;


#endif // _PSP2_KERNEL_IOFILEMGR_VOP_H_
