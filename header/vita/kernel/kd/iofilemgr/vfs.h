
#ifndef _PSP2_KERNEL_VFS_H_
#define _PSP2_KERNEL_VFS_H_


#include <psp2kern/types.h>


typedef struct SceVfsPath { //size is 0xC-bytes
	const char *name;
	SceSize name_len;
	const char *path;
} SceVfsPath;

typedef struct SceVfsopSetRootArgs { // size is 0xC-bytes
	struct SceVfsMount *pMount;
	int data_0x04;
	struct SceVfsNode *pNode;
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
	struct SceVfsMount *pMount;
	SceVfsPath *file_info;
} SceVfsMountArgs;

typedef struct SceVfsopDecodePathElemArgs { // size is 0x1C-bytes
	struct SceVfsMount *pMount;   // in
	const char *path;      // in
	const char **dst_path; // out
	const char **child;    // out
	char *dst;             // inout
	SceSize dst_size;      // in
	SceSize *pResultSize;  // out
} SceVfsopDecodePathElemArgs;

typedef struct SceVfsopUmountArgs { // size is 0x8-bytes
	struct SceVfsMount *mnt;
	int flags;
} SceVfsopUmountArgs;

typedef struct SceVfsopInitArgs { // size is 0x4-bytes
	struct SceVfsAddParam *pParam;
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

typedef struct SceVfsMountLock {
	SceUID mutex_id;
	SceUID cond_id;
	int data_0xD8;
	int data_0xDC;
} SceVfsMountLock;

typedef struct SceVfsMount_CC {
	struct SceVopTable *ops;
	int dirty;
	int *flag;
	SceUID *eventFlag;
} SceVfsMount_CC;

typedef union SceVfsMountAttr { // size is 4-bytes
	SceInt32 value;
	struct {
		SceInt16 _private;
		SceInt16 shared;
	};
} SceVfsMountAttr;

typedef struct SceVfsMount { // size is 0x100-bytes
	SceUInt8 fastmutex[0x40];

	struct SceVfsNode *data_0x40; // base device node
	SceUID heapid;
	int data_0x48;
	SceVfsMountAttr fsAttr;

	SceUInt32 mntAttr;
	struct SceVfsNode *pNodeTop;
	SceUInt32 nNodes;
	const struct SceVfsAddParam *pVfsAddParam;

	SceInt32 mntRefCount;
	int openedEntryNum;
	int data_0x68;
	int data_0x6C;
	struct SceVfsMount *refer_next;
	struct SceVfsMount *refer;
	struct SceVfsMount *next;
	const struct SceVfsMount2 *pVfsMount2;

	// offset: 0x80
	char device[0x40];
	int data_0xC0;
	void *pCommon;
	SceVfsMountLock *pLock;
	SceVfsMount_CC *pCC;

	SceVfsMountLock lock;
	SceVfsMount_CC CC;

	int data_0xF0;
	int data_0xF4;
	int data_0xF8;
	int data_0xFC;
} SceVfsMount;

// real name is ncache (name cache)
typedef struct SceVfsNCache { // size is 0x20-bytes
	struct SceVfsNCache *data_0x00; // next cache on current dir
	struct SceVfsNCache *parent; // ncdd
	struct SceVfsNCache *data_0x08; // link with per mount all cache
	struct SceVfsNCache *child;
	struct SceVfsNode *pNode;
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
		const struct SceVopTable *ops;
		SceUInt32 nodeInf;
		void *nodeData;
		SceVfsMount *mnt;

		// offset 0x50
		struct SceVfsNode *dd; // parent vnode
		struct SceVfsNode *pNextNode; // All node link of mount
		SceUInt32 refCount;
		const SceVfsTable *vfs_table;

		short *path;  // userdata. Outside of the control for vfs.
		SceUInt32 unk_64;
		SceUInt32 unk_68;
		SceUID allocator;

		SceVfsNCache *ncache;
		SceUInt32 state;
		SceUInt32 type; // 1:file 2:dir
		SceUInt32 unk_7C;

		// offset: 0x80
		SceOff size;
		SceUInt32 st_attr; // aclData?
		SceUInt32 unk_8C;   // aclData?

		struct SceVfsFileObject *fdList;
		SceUInt32 fdNum;
		struct SceVfsNode *linkTo;
		SceUInt32 linkedNum;

		SceUInt8 data2[0x30];

		SceUInt32 unk_D0;               // devMajor.w.unk_4E
		SceUInt32 unk_D4;
	} core;

	SceUInt8 padding_0xD8[0x28];
} SceVfsNode;

