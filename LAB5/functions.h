#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "bitops.h"

/* Generic declarations */

static struct option long_options[] = {
    {"function name", required_argument, 0,  'f' },
    {"1",             required_argument, 0,  '1' },
    {"2",             optional_argument, 0,  '2' },
};

static void print_usage(char* cmd) {
    printf("Usage: %s [-h] [-f <name> [-1|-2|-3 <val>]*]\n", cmd);
    printf("  -f <name> Name of function to test\n");
    printf("  -1 <val>  Specify first function argument\n");
    printf("  -2 <val>  Specify second function argument\n");
    printf("  -h        Print usage\n");
    exit(1);
}

/* Function specific declarations */
typedef struct fn_ent {
    char *name; // function name
    int (*fn)(int, ...); // function pointer
    int nargs; // number of arguments passed to function
} fn_ent_t;

static fn_ent_t fn_table[] = {
    {"and_op", (int (*)(int, ...)) and_op, 2},
    {"or_op", (int (*)(int, ...)) or_op, 2},
    {"xor_op", (int (*)(int, ...)) xor_op, 2},
    {"masking_and", (int (*)(int, ...)) masking_and, 2},
    {"masking_or", (int (*)(int, ...)) masking_or, 2},
    {"masking_xor", (int (*)(int, ...)) masking_xor, 2},
    {"shifting_left_op", (int (*)(int, ...)) shifting_left_op, 2},
    {"shifting_right_op", (int (*)(int, ...)) shifting_right_op, 2},
    {"bang", (int (*)(int, ...)) bang, 1}
};

int (*fn_lookup(const char *fn_name))(int, ...) {
    int i;

    if (!fn_name) {
        return NULL;
    }

    for (i = 0; i < sizeof(fn_table)/sizeof(fn_table[0]); ++i) {
        if (!strcmp(fn_name, fn_table[i].name)) {
	    return fn_table[i].fn;
        }
    }
    return NULL;
}

int get_fnargs(const char *fn_name) {
    int i;

    if (!fn_name) {
        return -1;
    }

    for (i = 0; i < sizeof(fn_table)/sizeof(fn_table[0]); ++i) {
        if (!strcmp(fn_name, fn_table[i].name)) {
            return fn_table[i].nargs;
        }
    }
    return -1;
}

int convert_optarg(char* optarg, int base) {
    char* endptr;
    int arg = strtol(optarg, &endptr, base);
    if ((arg == 0) && (strcmp(endptr, "\0"))) {
	/* If a conversion error occurred, display a message and exit */
        printf("Conversion error: %s is not in base %d\n", optarg, base);
        exit(EXIT_FAILURE);
    }
    return arg;
}

