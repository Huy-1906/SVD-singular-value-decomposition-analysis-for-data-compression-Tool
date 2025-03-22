// Copyright © 2025 Ho Chi Minh City University of Technology, HCMUT
// Created by Ly Gia Huy - 2452391
// Email: huy.lygiahuy2024bk@hcmut.edu.vn

#include <stdio.h>
#include <opencv2/opencv.hpp>

// Khai báo các hàm từ module khác
void print_channels(cv::Mat& img);
void compress_image(cv::Mat& img, int k, cv::Mat& compressed_img);

int main() {
    cv::Mat img = cv::imread("image.jpg");

    if (img.empty()) {
        printf("Lỗi: Không thể mở ảnh!\n");
        return -1;
    }

    printf("Ảnh gốc:\n");
    print_channels(img);

    int k = 50; // Chọn mức nén
    cv::Mat compressed_img;
    compress_image(img, k, compressed_img);

    printf("\nẢnh sau khi nén:\n");
    print_channels(compressed_img);

    cv::imwrite("compressed_image.jpg", compressed_img);
    printf("\nĐã lưu ảnh nén: compressed_image.jpg\n");

    return 0;
}