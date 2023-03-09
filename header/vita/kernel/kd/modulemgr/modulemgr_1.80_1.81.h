
typedef struct SceModuleCB SceModuleCB;

typedef struct SceModuleLibEnt { // size is 0x60-bytes
	SceUInt32 data_0x00;
	struct SceModuleLibEnt *next;
	SceUInt32 data_0x08;
	SceModuleExport *Export;

	SceModuleExport *ExportProc;
	char *name;
	SceUInt32 data_0x18;
	SceUInt32 data_0x1C;

	SceUInt32 data_0x20;
	SceUInt32 data_0x24;
	SceUInt32 data_0x28;
	SceUInt32 data_0x2C;

	SceUInt32 data_0x30;
	SceNID libnid;
	SceUID libent_guid;
	SceUInt32 data_0x3C;

	void *data_0x40; // LIBS data.
	SceUInt32 data_0x44;
	SceUInt32 data_0x48;
	SceUInt32 data_0x4C;

	SceUInt32 data_0x50;
	SceModuleCB *Module;
	SceUID pid;
	SceUInt32 data_0x5C;
} SceModuleLibEnt;

typedef struct SceModuleEntryPoint { // size is 0x5C-bytes
	SceUInt16 attr;
	SceUInt8 minor;
	SceUInt8 major;
	char name[27];
	SceUInt8 type;
	void *gp_value;
	SceUInt32 libent_top;
	SceUInt32 libent_btm;
	SceUInt32 libstub_top;
	SceUInt32 libstub_btm;
	SceUInt32 fingerpint;
	int unk_0x38;
	int unk_0x3C;
	int unk_0x40;
	SceUInt32 module_start;
	SceUInt32 module_stop;
	SceUInt32 exidx_start;
	SceUInt32 exidx_end;
	SceUInt32 extab_start;
	SceUInt32 extab_end;
} SceModuleEntryPoint;

typedef struct SceModuleCB { // size is 0x3F8-bytes on 1.81
	SceUID kModuleId;
	SceUID uModuleId;
	SceModuleEntryPoint entry;
	SceUInt8 data[0x10];
	Elf32_Ehdr ehdr;
	struct {
		Elf32_Phdr phdr;
		SceUInt8 data_0xC8[0x40];
		void *vbase;
		SceUID memid;
		void *vaddr;
		SceSize size;
		SceInt32 data_0x118;
	} segment[6];
	SceUInt8 data_0x360[0x68];
	struct SceModuleCB *next;
	SceUInt8 data_0x3CC[0x2C];
} SceModuleCB;

typedef struct SceUIDModuleObject { // size is 0xC-bytes on 1.81
	uint32_t sce_reserved[2];
	SceModuleCB *cb;
} SceUIDModuleObject;

typedef struct SceKernelLibraryDB { // size is 0x3C-bytes
	SceUInt32 data_0x00;
	SceModuleLibEnt *LibEntHead; // size is 0x60-bytes
	SceUInt32 data_0x08;
	void *data_0x0C; // LIBS data. size is 0x48-bytes
	SceUInt32 data_0x10;
	SceModuleCB *ModuleHead;
	SceUInt32 ModuleCounter;
	SceUInt32 data_0x1C;
	SceUInt32 data_0x20;
	void *data_0x24; // size is 0x3C-bytes or 0x40-bytes
	SceKernelSpinlock mutex;
	SceUInt32 data_0x2C;
	SceUID pid;
	SceUInt32 data_0x34;
	SceUInt32 data_0x38;
} SceKernelLibraryDB;
