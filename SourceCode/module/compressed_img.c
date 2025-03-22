// svd_compression.c
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <lapacke.h>

// Hàm thực hiện SVD và nén ảnh
void compute_svd(cv::Mat& channel, int k, cv::Mat& compressed) {
    int rows = channel.rows, cols = channel.cols;

    cv::Mat A;
    channel.convertTo(A, CV_32F);

    // Cấp phát bộ nhớ cho SVD
    float* U = (float*)malloc(rows * rows * sizeof(float));
    float* S = (float*)malloc(rows * sizeof(float));
    float* VT = (float*)malloc(cols * cols * sizeof(float));

    // Tính SVD bằng LAPACK
    int info = LAPACKE_sgesvd(LAPACK_ROW_MAJOR, 'S', 'S', rows, cols, A.ptr<float>(), cols, S, U, rows, VT, cols);

    if (info > 0) {
        printf("Lỗi: SVD không hội tụ!\n");
        return;
    }

    // Chỉ giữ lại k giá trị kỳ dị
    cv::Mat Uk(rows, k, CV_32F, U);
    cv::Mat Sk = cv::Mat::zeros(k, k, CV_32F);
    cv::Mat VkT(k, cols, CV_32F, VT);

    for (int i = 0; i < k; i++) {
        Sk.at<float>(i, i) = S[i];
    }

    // Tái tạo ảnh
    compressed = Uk * Sk * VkT;
    compressed.convertTo(compressed, CV_8U);

    free(U); free(S); free(VT);
}

// Hàm nén ảnh và lưu kết quả
void compress_image(cv::Mat& img, int k, cv::Mat& compressed_img) {
    cv::Mat channels[3], compressed_channels[3];
    cv::split(img, channels);

    for (int i = 0; i < 3; i++) {
        compute_svd(channels[i], k, compressed_channels[i]);
    }

    cv::merge(compressed_channels, 3, compressed_img);
}
