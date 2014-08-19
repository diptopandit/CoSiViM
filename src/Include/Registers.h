#ifndef COSIVM_REGISTERS_H
#define COSIVM_REGISTERS_H

// make register numbers easier on the eyes
typedef enum {
  // regs 0 through 9 for general use
  COSIVM_REG0 ,
  COSIVM_REG1 ,
  COSIVM_REG2 ,
  COSIVM_REG3 ,
  COSIVM_REG4 ,
  COSIVM_REG5 ,
  COSIVM_REG6 ,
  COSIVM_REG7 ,

  // regs used for cmp, et al
  COSIVM_EAX  ,
  COSIVM_EBX  ,
  COSIVM_ECX  ,

  // instruction pointer
  COSIVM_EIP  ,

  // stack pointer
  COSIVM_ESP  ,

  // frame pointer
  COSIVM_EFP  ,

  // Link register
  COSIVM_ELR ,

  // Status register
  COSIVM_PSR ,
  
  //total number of registers:
  COSIVM_NUM_REGS,
} cosivm_reg;

static char cosivm_reverse_reg[][5] = {
  "reg0","reg1","reg2","reg3","reg4","reg5","reg6","reg7",
  "eax","ebx","ecx","eip","esp","efp","elr","psr","undef"
};

#endif
