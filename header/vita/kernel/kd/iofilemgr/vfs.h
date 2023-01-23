
#ifndef _PSP2_KERNEL_VFS_H_
#define _PSP2_KERNEL_VFS_H_


#include <psp2kern/kernel/threadmgr.h>
#include <psp2kern/kernel/sysmem.h>
#include "vop.h"


typedef struct SceVfsNode SceVfsNode;
typedef struct SceVfsFileObject SceVfsFileObject;
typedef struct SceVfsMount SceVfsMount;
typedef struct SceVfsMount2 SceVfsMount2;
typedef struct SceVfsAddParam SceVfsAddParam;


typedef struct SceVfsPath { //size is 0xC-bytes
	const char *name;
	SceSize name_len;
	const char *path;
} SceVfsPath;

typedef struct SceVfsopSetRootArgs { // size is 0xC-bytes
	SceVfsMount *pMount;
	int data_0x04;
	SceVfsNode *pNode;
} SceVfsopSetRootArgs;

typedef struct SceVfsDevctl {
	void *unk_0x00;
	const char *dev;
	unsigned int cmd;
	void *indata;
	SceSize inlen;
	void *outdata;
	SceSize outlen;
} SceVfsDevctl;

typedef struct SceVfsMountArgs { // size is 0x8-bytes
	SceVfsMount *pMount;
	SceVfsPath *file_info;
} SceVfsMountArgs;



typedef struct SceVfsopDecodePathElemArgs { // size is 0x1C-bytes
	SceVfsMount *pMount;   // in
	const char *path;      // in
	const char **dst_path; // out
	const char **child;    // out
	char *dst;             // inout
	SceSize dst_size;      // in
	SceSize *pResultSize;  // out
} SceVfsopDecodePathElemArgs;

typedef struct SceVfsopUmountArgs { // size is 0x8-bytes
	SceVfsMount *mnt;
	int flags;
} SceVfsopUmountArgs;

typedef struct SceVfsopInitArgs { // size is 0x4-bytes
	SceVfsAddParam *pParam;
} SceVfsopInitArgs;

typedef struct SceVfsTable { // size is 0x34-bytes
	int (* vfs_mount)(SceVfsMountArgs *argp);
	int (* vfs_umount)(SceVfsopUmountArgs *argp);
	int (* vfs_set_root)(SceVfsopSetRootArgs *argp);
	const void *vfs_get_root;
	const void *func10;
	const void *func14;
	const void *func18; // called by 0x81011b2d
	const void *func1C;
	int (* vfs_init)(SceVfsopInitArgs *argp); // Called on ksceVfsAddVfs/vfs_init
	const void *func24; // Called on ksceVfsDeleteVfs
	const void *func28;
	int (* vfs_devctl)(SceVfsDevctl *args);
	int (* vfs_decode_path_elem)(SceVfsopDecodePathElemArgs *argp);
} SceVfsTable;

typedef struct SceVfsMount { // size is 0x100-bytes
	SceUInt8 fastmutex[0x40];

	SceVfsNode *data_0x40; // base device node
	SceUID heapid;
	int data_0x48;
	int data_0x4C; // some flags. copied from (SceVfsMountParam *)->data_0x08

	int data_0x50; // some flags. copied from ((SceVfsMountParam *)->data_0x0C & 0xFFFFF)
	SceVfsNode *pNodeTop;
	SceUInt32 nNodes;
	const SceVfsAddParam *pVfsAddParam;

	SceInt32 mntRefCount;
	int openedEntryNum;
	int data_0x68;
	int data_0x6C;
	void *data_0x70;
	void *data_0x74;
	struct SceVfsMount *next;
	const SceVfsMount2 *pVfsMount2;

	// offset: 0x80
	char device[0x40];
	int data_0xC0;
	void *data_0xC4; // pData? used for SceExfatfs 0x230 ctx
	void *data_0xC8; // pointer to mutex_id (fd_lock_ptr)
	void *prev;      // pointer to data_0xE0

	SceUID mutex_id;
	SceUID cond_id;
	int data_0xD8;
	int data_0xDC;

	int data_0xE0;
	int data_0xE4;
	void *data_0xE8;
	void *data_0xEC;

	int data_0xF0;
	int data_0xF4;
	int data_0xF8;
	int data_0xFC;
} SceVfsMount;

// real name is ncache (name cache)
typedef struct SceVfsNCache { // size is 0x20-bytes
	struct SceVfsNCache *data_0x00; // next cache on current dir
	struct SceVfsNCache *parent;
	struct SceVfsNCache *data_0x08; // link with per mount all cache
	struct SceVfsNCache *child;
	SceVfsNode *pNode;
	int state;
	int name_len; // len
	char *name;
} SceVfsNCache;

