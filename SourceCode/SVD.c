// Copyright © 2025 Ho Chi Minh City University of Technology, HCMUT
// Created by Ly Gia Huy - 2452391
// Email: huy.lygiahuy2024bk@hcmut.edu.vn

#include <stdio.h> 
#include <stdlib.h> 
#include <lapacke.h> 
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Load image as matrix
double *load_image_as_matrix(const char* filename, int* width, int* height) {
    int channels;
    unsigned char* img = stbi_load(filename, width, height, &channels, 1);
    if (!img) {
        printf("Không thể đọc ảnh!\n");
        return NULL;
    }
    double* matrix = (double*)malloc((*width) * (*height) * sizeof(double));
    for (int i = 0; i < (*width) * (*height); i++) {
        matrix[i] = (double)img[i];  
    }
    stbi_image_free(img);
    return matrix;
}

// Read matrix from txt file
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

// Print matrix
void print_matrix(double *A, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%8.4f ", A[i * col + j]);
        }
        printf("\n");
    }
}

int main() {
    int m, n;
    double *A = NULL;  // Sửa lỗi khai báo sai kiểu
    int choice;
    
    printf("Choose the data type you want to convert: \n");
    printf("1. File TXT\n");
    printf("2. Image\n");
    printf("3. CSV file\n");
    scanf("%d", &choice);
    getchar();
    
    char filename[100];
    printf("Enter the file name: ");
    scanf("%s", filename);

    switch (choice) {
        case 1:
            A = read_matrix_from_file(filename, &m, &n);
            break;
        case 2:
            A = load_image_as_matrix(filename, &m, &n);
            break;
        case 3:
            A = read_csv_as_matrix(filename, &m, &n);
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }

    if (A == NULL) {
        printf("Lỗi khi đọc dữ liệu từ file!\n");
        return 1;
    }

    // Allocate memory for SVD
    double *U = (double*)malloc(m * m * sizeof(double));
    double *S = (double*)malloc(m * n * sizeof(double));
    double *VT = (double*)malloc(n * n * sizeof(double));
    double *superb = (double*)malloc((m < n ? m : n) * sizeof(double));

    // Perform SVD
    int info = LAPACKE_dgesvd(LAPACK_ROW_MAJOR, 'A', 'A', m, n, A, n, S, U, m, VT, n, superb);
    
    if (info > 0) {
        printf("SVD không hội tụ!\n");
        return -1;
    }

    // Print results
    printf("U = \n");
    print_matrix(U, m, m);

    printf("Vector S = \n");
    for (int i = 0; i < m; i++) {
        printf("%8.4f ", S[i]);
    }
    printf("\n");

    printf("VT = \n");
    print_matrix(VT, n, n);

    // Free memory
    free(A);
    free(U);
    free(S);
    free(VT);
    free(superb);

    return 0;
}
