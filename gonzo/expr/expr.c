#include <ctype.h>
#include <stdio.h>
#include <string.h>

// dparse.h must be included after expr.h so D_ParseNode_User exists
#include "expr.h"
#include <dparse.h>

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
        parser->save_parse_tree = 1;

        while (1) {
            char line[256];
#if 1
            if (!fgets(line, 255, stdin)) {
                break;
            }
#else
            strcpy(line, "2+3*4+5*6");
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
            printf("value = %d\n", node->user.value);
            free_D_ParseNode(parser, node);
            node = 0;
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
