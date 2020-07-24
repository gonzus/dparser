// dparse.h must be included last so D_ParseNode_User exists
#include <stdio.h>
#include "expr_api.h"
#include "expr_parser.h"
#include <dparse.h>

// Defined in file generated from grammar
extern D_ParserTables parser_tables_expr;

int expr_evaluate(char* str, int len) {
    D_Parser* parser = 0;
    D_ParseNode* node = 0;
    int value = 0;

    do {
        parser = new_D_Parser(&parser_tables_expr, sizeof(D_ParseNode_User));
        if (!parser) {
            fprintf(stderr, "Could not create expr parser\n");
            break;
        }
        parser->save_parse_tree = 1;

        node = dparse(parser, str, len);
        if (!node) {
            fprintf(stderr, "Could not parse [%d:%s]\n", len, str);
            break;
        }

        if (parser->syntax_errors) {
            fprintf(stderr, "Could not evaluata [%d:%s]\n", len, str);
            break;
        }

        value = node->user.value;
    } while (0);

    if (node) {
        free_D_ParseNode(parser, node);
        node = 0;
    }

    if (parser) {
        free_D_Parser(parser);
        parser = 0;
    }

    return value;
}
