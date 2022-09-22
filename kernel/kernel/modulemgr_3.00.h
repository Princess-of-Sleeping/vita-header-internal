
typedef struct SceModuleImport SceModuleImport;
typedef struct SceModuleCB SceModuleCB;

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

typedef struct SceModuleSegment { // size is 0x20-bytes on 3.00
	int flags;
	int flags2;
	ScePVoid address;
	SceUID memblock_id;
	SceUInt32 unk_0x10;
	ScePVoid address2;
	int flags3;
	SceSize length;
} SceModuleSegment;

typedef struct SceModuleLibraryInfo { // size is 0x30-bytes on 3.00
	struct SceModuleLibraryInfo *next;
	struct SceModuleLibraryInfo *data_0x04; // maybe
	SceModuleExport *pExportInfo;
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
	SceModuleImportInfo *pImportedInfo;
	SceUID libid_kernel;
	SceUID libid_user;
	SceModuleCB *pModuleInfo;
	int data_0x24; // zero?
	int data_0x28; // zero?
} SceModuleLibraryInfo;

typedef struct SceModuleCB { // size is 0x114-bytes on 3.00
	SceUID module_guid;
	SceUID module_puid;
	SceUInt16 attr;
	SceUInt16 version;
	SceChar8 module_name[0x1C];
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
	SceUInt32 unk_0x70;
	SceUInt32 unk_0x74;
	SceModuleSegment segment[2];
	SceUInt32 unk_0xB8;
	SceUInt32 unk_0xBC;
	SceUInt32 unk_0xC0;
	SceUInt32 unk_0xC4;
	SceUInt32 unk_0xC8;
	SceUInt32 unk_0xCC;
	ScePVoid start_entry;
	ScePVoid stop_entry;
	ScePVoid exit_entry;
	ScePVoid module_bootstart;
	ScePVoid module_proc_param;
	ScePVoid sce_module_start_thread_parameter;
	ScePVoid sce_module_stop_thread_parameter;
	ScePVoid unk_0xEC;
	SceUInt32 unk_0xF0;
	SceUInt16 flags;
	SceUInt8 state;
	SceUInt8 pad_0xF7;
	ScePVoid prev_module;
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
