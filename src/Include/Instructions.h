#ifndef COSIVM_INSTRUCTIONS_H
#define COSIVM_INSTRUCTIONS_H

#define Instruction(x) COSIVM_INSTR_##x

// Opcodes
typedef enum {
  Instruction(NOP),		//0x00
  Instruction(LOAD),	//0x01
  Instruction(MOV),		//0x02
  Instruction(ADD),		//0x03
  Instruction(ADDI),	//0x04
  Instruction(SUB),		//0x05
  Instruction(SUBI),	//0x06
  Instruction(MUL),		//0x07
  Instruction(MULI),	//0x08
  Instruction(MOD),		//0x09
  Instruction(MODI),	//0x0A
  Instruction(NOT),		//0x0B
  Instruction(XOR),		//0x0C
  Instruction(XORI),	//0x0D
  Instruction(OR),		//0x0E
  Instruction(ORI),		//0x0F
  Instruction(AND),		//0x10
  Instruction(ANDI),	//0x11
  Instruction(PUSH),	//0x12
  Instruction(PSHI),	//0x13
  Instruction(POP),		//0x14
  Instruction(CMP),		//0x15
  Instruction(CMPI),	//0x16
  Instruction(JZ),		//0x17
  Instruction(JNZ),		//0x18
  Instruction(JMP),		//0x19
  Instruction(CALL),	//0x1A
  Instruction(RET),		//0x1B
  Instruction(RES1),	//0x1C
  Instruction(RES2),	//0x1D
  Instruction(RES3),	//0x1E
  Instruction(HALT),	//0x1F
//Total number of instructions:
  COSIVM_NUM_INSTRS,
} cosivm_instr;

static char cosivm_reverse_instr[][6] = {
  "nop","load","mov","add","addi","sub","subi","mul","muli","mod","modi","not","xor","xori","or","ori",
  "and","andi","push","pshi","pop","cmp","cmpi","jz","jnz","jmp","call","ret","res1","res2","res3","halt","undef"
};

#define COSIVM_BINOP(NAME, F) definstr (NAME) { \
  long long b, a; \
  if (cosivm_stack_pop(&m->stack, &b) == -1)\
    cosivm_vm_err(m, COSIVM_STACK_EMPTY);\
  if (cosivm_stack_pop(&m->stack, &a) == -1)\
    cosivm_vm_err(m, COSIVM_STACK_EMPTY);\
  cosivm_stack_push(&m->stack, a F b);}

#define COSIVM_SPOP(NAME) if (cosivm_stack_pop(&m->stack, &NAME) == -1) \
    cosivm_vm_err(m, COSIVM_STACK_EMPTY)

#define COSIVM_SPUSH(NAME) if (cosivm_stack_push(&m->stack, NAME) == -1) \
    cosivm_vm_err(m, COSIVM_STACK_NO_MEM)

#endif
