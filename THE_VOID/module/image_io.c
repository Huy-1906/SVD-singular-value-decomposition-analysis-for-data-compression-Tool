#include "image_io.h"
#include <jpeglib.h>

void print_matrix(const char *name, double *matrix, int width, int height) {
    printf("\nMa trận %s:\n", name);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%4.0f ", matrix[i * width + j]);
        }
        printf("\n");
    }
}

void read_image(const char *filename, double **R, double **G, double **B, int *width, int *height) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file = fopen(filename, "rb");

    if (!file) {
        perror("Lỗi mở file");
        return;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    *width = cinfo.output_width;
    *height = cinfo.output_height;
    int channels = cinfo.output_components;

    unsigned char *image_data = (unsigned char *)malloc((*width) * (*height) * channels);
    unsigned char **row_pointers = (unsigned char **)malloc((*height) * sizeof(unsigned char *));
    for (int i = 0; i < *height; i++) row_pointers[i] = image_data + i * (*width) * channels;

    while (cinfo.output_scanline < *height) {
        jpeg_read_scanlines(&cinfo, &row_pointers[cinfo.output_scanline], *height - cinfo.output_scanline);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);

    // Tách R, G, B
    *R = (double *)malloc((*width) * (*height) * sizeof(double));
    *G = (double *)malloc((*width) * (*height) * sizeof(double));
    *B = (double *)malloc((*width) * (*height) * sizeof(double));

    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            int index = (i * (*width) + j) * channels;
            (*R)[i * (*width) + j] = image_data[index];
            (*G)[i * (*width) + j] = image_data[index + 1];
            (*B)[i * (*width) + j] = image_data[index + 2];
        }
    }

    free(image_data);
    free(row_pointers);
}
