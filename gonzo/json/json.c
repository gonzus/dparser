#include <ctype.h>
#include <stdio.h>
#include <string.h>

// dparse.h must be included last so D_ParseNode_User exists
#include "json.h"
#include <dparse.h>

// #define FIXED_INPUT "{\"foo\": 4, \"bar\": [1,2,false]}"

// Defined in file generated from grammar
extern D_ParserTables parser_tables_gram;

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    D_Parser* parser = 0;
    D_ParseNode* node = 0;

    do {
        parser = new_D_Parser(&parser_tables_gram, sizeof(D_ParseNode_User));
        if (!parser) {
            break;
        }

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

            node = dparse(parser, line, len);
            if (!node) {
                printf("Could not parse [%d:%s]\n", len, line);
                break;
            }

            if (parser->syntax_errors) {
                printf("failure\n");
                continue;
            }

            printf("success\n");
            free_D_ParseNode(parser, node);
            node = 0;
#if defined(FIXED_INPUT)
            break;
#endif
        }

        if (node) {
            free_D_ParseNode(parser, node);
            node = 0;
        }
    } while (0);

    if (parser) {
        free_D_Parser(parser);
        parser = 0;
    }

    return 0;
}
