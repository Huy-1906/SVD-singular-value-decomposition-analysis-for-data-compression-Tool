// Load image as matrix
#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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