typedef struct SceVfsNode { // size is 0x100-bytes
	SceInt32  waiter;
	SceUID    ownerId;
	SceUInt32 recursiveCount;
	SceUID    waitId;
	SceUInt32 waitPattern;
	SceUInt32 padding_0x14[11];

	struct { // offset:0x40 size is 0x98-bytes
		const SceVopTable *ops;
		SceUInt32 nodeInf;
		void *nodeData;
		SceVfsMount *mnt;

		// offset 0x50
		struct SceVfsNode *dd; // parent vnode
		struct SceVfsNode *pNextNode; // All node link of mount
		SceUInt32 refCount;
		const SceVfsTable *vfs_table;

		short *path;  // userdata. Outside of the control for vfs.
		uint32_t unk_64;
		uint32_t unk_68;
		SceUID allocator;

		SceVfsNCache *ncache;
		SceUInt32 state;
		SceUInt32 type; // 1:file 2:dir
		SceUInt32 unk_7C;

		// offset: 0x80
		SceOff size;
		SceUInt32 st_attr; // aclData?
		uint32_t unk_8C;   // aclData?

		SceVfsFileObject *fdList;
		SceUInt32 fdNum;
		struct SceVfsNode *child_node; // child node with deeper level of i/o implementation?
		uint32_t unk_9C;

		uint8_t data2[0x30];

		uint32_t unk_D0;               // devMajor.w.unk_4E
		uint32_t unk_D4;
	} core;

	uint8_t padding_0xD8[0x28];
} SceVfsNode;

typedef struct SceVfsFileObject { // size is 0x40-bytes
	SceBool is_dir_handler;
	int flags;                         // open flags
	SceOff offset;
	int flags2;                        // 0x10 some flags
	SceUID pid;
	SceVfsNode *node;                  // 0x18
	struct SceVfsFileObject *prev_obj;
	void *device_handle;               //0x20 - for Sdstor this will be sd_stor_device_handle*
	uint16_t unk24;
	uint8_t unk26;
	uint8_t unk27;
	void *fd_lock_ptr;                 // 0x28
	int devMinor;                      // 0x2C
	void *file_info; // size is 0x20-bytes. If have Dipsw 0xD2, only.
	char unk34[12];
} SceVfsFileObject;

typedef struct SceUIDVfsFileObject {
	void *userdata;
	SceClass *sce_class; 
	SceVfsFileObject vfs_object;
} SceUIDVfsFileObject;

typedef struct SceVfsAddParam { // size is 0x20-bytes
	const SceVfsTable *pVfsTable;
	const char *vfsName;   // ex:"bsod_dummy_host_fs"/"exfat"
	SceSize vfsNameLen;
	int is_mounted;
	int data_0x10;         // ex:0x10
	const SceVopTable *pVopTable;
	int data_0x18;
	struct SceVfsAddParam *prev;
} SceVfsAddParam;

typedef struct SceVfsMount2 { // size is 0x14-bytes
	const char *assignName;
	const char *fsName;
	const char *blockdevName;
	const char *blockdevNameNoPart;
	int data_0x10;
} SceVfsMount2;


#define SCE_VFS_MOUNT_FLAG_RO (0x1000)

typedef struct SceVfsMountParam {   // size is 0x20-bytes
	const char *device;    // ex: "/host", "/dev", "/tty", "/md"
	int data_0x04;
	int data_0x08;         // ex:0x03000004

	/*
	 * flags ex:0x00008006
	 * mask 0x000000FF : device
	 *      1 : pfs
	 *      2 : unknown. another fs import?
	 *      3 : virtual device. like tty/md. Also "sdstor0:" entry.
	 *      4 : if data_0x04 != 0, success, but nop.
	 *      5 : ?
	 *      6 : host0:
	 * mask 0x0000FF00 : access?
	 *      0x1000 : Read only
	 */
	int data_0x0C;
	const char *data_0x10; // ex:"bsod_dummy_host_fs"/"exfat"
	int data_0x14;
	const SceVfsMount2 *pVfsMount2;
	int data_0x1C;
} SceVfsMountParam;

typedef struct SceVfsUmountParam {
	const char *device; // ex:"/host"
	int data_0x04;
} SceVfsUmountParam;

/* vfs function */

/*
 * Add new vfs
 */
int ksceVfsAddVfs(SceVfsAddParam *pParam);

/*
 * Delete registered vfs
 */
int ksceVfsDeleteVfs(const char *fs, SceVfsAddParam **pParam);

/*
 * Mount registered vfs
 */
int ksceVfsMount(const SceVfsMountParam *pParam);

/*
 * Unmount registered vfs
 */
int ksceVfsUnmount(const SceVfsUmountParam *pParam);

int ksceVfsGetNewNode(SceVfsMount *mount, const SceVopTable *pTable, int a3, SceVfsNode **ppNode);
int ksceVfsFreeVnode(SceVfsNode *pNode);

int sceVfsLockVnode(SceVfsNode *pNode);
int sceVfsUnlockVnode(SceVfsNode *pNode);

int ksceVfsOpDevctl(SceVfsMount *pMountInfo, const char *dev, int cmd, void *indata, SceSize inlen, void *outdata, SceSize outlen);
int ksceVfsOpDecodePathElem(SceVfsMount *pMount, const char *path, const char **dst_path, const char **child, char *dst, SceSize dst_size, SceSize *pResultSize);
int sceVfsopInit(SceVfsAddParam *pParam); // no exported
int sceVfsopUmount(SceVfsMount *mnt, int flags); // no exported

SceUID sceVfsAllocateFile(SceVfsNode *pNode, SceVfsFileObject **ppObject, const char *name);
int sceVfsFreeFile(SceVfsNode *pNode, SceUID fd);


#endif // _PSP2_KERNEL_VFS_H_
