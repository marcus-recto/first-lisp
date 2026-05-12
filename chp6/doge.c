// REPL LISPY
#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"


#ifdef _WIN32
#include <string.h>

static char buffer[2048];

// Pseudo readline function
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

// Fake add history function
// Windows already shows input history through arrows
void add_history(char* unused) {}

// otherwise include editline headers
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv) {
    // Create parsers
    mpc_parser_t* Adjective = mpc_new("adjective");
    mpc_parser_t* Noun = mpc_new("noun");
    mpc_parser_t* Phrase = mpc_new("phrase");
    mpc_parser_t* Doge = mpc_new("doge");

    mpca_lang(MPCA_LANG_DEFAULT,
    "\
        adjective : \"wow\" | \"many\" | \"so\" | \"such\" ; \
        noun      : \"lisp\" | \"language\" | \"c\" | \"book\" ; \
        phrase    : <adjective> <noun> ; \
        doge      : /^/ <phrase> /$/; \
    ",
    Adjective, Noun, Phrase, Doge);
    

    // Print version and exit information
    puts("Lispy Version 0.0.0.0.1");
    puts("Press ctrl+c to exit\n");

    while(1) {
        // Prompt and input
        char *input = readline("doge > ");

        // Add input to history
        add_history(input);


        // Attempt to parse user input
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Doge, &r)) {
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        free(input);
    }
    mpc_cleanup(4, Adjective, Noun, Phrase, Doge);

    return 0;
}
