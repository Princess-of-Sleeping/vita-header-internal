
typedef struct SceModuleCB { // size is 0x400-bytes on 1.81
	SceUInt8 data[0x400];
} SceModuleCB;

typedef struct SceUIDModuleObject { // size is 0xC-bytes on 1.81
	uint32_t sce_reserved[2];
	SceModuleCB *cb;
} SceUIDModuleObject;
