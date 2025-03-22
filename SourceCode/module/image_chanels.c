// Print the RGB channels of an image
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
using namespace cv;

//link opencv lib 


// Print the RGB channels of an image
void print_matrix(cv::Mat& channel, const char* name) {
    printf("\n=== Kênh %s ===\n", name);
    for (int i = 0; i < channel.rows; i++) {
        for (int j = 0; j < channel.cols; j++) {
            printf("%3d ", channel.at<uchar>(i, j));
        }
        printf("\n");
    }
}

// Hàm tách và in ma trận 3 kênh màu
void print_channels(cv::Mat& img) {
    cv::Mat channels[3];
    cv::split(img, channels);

    print_matrix(channels[2], "R (Red)");
    print_matrix(channels[1], "G (Green)");
    print_matrix(channels[0], "B (Blue)");
}
