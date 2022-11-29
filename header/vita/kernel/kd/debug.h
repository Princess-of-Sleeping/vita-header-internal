
#ifndef _PSP2_KERNEL_DEBUG_H_
#define _PSP2_KERNEL_DEBUG_H_

#include <vita/shared/types.h>


#ifdef __cplusplus
extern "C" {
#endif


int sceKernelPrintf(const char *fmt, ...);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_DEBUG_H_ */
