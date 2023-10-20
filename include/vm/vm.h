#ifndef ___VM_H___
#define ___VM_H___

#include <stdint.h>
#include <vm/vm_opcodes.h>

typedef struct rita_VM rita_VM;

int32_t
rita_VM_run(rita_VM *vm);



int64_t
size_of_op(void);

#endif
