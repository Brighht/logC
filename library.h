#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <regex.h>

// Log keywords
#define LOG_ERROR 0
#define LOG_WARNING 1
#define LOG_INFO 2
#define LOG_DEBUG 3


#define MAX_LINE_LENGTH 4096
#define MAX_TIMESTAMP_LENGTH 26
#define MAX_FILE_SIZE (10 * 1024 * 1024)  // 10MB

// Structure to hold log statistics
typedef struct {
    int errorCount;
    int warningCount;
    int infoCount;
    int debugCount;
    time_t startTime;
    time_t endTime;
} LogStats;

// // Structure to hold log configuration
// typedef struct {
//     int minLogLevel;        // Minimum log level to process
//     char *filterKeyword;    // Keyword to filter logs
//     char *dateFrom;         // Start date filter
//     char *dateTo;          // End date filter
// } LogConfig;

// Function declarations
void process_line(char *line, LogStats *stats);
void analyze_line(const char *line, LogStats *stats, FILE *output);
int contains_level(const char *line, const char *level);
void print_summary(FILE *output,LogStats *stats);
char* extract_timestamp(const char *line, char *timestamp);
// void print_summary_json(FILE *output, LogStats *stats);
// int match_pattern(const char *line, const char *pattern);
// void rotate_log_file(const char *filename);


#define ANSI_RED     "\x1b[31m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_RESET   "\x1b[0m"

#endif 