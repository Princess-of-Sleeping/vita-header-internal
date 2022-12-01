
#ifndef _PSP2_KERNEL_DEBUG_H_
#define _PSP2_KERNEL_DEBUG_H_


#include <vita/shared/types.h>
#include <stdarg.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef enum SceKernelDebugLevel {
	SCE_KERNEL_DEBUG_LEVEL_TRACE = 0, /* An extremely verbose logging level, mostly useful for internal developers. */
	SCE_KERNEL_DEBUG_LEVEL_DEBUG,     /* A diagnostic logging level. */
	SCE_KERNEL_DEBUG_LEVEL_INFO,      /* An informational logging level. */
	SCE_KERNEL_DEBUG_LEVEL_WARNING,   /* A logging level that gives warnings of situations detrimental to proper execution. */
	SCE_KERNEL_DEBUG_LEVEL_ERROR,     /* A logging level that will report erroneous conditions in execution. */
	SCE_KERNEL_DEBUG_LEVEL_NUMBERS    /* The number of logging levels available. */
} SceKernelDebugLevel;

typedef struct SceKernelDebugInfo { // size is 0x18 on FW 3.60
	SceUInt32 fileHash; // First 4 bytes of SHA1(__FILE__) - e.g. 0x123EC4E8 = "processmgr.c"
	SceUInt32 lineHash; // First 4 bytes of SHA1("%s:%d" % (__FILE__, __LINE__)) - e.g. 0x7D3F4B00 = "boot.c:1868"
	SceUInt32 funcHash; // First 4 bytes of SHA1(__FUNC__) - e.g. 0x197C5ED2 = "LedModuleStart"
	const char *pFile;  // Pointer to file name - can be NULL.
	SceUInt32 line;     // Line in file - ignored if pFile is NULL.
	const char *pFunc;  // Pointer to function name - ignored if pFile is NULL.
} SceKernelDebugInfo;

typedef enum SceKernelDebugInfoFlag {
	SCE_KERNEL_DEBUG_INFO_FLAG_NONE = 0,
	SCE_KERNEL_DEBUG_INFO_FLAG_CORE = 1,
	SCE_KERNEL_DEBUG_INFO_FLAG_FUNC = 2,
	SCE_KERNEL_DEBUG_INFO_FLAG_LINE = 4,
	SCE_KERNEL_DEBUG_INFO_FLAG_FILE = 8
} SceKernelDebugInfoFlag;


int sceKernelPrintf(const char *fmt, ...);
int sceKernelPrintfLevel(SceUInt32 level, const char *fmt, ...);
int sceKernelPrintfLevelWithInfo(SceUInt32 level, const SceKernelDebugInfo *pInfo, const char *fmt, ...);

int sceKernelVprintf(const char *fmt, va_list arg);
int sceKernelVprintfAssertLevel(SceUInt32 level, SceBool condition, const SceKernelDebugInfo *pInfo, const void *lr, const char *fmt, va_list arg);

int sceKernelAssert(SceBool condition, const SceKernelDebugInfo *pInfo, const void *lr);
int sceKernelAssertLevel(SceUInt32 level, SceBool condition, const SceKernelDebugInfo *pInfo, const void *lr);

SceUInt32 sceKernelGetAssertLevel(void);

int sceKernelPanic(const SceKernelDebugInfo *pInfo, const void *lr);

int sceKernelVprintfLevel(SceUInt32 level, const char *fmt, va_list arg);
int sceKernelVprintfWithInfo(SceUInt32 level, const SceKernelDebugInfo *pInfo, const char *fmt, va_list arg);
int sceKernelVprintfPanic(const SceKernelDebugInfo *pInfo, const void *lr, const char *fmt, va_list arg);



#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_DEBUG_H_ */
