#ifndef ___VM_OPCODES_H___
#define ___VM_OPCODES_H___
#include <stdint.h>
#include <limits.h>

typedef struct _op op_code;

enum _instruction {
    ADD = 0,
    SUB,
    MUL,
    DIV,
    MOD,
    AND,
    OR,
    XOR,
    CMD,
    JE,
    JNE,
    JL,
    JLE,
    JG,
    JGE,
    CALL,
    JMP,
    RET,
    LOAD,
    LOADB,
    STORE,
    STOREB,
    PUSH,
    POP,
    IN,
    OUT,
    MOV,
    HLT,
    NOP,
    SYSCALL,

    // Hax so it can be at least 32bit size
    _MAX = INT32_MAX
} __attribute__((__packed__));

// Should be 32bit in total size due bitfield specification and packed attributes
struct _op {
    union {
        struct operands {
            uint32_t operand_1;
            uint32_t operand_2;
        } operands;
        struct vals {
            uint32_t lval;
            uint32_t rval;
        } vals;
    } operand_x;
    uint8_t operand_0;
    enum _instruction instruction : 8;
};

#endif
