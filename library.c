// #include "library.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void process_line(char *line);
void analyze_line(const char *line);

int containsError(const char *line){
    return strstr(line, "ERROR") != NULL;
};

int containsAlert(const char *line){
    return strstr(line, "ALERT") != NULL;
}

int containsInfo(const char *line){
    return strstr(line, "INFO") != NULL;
}

int main(int const argc, char ** argv) {
    /* clear buff */
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    const char *inputfile = argv[1];
    const char *outputfile = argv[2];

    if (argc != 3) {
        printf("Usage: ./logfile <%s>\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *logfile = fopen(inputfile, "r");
    if (logfile == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    FILE *logOutput = fopen(outputfile, "w");
    if(!logOutput){
        printf("Error opening file ", outputfile);
        return EXIT_FAILURE;
    }

    int errCount ,infoCount = 0;
    //initialize line variable
    char line[4096];
    while (fgets(line, sizeof(line), logfile)) {
        process_line(line);
    }

    //close logfile
    fclose(logfile);
    fclose(logOutput);

    return EXIT_SUCCESS;
}

/**
 * Function: analyze_line
 * ----------------------
 * Analyzes a single line from the log file.
 */

void analyze_line(const char *line) {
    size_t errCount = 0;
    // Example: Check for a specific keyword in the line
    for(size_t i = 0; i < strlen(line); i++){
        if (containsError(line)) {
            errCount++;
            printf("[ALERT] Found an error: %s\n", line);
            //todo: ERROR logic here
        }
        else if (containsInfo(line)) {
            int infoC = 0;
            printf("[INFO] General information: %s\n", line);
            //todo: INFO logic here
        }
        else {
            printf("[DEBUG] Other line: %s\n", line);
            //todo: DEBUG logic here
        }
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
