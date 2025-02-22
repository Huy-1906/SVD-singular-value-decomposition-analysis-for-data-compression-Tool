// Copyright © 2025 Ho Chi Minh City University of Technology, HCMUT
// Created by Ly Gia Huy -2452391
// Email: huy.lygiahuy2024bk@hcmut.edu.vn
// Personal contact: giahuy196cv@gmail.com

/*Sumary: This program is used to convert the input data in to specific type. Then we are using 
lapacke.h library to calculate the SVD of the matrix. The result (U, S, VT) will be printed out in the console
*/

#define STB_IMAGE_IMPLEMENTATION
#include  <stdio.h> //To print out the result
#include  <stdlib.h> //To use malloc function
#include <lapacke.h> //To use SVD function
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// turn the picture into the matrix
// convert the picture into grayscale typpe and save as real number matrix

double * load_image_as_matrix(const char* filename, int* width, int* height) {
    int channels; //Channels which means color channels
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

// Read the matrix from the txt file
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

// Read the CSV as matrix
double* read_csv_as_matrix(const char* filename, int* rows, int* cols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Không thể mở file CSV!\n");
        return NULL;
    }
    double* matrix = (double*)malloc(100 * 100 * sizeof(double)); // Giới hạn 100x100
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

// print the matrix
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
    double A;
    // Choose which data type you want to convert
    int choice;
    printf("Choose the data type you want to convert: \n");
    printf("1. file txt\n");
    printf("2. Image \n");
    printf("3. CSV file\n");
    scanf("%d", &choice);
    getchar(); // newline character handling
    
    char filename[100];
    printf("Enter the file name: ");
    scanf("%s", filename);

    //input selecton processing
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
}    
// Initialize matrices U, S, VT to perform SVD
double *U= (double*)malloc(m * m * sizeof(double));
double *S= (double*)malloc(m * n * sizeof(double));
double *VT= (double*)malloc(n * n * sizeof(double));
double *superb = (double*)malloc((m < n ? m : n) * sizeof(double)); //superb (super-diagonal elements buffer) to store the super-diagonal elements of the diagonal matrix   

// Perform SVD degenerate value analysis
int info = LAPACKE_dgesvd(LAPACK_ROW_MAJOR, 'A', 'A', m, n, A, n, S, U, m, VT, n, superb);

if (info > 0) {
    printf("SVD failed to converge!\n"); //translate into vietnamese means "SVD không hội tụ!"
    return -1;
}

// Print out the result of matrices U, S, VT
printf("U = \n");
print_matrix(U, m, m);

printf("Vector S = \n");
for (int i = 0; i < m; i++) {
    printf("&8.4f", S[i])
    printf("\n");
}

{
printf("VT = \n");
print_matrix(VT, n, n);

// Free the memory
free(A);
free(U);
free(S);
free(VT);

return 0;
}