// Copyright © 2025 Ho Chi Minh City University of Technology, HCMUT
// Created by Ly Gia Huy - 2452391
// Email: huy.lygiahuy2024bk@hcmut.edu.vn

#include "image_io.h"
#include "svd_compression.h"
#include "image_merge.h"

int main() {
    const char *inputFile = "image.jpg";
    const char *outputFile = "compressed.jpg";

    int width, height, K;
    double *R, *G, *B;

    printf("Nhập số hạng kỳ dị K: ");
    scanf("%d", &K);

    read_image(inputFile, &R, &G, &B, &width, &height);
    apply_svd(R, width, height, K);
    apply_svd(G, width, height, K);
    apply_svd(B, width, height, K);
    save_image(outputFile, R, G, B, width, height);

    free(R); free(G); free(B);
    printf("Ảnh đã nén và lưu tại %s\n", outputFile);
    return 0;
}
