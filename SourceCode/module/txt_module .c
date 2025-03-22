// Read matrix from txt file (located in data folder)
#include <stdio.h>
#include <stdlib.h>

double* read_matrix_from_file(const char* filename, int* m, int* n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Không thể mở file!\n");
        return NULL;
    }
    fscanf(file, "%d %d", m, n);
    double* matrix = (double*)malloc((*m) * (*n) * sizeof(double));
    for (int i = 0; i < (*m) * (*n); i++) {
        fscanf(file, "%lf", &matrix[i]);
    }
    fclose(file);
    return matrix;
}