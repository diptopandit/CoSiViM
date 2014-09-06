#include "../Include/Tokenizer.h"
#include "../Include/HashTable.h"

cosivm_reg cosivm_register (char *s) {
  assert(s != NULL);
  int i;
  for (i = 0; i < COSIVM_NUM_REGS; i++)
    if (!strcmp(cosivm_reverse_reg[i], s))
      return i;

  return -1;
}

cosivm_instr cosivm_instruction (char *s) {
  assert(s != NULL);
  int i;
  for (i = 0; i < COSIVM_NUM_INSTRS; i++)
    if (!strcmp(cosivm_reverse_instr[i], s))
      return i;

  return -1;
}


long long cosivm_create_machine_code (cosivm_token *tokens, long long** machine_code, long long* main) {
  assert(tokens != NULL);

  long long length = -1;
  cosivm_token *tmp = tokens;
  cosivm_hashtable labels;

  cosivm_hashtable_init(&labels);
  //assert(labels != NULL);

  while (tmp != NULL) {
    switch (tmp->type) {
    case Type(UNDEF): {
      fprintf(stderr, "Unknown token <%s>\n", tmp->token);
      cosivm_hashtable_cleanup(&labels);
      return 1;
      break; }
      
    case Type(NUM): {
      long long num = atoi(tmp->token);
      tmp->value = num;
      break; }

    case Type(REG): {
      cosivm_reg reg = cosivm_register(tmp->token);
      tmp->value = reg;
      break; }

    case Type(LBL): {
      cosivm_hashtable *res = cosivm_hashtable_set(&labels, tmp->token, tmp->pos);
      if (res == NULL) {
		fprintf(stderr, "Could not make label <%s>\n", tmp->token);
		cosivm_hashtable_cleanup(&labels);
		return 1;
      }

      long long instr = COSIVM_INSTR_NOP;
      tmp->value = instr;
      break; }

    case Type(FUNC): {
      cosivm_hashtable *res = cosivm_hashtable_get(&labels, tmp->token);
      if (res == NULL) {
		fprintf(stderr, "Unknown label <%s>\n", tmp->token);
		//assert(tokens != NULL);
		//assert(labels != NULL);

		cosivm_cleanup_tokens(tokens);
		cosivm_hashtable_cleanup(&labels);
		exit(1);
		//cosivm_exit_generator(tokens, labels, 1);
      }
      tmp->value = res->value;
      break; }

    case Type(VAR): {
      //not implemented yet
      break; }

    case Type(INSTR): {
      long long instr = cosivm_instruction(tmp->token);
      tmp->value = instr;
      break; }
    }

    /*printf("[%04lld] %5s (%5s) = %4lld\n",
      tmp->pos, tmp->token, carp_reverse_type[tmp->type], tmp->value);
    // */
    tmp = tmp->next;
    length++;
  }
//printf("parsed correctly, length:%lld\n",length);
  *machine_code = malloc(sizeof(tmp->value)*(length+1));
  //long long code[length];
  tmp = tokens;

  while (tmp != NULL) {
    //printf("copied [%lld]%lld\n",tmp->pos,tmp->value);
    (*machine_code)[tmp->pos] = tmp->value;
    tmp = tmp->next;
  }
  cosivm_hashtable *res = cosivm_hashtable_get(&labels, "main");
  *main = res->value;
  cosivm_hashtable_cleanup(&labels);
  return length;
}

long long cosivm_create_executable(char* fn, long long* machine_code, long long length, long long* main)
{
  //if(fn==NULL)
	fn="./output.cvmex";
  /*else
  {
	  //do nothing
	}*/
  long long res;
  printf("DEBUG:: length= %lld\n", length);
  FILE *fp = fopen(fn, "wb");
  assert(fp != NULL);
  res =  fwrite(machine_code, sizeof(long long), length,fp);
  printf("DEBUG:: res= %lld\n", res);
  fclose(fp);
  return res;
}
