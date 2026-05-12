// REPL LISPY
#include <stdio.h>
#include <stdlib.h>


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
    // Print version and exit information
    puts("Lispy Version 0.0.0.0.1");
    puts("Any input you throw, it can handle.");
    puts("Press ctrl+c to exit\n");

    while(1) {
        // Prompt and input
        char *input = readline("whisp > ");

        // Add input to history
        add_history(input);

        // Echo input
        printf("'%s'? I don't understand :)\n", input);

        free(input);
    }

    return 0;
}
