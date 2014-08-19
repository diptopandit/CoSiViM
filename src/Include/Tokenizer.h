#ifndef COSIVM_TOK_H
#define COSIVM_TOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "Instructions.h"
#include "Registers.h"

#define COSIVM_TOKEN_LENGTH 10

// shortcut
#define Type(x) COSIVM_TYPE_##x

typedef enum {
  Type(UNDEF),
  Type(NUM),
  Type(REG),
  Type(LBL),
  Type(FUNC),
  Type(VAR),
  Type(INSTR),
} cosivm_token_type;

static char cosivm_reverse_type[][6] = {
  "undef","num","reg","lbl","func","var","instr"
};

typedef struct cosivm_tok_s {
  char token[COSIVM_TOKEN_LENGTH];
  cosivm_token_type type;
  long long pos;
  long long value;

  struct cosivm_tok_s *next;
} cosivm_token;

cosivm_token *cosivm_tokenize (char *);
void cosivm_cleanup_tokens (cosivm_token *);
char* read_file (char *);
int is_sign (char);
int is_num (char *);
char *is_reg (char *);
char *is_label (char *);
char *is_func (char *);
char *is_var (char *);
int is_instr (char *);


#endif
