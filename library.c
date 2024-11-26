// #include "library.h"

#include <stdio.h>
#include <stdlib.h>

void process_line(char *line);

int main(int const argc, char ** argv) {
    if (argc != 2) {
        printf("Usage: ./logfile <%s>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *logfile = fopen(argv[1], "r");
    if (logfile == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    //initialize line variable
    char line[1024];
    while (fgets(line, sizeof(line), logfile)) {
        process_line(line);
    }

    //close logfile
    fclose(logfile);
    return EXIT_SUCCESS;
}
