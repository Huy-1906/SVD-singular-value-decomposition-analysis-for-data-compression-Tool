#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <jpeglib.h>
#include <png.h>
#include <lapacke.h>

#define MAX_WIDTH 512
#define MAX_HEIGHT 512

// Hàm in ma trận ra terminal
void printMatrix(const char *name, double *matrix, int width, int height) {
    printf("\nMa trận %s:\n", name);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%4.0f ", matrix[i * width + j]);
        }
        printf("\n");
    }
}

// Hàm áp dụng SVD và giữ lại K giá trị kỳ dị
void applySVD(double *A, int m, int n, int k) {
    int lda = m, ldu = m, ldvt = n;
    double *S = (double *)malloc(n * sizeof(double));
    double *U = (double *)malloc(m * m * sizeof(double));
    double *VT = (double *)malloc(n * n * sizeof(double));
    double *superb = (double *)malloc((m < n ? m : n) * sizeof(double));

    // Tính SVD
    LAPACKE_dgesvd(LAPACK_ROW_MAJOR, 'A', 'A', m, n, A, lda, S, U, ldu, VT, ldvt, superb);

    // Giữ lại K giá trị kỳ dị lớn nhất
    for (int i = k; i < n; i++) S[i] = 0;

    // Khôi phục ma trận xấp xỉ A ≈ U * Σ * V^T
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i * n + j] = 0;
            for (int l = 0; l < k; l++) {
                A[i * n + j] += U[i * m + l] * S[l] * VT[l * n + j];
            }
        }
    }

    free(S);
    free(U);
    free(VT);
    free(superb);
}

// Đọc ảnh JPG, tách R, G, B
void processJPG(const char *filename, const char *output, int K) {
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

    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int channels = cinfo.output_components;

    unsigned char *image_data = (unsigned char *)malloc(width * height * channels);
    unsigned char **row_pointers = (unsigned char **)malloc(height * sizeof(unsigned char *));
    for (int i = 0; i < height; i++) row_pointers[i] = image_data + i * width * channels;

    while (cinfo.output_scanline < height) {
        jpeg_read_scanlines(&cinfo, &row_pointers[cinfo.output_scanline], height - cinfo.output_scanline);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);

    // Tách R, G, B
    double *R = (double *)malloc(width * height * sizeof(double));
    double *G = (double *)malloc(width * height * sizeof(double));
    double *B = (double *)malloc(width * height * sizeof(double));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = (i * width + j) * channels;
            R[i * width + j] = image_data[index];
            G[i * width + j] = image_data[index + 1];
            B[i * width + j] = image_data[index + 2];
        }
    }

    // In ma trận trước khi nén
    printMatrix("R", R, width, height);
    printMatrix("G", G, width, height);
    printMatrix("B", B, width, height);

    // Áp dụng SVD
    applySVD(R, height, width, K);
    applySVD(G, height, width, K);
    applySVD(B, height, width, K);

    // In ma trận sau khi nén
    printMatrix("R nén", R, width, height);
    printMatrix("G nén", G, width, height);
    printMatrix("B nén", B, width, height);

    // Chuyển về ảnh và lưu lại
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = (i * width + j) * channels;
            image_data[index] = (unsigned char)R[i * width + j];
            image_data[index + 1] = (unsigned char)G[i * width + j];
            image_data[index + 2] = (unsigned char)B[i * width + j];
        }
    }

    free(R);
    free(G);
    free(B);

    // Xuất ảnh JPG mới
    struct jpeg_compress_struct cinfo_out;
    struct jpeg_error_mgr jerr_out;
    FILE *outfile = fopen(output, "wb");

    if (!outfile) {
        perror("Lỗi ghi file");
        free(image_data);
        return;
    }

    cinfo_out.err = jpeg_std_error(&jerr_out);
    jpeg_create_compress(&cinfo_out);
    jpeg_stdio_dest(&cinfo_out, outfile);

    cinfo_out.image_width = width;
    cinfo_out.image_height = height;
    cinfo_out.input_components = channels;
    cinfo_out.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo_out);
    jpeg_set_quality(&cinfo_out, 90, TRUE);
    jpeg_start_compress(&cinfo_out, TRUE);

    while (cinfo_out.next_scanline < cinfo_out.image_height) {
        jpeg_write_scanlines(&cinfo_out, &row_pointers[cinfo_out.next_scanline], 1);
    }

    jpeg_finish_compress(&cinfo_out);
    jpeg_destroy_compress(&cinfo_out);
    fclose(outfile);

    free(image_data);
    free(row_pointers);
}

int main() {
    const char *inputFile = "image.jpg";  // Đổi thành file của bạn
    const char *outputFile = "compressed.jpg";

    int K;
    printf("Nhập số hạng kỳ dị K: ");
    scanf("%d", &K);

    processJPG(inputFile, outputFile, K);

    printf("Nén ảnh thành công! Lưu tại %s\n", outputFile);
    return 0;
}
