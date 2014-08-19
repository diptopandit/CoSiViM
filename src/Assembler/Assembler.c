#include "../Include/Assembler.h"

int main(int argc, char* argv[])
{
	static struct option long_options[] = {
    {"version", 0, 0, 'v'},
    {"license", 0, 0, 'l'},
    {"warranty", 0, 0, 'w'},
    {"conditions", 0, 0, 'c'},
    {"file", 1, 0, 'f'},
    {"help", 0, 0, 'h'},
    {NULL, 0, NULL, 0},
  };

  cosivm_option opts = {0, 0, 0, 0};

  int c;
  int option_index = 0;
  while ((c = getopt_long(argc, argv, "vlwcf:h", long_options, &option_index)) != -1) {
    int this_option_optind = optind ? optind : 1;
    switch (c) {
    case 0:
      printf("option %s", long_options[option_index].name);
      if (optarg)
		printf(" with arg %s", optarg);
      puts("");
     break;

    case 'v':
      // version
      cosivm_print_version();
      break;

    case 'l':
      // license
      cosivm_print_license();
      break;

    case 'w':
      // warranty
      cosivm_print_warranty();
      break;

    case 'c':
      // conditions
      cosivm_print_conditions();
      break;

    case 'f':
      // file
      cosivm_run_assembler(optarg);
      break;

    case 'h':
      // help
      printf("help msg\n");
      break;

    default:
      puts("For usage, run `cvmas -h' or `cvmas --help'.");
      break;
    }
  }

  return 0;
}


void cosivm_print_version () {
  printf("cosivm %1.1f\n", COSIVM_ASEMBLER_VERSION);
}

void cosivm_print_license () {
  puts("cosivm  Copyright (C) 2014  Dipta Pandit\n\
    This program comes with ABSOLUTELY NO WARRANTY; for details type `cbmas -w'.\n\
    This is free software, and you are welcome to redistribute it\n\
    under certain conditions; type `cvmas -c' for details.");
}

void cosivm_print_warranty () {
  puts("THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.");
}

void cosivm_print_conditions () {
  puts("See LICENSE.txt or http://www.gnu.org/licenses/gpl-3.0.txt");
}

void cosivm_run_assembler (char *fn) {
  cosivm_token *tokens = cosivm_tokenize(fn);
  if (tokens == NULL) {
    fprintf(stderr, "Something went wrong with tokenization.\n");
    exit(1);
  }
  long long* machine_code;
  long long res = cosivm_create_machine_code(tokens,&machine_code);
  printf("Machine code: \n");
  while(res>=0)
	  printf("%lld\n",machine_code[res--]);
  //if(res) res = cosivm_create_executable(fn, machine_code);
  cosivm_cleanup_tokens(tokens);
  //cosivm_cleanup_code(machine_code);
}
