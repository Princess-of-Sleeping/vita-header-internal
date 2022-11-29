
typedef struct SceModuleCB { // size is 0x2CC-bytes on 2.00-2.06
	SceUInt8 data[0x2CC];
} SceModuleCB;

typedef struct SceUIDModuleObject { // size is 0xC-bytes on 2.00-2.06
	uint32_t sce_reserved[2];
	SceModuleCB *cb;
} SceUIDModuleObject;
