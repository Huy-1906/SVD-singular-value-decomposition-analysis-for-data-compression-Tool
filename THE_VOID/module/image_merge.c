#include "image_merge.h"
#include <jpeglib.h>

void save_image(const char *filename, double *R, double *G, double *B, int width, int height) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *outfile = fopen(filename, "wb");

    if (!outfile) {
        perror("Lỗi ghi file");
        return;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 90, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    unsigned char *image_data = (unsigned char *)malloc(width * height * 3);
    for (int i = 0; i < width * height; i++) {
        image_data[3 * i] = (unsigned char)R[i];
        image_data[3 * i + 1] = (unsigned char)G[i];
        image_data[3 * i + 2] = (unsigned char)B[i];
    }

    while (cinfo.next_scanline < height) {
        jpeg_write_scanlines(&cinfo, &image_data + cinfo.next_scanline * width * 3, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);
    free(image_data);
}
