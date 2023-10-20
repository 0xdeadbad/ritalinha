#include <bits/stdint-uintn.h>
#include <stdlib.h>
#include <stdio.h>

#include "vm/vm.h"

#define PUSH(vm,val) ((uint64_t)vm->stack[vm->sp++] = (uint64_t)val)
#define POP(vm) ((uint64_t)vm->stack[--vm->sp])

struct rita_VM
{
    op_code *ops;
    struct registers 
    {
        uint32_t ip;
        uint8_t sp;
        uint8_t bp;
        uint64_t r0;
        uint64_t r1;
        uint64_t r2;
    } registers;
    uint64_t stack[];
};

rita_VM*
rita_VM_new(size_t stack_size)
{
    rita_VM *r;

    if((r = (rita_VM*)calloc(sizeof(rita_VM) + stack_size, 1)) == NULL)
    {
        return NULL;
    }

    r->ops = NULL;
    r->registers.ip = r->registers.sp = r->registers.bp = 0;

    return r;
}

/*int x = 0;
__asm("movl $5, %[myvar]"
    : [myvar] "=rm"(x));
printf("%d\n", x);*/

int32_t
rita_VM_run(rita_VM *vm)
{
    struct registers *ry = &vm->registers;
    op_code op;
    for(;;)
    {
        op = vm->ops[vm->registers.ip];
        switch(vm->ops[vm->registers.ip].instruction)
        {
            
            case ADD:
            {
                ry->r2 = op.operand_x.vals.lval + op.operand_x.vals.rval;
            }
            break;
            case SUB:
            case MUL:
            case DIV:
            case MOD:
            case AND:
            case OR:
            case XOR:
            case CMD:
            case JE:
            case JNE:
            case JL:
            case JLE:
            case JG:
            case JGE:
            case CALL:
            case JMP:
            case RET:
            case LOAD:
            case LOADB:
            case STORE:
            case STOREB:
            case PUSH:
            case POP:
            case IN:
            case OUT:
            case MOV:
            case HLT:
            case NOP:
            case SYSCALL:
            case _MAX:
                break;
            };
    }

    return EXIT_SUCCESS;
}

int64_t
size_of_op(void) 
{
    return sizeof(struct _op);
}
