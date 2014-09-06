#ifndef COSIVM_ASSEMBLER_H
#define COSIVM_ASSEMBLER_H

#include <getopt.h>
#include "../Include/Tokenizer.h"
#define COSIVM_ASEMBLER_VERSION 0.1

typedef struct cosivm_option_s {
  short int version;
  short int license;
  short int warranty;
  short int conditions;
  char *file;
} cosivm_option;

void cosivm_print_version ();
void cosivm_print_license ();
void cosivm_print_warranty ();
void cosivm_print_conditions ();
long long cosivm_create_machine_code (cosivm_token*, long long **, long long*);
void cosivm_run_assembler(char *);
long long cosivm_create_executable(char*, long long *, long long, long long*);
void cosivm_cleanup_code(char*);

#endif