typedef struct SceVfsFileObject { // size is 0x40-bytes
	SceBool is_dir_handler;
	int flags;                    // from sceIoOpen args
	SceOff offset;

	int flags2;
	SceUID pid;
	SceVfsNode *node;
	struct SceVfsFileObject *prev_obj;

	void *device_handle;
	SceUInt16 unk24;
	SceUInt8 unk26;
	SceUInt8 unk27;
	SceVfsMountLock *pLock;
	int devMinor;

	void *file_info; // size is 0x20-bytes. If have Dipsw 0xD2, only.
	char unk34[12];
} SceVfsFileObject;

typedef struct SceUIDVfsFileObject {
	void *userdata;
	void *sce_class; 
	SceVfsFileObject vfs_object;
} SceUIDVfsFileObject;

typedef struct SceVfsAddParam { // size is 0x20-bytes
	const SceVfsTable *pVfsTable;
	const char *vfsName;   // ex:"bsod_dummy_host_fs"/"exfat"
	SceSize vfsNameLen;
	int is_mounted;
	int data_0x10;         // ex:0x10
	const struct SceVopTable *pVopTable;
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



#define SCE_VFS_FS_ATTR_EXFAT     (1)
#define SCE_VFS_FS_ATTR_PFS       (2)
#define SCE_VFS_FS_ATTR_HOST      (4)
#define SCE_VFS_FS_ATTR_BLOCK     (0x10)
#define SCE_VFS_FS_ATTR_TTY       (0x20)
#define SCE_VFS_FS_ATTR_REMOVAL   (0x10000)
#define SCE_VFS_FS_ATTR_REMOVAL2  (0x20000)
#define SCE_VFS_FS_ATTR_INTERNAL  (0x1000000)
#define SCE_VFS_FS_ATTR_EXTERNAL  (0x2000000)
#define SCE_VFS_FS_ATTR_0x4000000 (0x4000000)

#define SCE_VFS_MOUNT_FLAG_RO (0x1000)

typedef struct SceVfsMountParam { // size is 0x20-bytes
	const char *device;    // ex: "/host", "/dev", "/tty", "/md"
	const char *blockdevName;
	SceUInt32 fsAttr;
	SceUInt32 mntAttr;
	const char *vfsName;
	void *pCommon;
	const SceVfsMount2 *pVfsMount2;
	const struct SceVopTable *vop;
} SceVfsMountParam;

typedef struct SceVfsUmountParam {
	const char *device; // ex:"/host"
	int data_0x04;
} SceVfsUmountParam;

/* vfs function */

/*
 * Mount registered vfs
 */
int ksceVfsMount(const SceVfsMountParam *pParam);

/*
 * Unmount registered vfs
 */
int ksceVfsUnmount(const SceVfsUmountParam *pParam);

int ksceVfsOpDevctl(SceVfsMount *pMountInfo, const char *dev, int cmd, void *indata, SceSize inlen, void *outdata, SceSize outlen);
int ksceVfsOpDecodePathElem(SceVfsMount *pMount, const char *path, const char **dst_path, const char **child, char *dst, SceSize dst_size, SceSize *pResultSize);


typedef struct SceIoMountInfo { // size is 0x54C-bytes
	void *mnt;
	int mntId;
	char assignName[0x20];
	SceUInt32 openedEntryNum;
	int unk_0x2C;
	SceUInt32 mntAttr;
	SceUInt32 fsAttr;
	int unk_0x38;
	int unk_0x3C;
	int unk_0x40;
	int unk_0x44;
	int unk_0x48;
	int unk_0x4C;
	int unk_0x50;
	int unk_0x54;
	int unk_0x58;
	int unk_0x5C;
	int unk_0x60;
	int unk_0x64;
	int unk_0x68;
	int unk_0x6C;
	int unk_0x70;
	int unk_0x74;
	int unk_0x78;
	int unk_0x7C;
	int unk_0x80;
	int unk_0x84;
	char unk_0x88[0x400];
	int unk_0x488;
	char unk_0x48C[0x40];
	char blockdevName[0x40];
	char unk_0x50C[0x40];
} SceIoMountInfo;


#endif // _PSP2_KERNEL_VFS_H_
