#include <stdio.h>
#include <stdlib.h>

// Read CSV file as matrix
double* read_csv_as_matrix(const char* filename, int* rows, int* cols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Không thể mở file CSV!\n");
        return NULL;
    }
    double* matrix = (double*)malloc(100 * 100 * sizeof(double));
    *rows = 0;
    *cols = 0;
    char line[1024];
    while (fgets(line, 1024, file)) {
        *cols = 0;
        char* token = strtok(line, ",");
        while (token) {
            matrix[(*rows) * 100 + (*cols)] = atof(token);
            token = strtok(NULL, ",");
            (*cols)++;
        }
        (*rows)++;
    }
    fclose(file);
    return matrix;
}
