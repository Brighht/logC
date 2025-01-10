#include "library.h"

int contains_level(const char *line, const char *level) {
    return strstr(line, level) != NULL;
}

char* extract_timestamp(const char *line, char *timestamp) {
    // Assuming timestamp format: [YYYY-MM-DD HH:MM:SS]
    char *start = strchr(line, '[');
    char *end = strchr(line, ']');
    
    if (start && end && end > start) {
        size_t len = end - start - 1;
        strncpy(timestamp, start + 1, len);
        timestamp[len] = '\0';
        return timestamp;
    }
    return NULL;
}

void analyze_line(const char *line, LogStats *stats, FILE *output) {
    char timestamp[MAX_TIMESTAMP_LENGTH] = {0};
    char *time_str = extract_timestamp(line, timestamp);
    const char *prefix = time_str ? timestamp : "NO_TIMESTAMP";

    if (contains_level(line, "ERROR")) {
        stats->errorCount++;
        fprintf(output, "[%s][ERROR] %s", prefix, line);
        fprintf(stderr, ANSI_RED "[ERROR] Found error in log: %s" ANSI_RESET, line);
    }
    else if (contains_level(line, "WARNING")) {
        stats->warningCount++;
        fprintf(output, "[%s][WARNING] %s", prefix, line);
    }
    else if (contains_level(line, "INFO")) {
        stats->infoCount++;
        fprintf(output, "[%s][INFO] %s", prefix, line);
    }
    else {
        stats->debugCount++;
        fprintf(output, "[%s][DEBUG] %s", prefix, line);
    }
}

void process_line(char *line, LogStats *stats) {
    // Remove newline if present
    size_t len = strlen(line);
    if (len > 0 && line[len-1] == '\n') {
        line[len-1] = '\0';
    }
}

void print_summary(FILE *output, LogStats *stats) {
    time_t duration = stats->endTime - stats->startTime;
    
    fprintf(output, "\n=== Log Analysis Summary ===\n");
    fprintf(output, "Analysis Duration: %ld seconds\n", duration);
    fprintf(output, "Total Errors: %d\n", stats->errorCount);
    fprintf(output, "Total Warnings: %d\n", stats->warningCount);
    fprintf(output, "Total Info Messages: %d\n", stats->infoCount);
    fprintf(output, "Total Debug Messages: %d\n", stats->debugCount);
    fprintf(output, "Total Messages: %d\n", 
            stats->errorCount + stats->warningCount + 
            stats->infoCount + stats->debugCount);
    fprintf(output, "========================\n");
}

int main(int argc, char **argv) {
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputfile = argv[1];
    const char *outputfile = argv[2];

    FILE *logfile = fopen(inputfile, "r");
    if (logfile == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    FILE *logOutput = fopen(outputfile, "w");
    if (!logOutput) {
        fprintf(stderr, "Error opening output file %s: %s\n", outputfile, strerror(errno));
        fclose(logfile);
        return EXIT_FAILURE;
    }

    // Initialize statistics
    LogStats stats = {0};
    time(&stats.startTime);

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), logfile)) {
        process_line(line, &stats);
        analyze_line(line, &stats, logOutput);
    }

    time(&stats.endTime);
    print_summary(logOutput, &stats);

    // Print console summary
    printf("Processing complete.\n");
    printf("Found %d errors, %d warnings, %d info messages, and %d debug messages.\n",
           stats.errorCount, stats.warningCount, stats.infoCount, stats.debugCount);

    fclose(logfile);
    fclose(logOutput);

    return EXIT_SUCCESS;
}
