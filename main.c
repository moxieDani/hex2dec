#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apis.h"

struct test_case {
    const char *hexstr;
    const char *decstr;
};
 
int main(void)
{
    // Test cases for hexstr_to_decstr()
    const struct test_case cases[] = {
        {"0", "0"},
        {"000", "0"},
        {"FFFFFFFF", "4294967295"},
        {"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "5444517870735015415413993718908291383295"},
        {NULL, NULL}
    };
    const struct test_case *t;
 
    for (t = cases; t->hexstr != NULL; t++) {
        char *decstr;
 
        decstr = hexstr_to_decstr(t->hexstr);
 
        if (strcmp(decstr, t->decstr) == 0) {
            printf("[pass] %s -> %s\n", t->hexstr, decstr);
        } else {
            printf("[fail] %s -> %s (expected %s)\n", t->hexstr, decstr, t->decstr);
        }
 
        free(decstr);
    }
 
    return 0;
}