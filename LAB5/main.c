#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "bitops.h"
#include "functions.h"

int main(int argc, char *argv[]) {
    int opt = 0;
    int long_index = 0;
    char* fname;
    int arg1 = 0, arg2 = 0;
    int base;

    while ((opt = getopt(argc, argv, "f:1:2:3:h:")) != -1) {
	base = 10; // default
        switch (opt) {
             case 'f' :
		fname = optarg;
                break;
             case '1' :
		if (strstr(optarg, "0x") != NULL) base = 16;
		arg1 = convert_optarg(optarg, base);
                break;
             case '2' :
		if (strstr(optarg, "0x") != NULL) base = 16;
                arg2 = convert_optarg(optarg, base);
                break;
             default:
		print_usage(argv[1]);
                exit(EXIT_FAILURE);
        }
    }

    if (strncmp(fname, "bit_conversion", 14) == 0) {
      bit_conversion(arg1);
    } else {
      int fn_args = get_fnargs(fname); // get function arguments
      if (fn_args != -1) {
	  int result;
	  switch(fn_args) {
	       case (1): {
		  result = fn_lookup(fname)(arg1);
		  break;
	       }
	       case (2): {
		  result = fn_lookup(fname)(arg1, arg2);
		  break;
	       }
	       default:
		  print_usage(argv[1]);
		  exit(EXIT_FAILURE);
	  }

	  if (strstr(fname, "masking_") != NULL || strstr(fname, "shifting_") != NULL) {
	    printf("0x%x\n", result);
	  } else {
            printf("%d\n", result);
	  }
      } else {
	  print_usage(argv[1]);
   	  exit(EXIT_FAILURE);
      }
    }
    return 0;
}

