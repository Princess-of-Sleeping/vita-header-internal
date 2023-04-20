
#ifndef _PSP2_KERNEL_MODULEMGR_INTERNAL_H_
#define _PSP2_KERNEL_MODULEMGR_INTERNAL_H_


#include <psp2kern/types.h>


/*
typedef struct SceKernelModulePrivate9 { // size is 0x84-bytes on 3.00
	SceClass SceUIDModuleClass;
	SceClass SceUIDLibraryClass;
	SceKernelProcessModuleInfo ProcModuleInfo;
	void *data_0x7C;
	SceUID ScePsp2BootConfig_modid;
} SceKernelModulePrivate9;

*/

typedef struct SceModuleCB SceModuleCB;
typedef struct SceModuleLibEnt SceModuleLibEnt;

typedef struct SceModuleImportOld { // size is 0x34-bytes
	SceUInt8 size;
	SceUInt8 auxattr;
	uint16_t version;
	uint16_t flags;
	uint16_t entry_num_function;
	uint16_t entry_num_variable;
	uint16_t entry_num_tls;
	uint32_t rsvd1;
	uint32_t libnid;
	const char *libname;
	uint32_t rsvd2;
	uint32_t *table_func_nid;
	void    **table_function;
	uint32_t *table_vars_nid;
	void    **table_variable;
	uint32_t *table_tls_nid;
	void    **table_tls;
} SceModuleImportOld;

typedef struct SceModuleImport { // size is 0x24-bytes
	SceUInt8 size;
	SceUInt8 auxattr;
	uint16_t version;
	uint16_t flags;
	uint16_t entry_num_function;
	uint16_t entry_num_variable;
	uint16_t data_0x0A; // unused?
	SceNID libnid;
	const char *libname;
	SceNID *table_func_nid;
	void  **table_function;
	SceNID *table_vars_nid;
	void  **table_variable;
} SceModuleImport;

typedef struct SceModuleExport {
	uint8_t size; // 0x20
	uint8_t auxattr;
	uint16_t version;
	uint16_t attr; // 0x4000:user export
	uint16_t entry_num_function;
	uint16_t entry_num_variable;
	uint16_t data_0x0A; // unused?
	uint32_t data_0x0C; // unused?
	uint32_t libnid;
	const char *libname;
	uint32_t *table_nid;
	void    **table_entry;
} SceModuleExport;

typedef struct SceModuleClient { // size is 0x18-bytes
	struct SceModuleClient *next;
	SceModuleImport *Import;
	SceModuleImport *Import2;
	SceModuleLibEnt *LibEnt;
	SceModuleCB *Module;
	ScePVoid stubtbl; // Required the dipsw 0xD2. stub pointer + stub nids
} SceModuleClient;

typedef struct SceModuleLibEnt { // size is 0x30-bytes on 3.00
	struct SceModuleLibEnt *next;
	struct SceModuleLibEnt *data_0x04; // maybe
	SceModuleExport *Export;
	SceModuleExport *pExportInfo2;

	/*
	 * (syscall_idx &  0xFFF):syscall idx
	 * (syscall_idx & 0x1000):has syscall flag?
	 * (syscall_idx == 0) -> kernel export
	 */
	uint16_t syscall_info;
	uint16_t data_0x0E;

	/*
	 * Number of times this export was imported into another module
	 */
	SceSize number_of_imported;
	SceModuleClient *Client;
	SceUID libid_kernel;
	SceUID libid_user;
	SceModuleCB *Module;
	int data_0x24; // zero?
	int data_0x28; // zero?
} SceModuleLibEnt;

typedef struct SceModuleSegment { // size is 0x20-bytes on 3.00
	int flags;
	int flags2;
	ScePVoid vaddr;
	SceUID memblock_id;
	SceUInt32 unk_0x10;
	ScePVoid address2;
	int flags3;
	SceSize length;
} SceModuleSegment;

typedef struct _SceModuleCB {
	struct _SceModuleCB *next;
	SceModuleCB *Module;
	int a3;
} _SceModuleCB;

typedef struct SceModuleCB { // size is 0x114-bytes on 3.00
	SceUID module_guid;
	SceUID module_puid;
	SceUInt16 attr;
	SceUInt16 version;
	char module_name[0x1C];
	SceModuleExport *export_start;
	SceModuleExport *export_end;
	SceModuleImport *import_start;
	SceModuleImport *import_end;
	SceUInt32 fingerprint;
	ScePVoid tls_start;
	ScePVoid tls_filesz;
	ScePVoid tls_memsz;
	ScePVoid exidx_start;
	ScePVoid exidx_end;
	ScePVoid extab_start;
	ScePVoid extab_end;
	SceChar8 *module_path;
	ScePVoid unk_0x5C;
	ScePVoid unk_0x60;
	SceUInt32 unk_0x64;
	SceUInt32 unk_0x68;
	SceInt32 segment_num;
	SceModuleSegment segment[3];
	ScePVoid start_entry;
	ScePVoid stop_entry;
	ScePVoid exit_entry;
	ScePVoid module_bootstart;
	ScePVoid module_proc_param;
	ScePVoid sce_module_start_thread_parameter;
	ScePVoid sce_module_stop_thread_parameter;
	ScePVoid unk_0xEC;
	_SceModuleCB *unk_0xF0;
	SceUInt16 flags;
	SceUInt8 state;
	SceUInt8 pad_0xF7;
	// struct SceModuleCB *prev_module; // real name
	struct SceModuleCB *next;
	SceUID processId;
	SceUInt32 module_sdk_version;
	SceUInt32 unk_0x104;
	ScePVoid module_dtrace_probes_info;
	ScePVoid module_dtrace_probes;
	SceUInt32 unk_0x110;
} SceModuleCB;

typedef struct SceUIDModuleObject { // size is 0x120-bytes on 3.00
	uint32_t sce_reserved[2];
	SceModuleCB cb;
	int data_0x11C;
} SceUIDModuleObject;


typedef struct SceKernelLibraryDB { // size is 0x24-bytes
	SceUID pid;
	SceModuleLibEnt *LibEntHead;
	SceUInt16 LibEntCounter;
	SceUInt16 LostClientCounter;
	SceModuleClient *LostClientHead;
	SceModuleCB *ModuleHead;
	SceUID ModuleId;
	SceUInt16 ModuleCounter;
	SceUInt16 flags;
	void *Addr2ModTbls;
	SceUInt32 mutex;
} SceKernelLibraryDB;


#endif /* _PSP2_KERNEL_MODULEMGR_INTERNAL_H_ */
