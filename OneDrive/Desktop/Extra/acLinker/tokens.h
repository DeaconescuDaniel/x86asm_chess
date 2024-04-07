#include <stdint-gcc.h>
typedef enum {
    add,
    addi,
    and,
    andi,
    beq,
    bgez,
    bgtz,
    bne,
    j,
    jr,
    lw,
    noop,
    or,
    ori,
    sll,
    sllv,
    slt,
    slti,
    sra,
    srl,
    sub,
    sw,
    xor
} TOK;

typedef enum {
    R_TYPE,
    I_TYPE,
    J_TYPE,
    UNKNOWN_TYPE
} OpType;

OpType getOpType(TOK token);
uint8_t opcodeMask(TOK token);
uint32_t parseOperation(TOK op,const char* str);
TOK findFirstToken(const char *str);