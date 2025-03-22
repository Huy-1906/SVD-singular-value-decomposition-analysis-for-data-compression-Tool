#include <stdio.h>
#include <opencv2/opencv.hpp>

void compress_image(const char* input_path, int k, const char* output_path) {
    cv::Mat img = cv::imread(input_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        printf("Cannot read image file\n");
        return;
    }

    // Chuyển sang không gian màu YCrCb
    cv::Mat ycrcb;
    cv::cvtColor(img, ycrcb, cv::COLOR_BGR2YCrCb);

    // Tách kênh màu
    std::vector<cv::Mat> channels;
    cv::split(ycrcb, channels);

    // Áp dụng SVD lên từng kênh
    for (size_t i = 0; i < channels.size(); i++) {
        cv::Mat U, S, V;
        cv::SVD::compute(channels[i], S, U, V);

        // Giữ lại k giá trị đầu
        S = S(cv::Range(0, k), cv::Range(0, k));
        U = U(cv::Range::all(), cv::Range(0, k));
        V = V(cv::Range(0, k), cv::Range::all());

        // Khôi phục ảnh
        channels[i] = U * cv::Mat::diag(S) * V;
    }

    // Gộp kênh màu lại
    cv::merge(channels, ycrcb);
    cv::cvtColor(ycrcb, img, cv::COLOR_YCrCb2BGR);

    // Lưu ảnh
    cv::imwrite(output_path, img);
    printf("Compressed image saved to %s\n", output_path);
}

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Usage: %s <input_image> <k_value> <output_image>\n", argv[0]);
        return -1;
    }
    compress_image(argv[1], atoi(argv[2]), argv[3]);
    return 0;
}
