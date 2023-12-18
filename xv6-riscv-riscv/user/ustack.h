#ifndef XV6_RISCV_RISCV_USTACK_H
#define XV6_RISCV_RISCV_USTACK_H

#endif //XV6_RISCV_RISCV_USTACK_H
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/riscv.h"

void* ustack_malloc(uint len);
int ustack_free(void);