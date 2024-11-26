// #include "library.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_line(char *line);
void analyze_line(char *line);

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

/**
 * Function: analyze_line
 * ----------------------
 * Analyzes a single line from the log file.
 */

void analyze_line(const char *line) {
    // Example: Check for a specific keyword in the line
    if (strstr(line, "ERROR")) {
        printf("[ALERT] Found an error: %s\n", line);
        //todo: ERROR logic here
    }
    else if (strstr(line, "INFO")) {
        printf("[INFO] General information: %s\n", line);
        //todo: INFO logic here
    }
    else {
        printf("[DEBUG] Other line: %s\n", line);
        //todo: DEBUG logic here
    }
}

void process_line(char * line) {
  int len = strlen(line);
  char *token = strtok(line, " ");
  while (token != NULL) {
	analyze_line(token);
   	token = strtok(NULL, ", ");
  }
}