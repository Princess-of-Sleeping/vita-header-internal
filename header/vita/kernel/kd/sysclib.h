
#ifndef _PSP2_KERNEL_SYSCLIB_H_
#define _PSP2_KERNEL_SYSCLIB_H_

#include <shared/types.h>


#ifdef __cplusplus
extern "C" {
#endif


void *memset(void *dst, int ch, int n);
void *memcpy(void *dst, const void *src, int n);


#ifdef __cplusplus
}
#endif


#endif /* _PSP2_KERNEL_SYSCLIB_H_ */
