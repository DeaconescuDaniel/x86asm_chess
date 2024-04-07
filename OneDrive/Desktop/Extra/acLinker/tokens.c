#include "tokens.h"
#include <string.h>
#include <stdio.h>

uint8_t getFunction(TOK op);

TOK findFirstToken(const char *str) {
    switch (str[0]) {
        case 'a':
            if (strncmp(str, "addi", 4) == 0) {
                return addi;
            } else if (strncmp(str, "add", 3) == 0) {
                return add;
            }
            break;
        case 'b':
            if (strncmp(str, "bgez", 4) == 0) {
                return bgez;
            } else if (strncmp(str, "bgtz", 4) == 0) {
                return bgtz;
            } else if (strncmp(str, "beq", 3) == 0) {
                return beq;
            } else if (strncmp(str, "bne", 3) == 0) {
                return bne;
            }
            break;
        case 'j':
            if (strncmp(str, "jr", 2) == 0) {
                return jr;
            } else if (strncmp(str, "j", 1) == 0) {
                return j;
            }
            break;
        case 'l':
            if (strncmp(str, "lw", 2) == 0) {
                return lw;
            }
            break;
        case 'n':
            if (strncmp(str, "noop", 4) == 0) {
                return noop;
            }
            break;
        case 'o':
            if (strncmp(str, "or", 2) == 0) {
                return or;
            } else if (strncmp(str, "ori", 3) == 0) {
                return ori;
            }
            break;
        case 's':
            if (strncmp(str, "sllv", 4) == 0) {
                return sllv;
            } else if (strncmp(str, "sll", 3) == 0) {
                return sll;
            } else if (strncmp(str, "slt", 3) == 0) {
                return slt;
            } else if (strncmp(str, "slti", 4) == 0) {
                return slti;
            } else if (strncmp(str, "sra", 3) == 0) {
                return sra;
            } else if (strncmp(str, "srl", 3) == 0) {
                return srl;
            } else if (strncmp(str, "sub", 3) == 0) {
                return sub;
            } else if (strncmp(str, "sw", 2) == 0) {
                return sw;
            }
            break;
        case 'x':
            if (strncmp(str, "xor", 3) == 0) {
                return xor;
            }
            break;
    }
    return -1;
}

uint32_t parseOperation(TOK op, const char *str) {
    OpType type = getOpType(op);
    uint8_t s = 0, t = 0, d = 0, sa = 0, fun = getFunction(op);
    uint8_t opcode = opcodeMask(op);
    uint16_t imm = 0xFFFF;
    uint32_t jaddr = 0;
    uint32_t out = 0XFFFFFFFF;
    switch (type) {
        case R_TYPE:
            switch (op) {
                case sll:
                case sllv:
                case slt:
                case sra:
                case srl:
                    if (sscanf(str, "%*[^$]$%hhu,$%hhu,$%hhu", &t, &d, &sa) == 3) {
                        if (s > 31 || t > 31 || d > 31) {
                            return -1;
                        }
                    }
                    break;
                case jr:
                    if (sscanf(str, "jr $%hhu", &s) == 1) {
                        if (s > 31 || t > 31 || d > 31) {
                            return -1;
                        }
                    }
                    break;
                default:
                    if (sscanf(str, "%*[^$]$%hhu,$%hhu,$%hhu", &s, &t, &d) == 3) {
                        if (s > 31 || t > 31 || d > 31) {
                            return -1;
                        }
                    }
                    break;
            }
            out &= (((uint32_t) opcode) << 26) | 0x3FFFFFF;
            out &= (((uint32_t) s) << 21) | 0xFC1FFFFF;
            out &= (((uint32_t) t) << 17) | 0xFFE0FFFF;
            out &= (((uint32_t) d) << 12) | 0xFFFF07FF;
            out &= (((uint32_t) sa) << 6) | 0xFFFFF83F;
            out &= ((uint32_t) fun) | 0xFFFFFFC0;
            return out;

        case I_TYPE:
            switch (op) {
                case lw:
                case sw:
                    if (sscanf(str, "%*[^$]$%hhu,$%hd($%hhu)", &t, &imm, &s) == 3) {
                        if (s > 31 || t > 31 || imm > 65535) {
                            return -1;
                        }
                    }
                    break;
                case bgez:
                case bgtz:
                case bne:
                    if (sscanf(str, "%*[^$]$%hhu,%hd", &s, &imm) == 2) {
                        if (s > 31 || t > 31 || imm > 65535) {
                            return -1;
                        }
                    }
                    break;
                default:
                    if (sscanf(str, "%*[^$]$%hhu,$%hhu,%hd", &s, &t, &imm) == 3) {
                        if (s > 31 || t > 31 || imm > 65535) {
                            return -1;
                        }
                    }
                    break;
            }

            out &= (((uint32_t) opcode) << 26) | 0x3FFFFFF;
            out &= (((uint32_t) s) << 21) | 0xFC1FFFFF;
            out &= (((uint32_t) t) << 17) | 0xFFE0FFFF;
            out &= ((uint32_t) imm) | 0xFFFF0000;
            return out;
        case J_TYPE:
            if (sscanf(str, "j %d", &jaddr) == 1) {
                if (jaddr < 0) {
                    return -1;
                }
                out &= (((uint32_t) opcode) << 26) | 0x3FFFFFF;
                out &= ((uint32_t) jaddr) | 0xFC000000;
                return out;
            }
            break;
        case UNKNOWN_TYPE:
            return -1;
    }

    return -1;
}

uint8_t getFunction(TOK op) {
    switch (op) {
        case add:
            return 0x80;
        case and:
            return 0x90;
        case beq:
            return 0x10;
        case bgez:
            return 0x02;
        case bgtz:
            return 0x1C;
        case bne:
            return 0x18;
        case j:
            return 0x08;
        case jr:
            return 0x00;
        case lw:
            return 0x8C;
        case noop:
            return 0x00;
        case or:
            return 0x00;
        case ori:
            return 0x34;
        case sll:
            return 0x00;
        case sllv:
            return 0x00;
        case slt:
            return 0x00;
        case slti:
            return 0x24;
        case sra:
            return 0x00;
        case srl:
            return 0x00;
        case sub:
            return 0x00;
        case sw:
            return 0xAC;
        case xor:
            return 0x00;
        default:
            return -1;;
    }
}


OpType getOpType(TOK token) {
    switch (token) {
        case add:
        case and:
        case or:
        case sll:
        case sllv:
        case slt:
        case sra:
        case srl:
        case sub:
        case xor:
        case jr:
            return R_TYPE;
        case addi:
        case andi:
        case beq:
        case bgez:
        case bgtz:
        case bne:
        case lw:
        case noop:
        case ori:
        case slti:
        case sw:
            return I_TYPE;
        case j:
            return J_TYPE;
        default:
            return UNKNOWN_TYPE;
    }
}


uint8_t opcodeMask(TOK token) {
    switch (token) {
        case add:
        case and:
        case noop:
        case or:
        case sll:
        case sllv:
        case slt:
        case sra:
        case srl:
        case sub:
        case xor:
            return 0x00;
        case addi:
            return 0x20;
        case andi:
            return 0x30;
        case beq:
            return 0x10;
        case bgez:
            return 0x02;
        case bgtz:
            return 0x1C;
        case bne:
            return 0x18;
        case j:
            return 0x08;
        case jr:
            return 0x00;
        case lw:
            return 0x8C;
        case ori:
            return 0x34;
        case slti:
            return 0x24;
        case sw:
            return 0xAC;
        default:
            return -1;
    }

}



