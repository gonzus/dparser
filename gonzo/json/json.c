#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <dparse.h>

// Defined in file generated from grammar
extern D_ParserTables parser_tables_gram;

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    D_Parser* parser = new_D_Parser(&parser_tables_gram, 0);
    while (1) {
        char line[256];
        if (!fgets(line, 255, stdin)) {
            break;
        }

        int len = strlen(line);
        int j = 0;
        for (j = len - 1; j >= 0; --j) {
            if (!isspace(line[j])) {
                break;
            }
        }
        len = j + 1;
        line[len] = '\0';

        if (!dparse(parser, line, len)) {
            printf("Could not parse [%d:%s]\n", len, line);
            break;
        }

        if (parser->syntax_errors) {
            printf("failure\n");
            continue;
        }

        printf("success\n");
    }
    free_D_Parser(parser);
    return 0;
}
