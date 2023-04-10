#define _GNU_SOURCE

#include "include/io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char* read_steel_file(const char* filename) {
    FILE* fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("Could not read file '%s'\n", filename);
        exit(1);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    char* buffer = calloc(1, sizeof(char));
    buffer[0] = '\0';

    while ((read = getline(&line, &len, fp)) != -1) {
        buffer = realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
        strcat(buffer, line);
    }

    fclose(fp);

    if(line)
        free(line);

    return buffer;
}