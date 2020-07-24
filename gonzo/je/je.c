#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "json_api.h"

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    while (1) {
        char line[256];
#if defined(FIXED_INPUT)
        strcpy(line, FIXED_INPUT);
#else
        if (!fgets(line, 255, stdin)) {
            break;
        }
#endif
        int len = strlen(line);
        int j = 0;
        for (j = len - 1; j >= 0; --j) {
            if (!isspace(line[j])) {
                break;
            }
        }
        len = j + 1;
        line[len] = '\0';

        int rc = json_parse(line, len);
        printf("[%d:%s] => %d\n", len, line, rc);

#if defined(FIXED_INPUT)
        break;
#endif
    }

    return 0;
}
