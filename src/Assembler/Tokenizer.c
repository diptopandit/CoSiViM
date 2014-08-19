#include "../Include/Tokenizer.h"

cosivm_token *cosivm_tokenize (char *fn) {
  assert(fn != NULL);

  char *str = read_file(fn);
  char *delim = " ,\t\n";
  char *toks = strtok(str, delim);

  cosivm_token_type type;
  cosivm_token *parsed = malloc(sizeof(cosivm_token));
  cosivm_token *head = parsed;
  long long i = 0;

  while (toks != NULL) {
    if (is_num(toks))
      type = Type(NUM);
    else if (is_reg(toks))
      type = Type(REG);
    else if (is_label(toks))
      type = Type(LBL);
    else if (is_func(toks))
      type = Type(FUNC);
    else if (is_var(toks))
      type = Type(VAR);
    else if (is_instr(toks))
      type = Type(INSTR);
    else
      type = Type(UNDEF);

    // don't copy colon
    if (type == Type(LBL))
      memcpy(parsed->token, toks, strlen(toks) - 1);
    // don't copy @
    else if (type == Type(REG) || type == Type(FUNC) || type == Type(VAR))
      memcpy(parsed->token, toks + 1, strlen(toks) - 1);
    // nothing to avoid
    else
      memcpy(parsed->token, toks, strlen(toks));

    parsed->type = type;
    parsed->pos = i++;
    parsed->next = NULL;

    toks = strtok(NULL, delim);
    if (toks != NULL) {
      parsed->next = malloc(sizeof(cosivm_token));
      parsed = parsed->next;
    }
  }

  free(str);

  return head;
}

void cosivm_cleanup_tokens (cosivm_token *tokens) {
  assert(tokens != NULL);

  cosivm_token *tmp;

  while (tokens != NULL) {
    tmp = tokens->next;
    free(tokens);
    tokens = tmp;
  }
}

char *read_file (char *fn) {
  assert(fn != NULL);

  char *contents;
  long long fsize;

  FILE *fp = fopen(fn, "rb");
  assert(fp != NULL);

  fseek(fp, 0, SEEK_END); // go to end
  fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET); // go to beginning

  contents = malloc(fsize * sizeof(char));
  if (contents == NULL) {
    fprintf(stderr, "Could not malloc space for file contents.\n");
    exit(1);
  }

  int nread = fread(contents, sizeof(char), fsize, fp);
  assert(nread == fsize);
  fclose(fp);

  return contents;
}


int is_sign (char c) {
  return c == '+' || c == '-';
}

int is_num (char *s) {
  assert(s != NULL);

  if (!(is_sign(s[0]) || isdigit(s[0]))) return 0;

  for (int i = 1; i < strlen(s); i++)
    if (!isdigit(s[i])) return 0;

  return 1;
}

char *is_reg (char *s) {
  assert(s != NULL);

  return strchr(s, '%');
}

char *is_label (char *s) {
  assert(s != NULL);

  return strchr(s, ':');
}

char *is_func (char *s) {
  assert(s != NULL);

  return strchr(s, '@');
}

char *is_var (char *s) {
  assert(s != NULL);

  return strchr(s, '$');
}

int is_instr (char *s) {
  assert(s != NULL);
  for (int i = 0; i < COSIVM_NUM_INSTRS; i++)
    if (!strcmp(cosivm_reverse_instr[i], s))
      return 1;

  return 0;
}
