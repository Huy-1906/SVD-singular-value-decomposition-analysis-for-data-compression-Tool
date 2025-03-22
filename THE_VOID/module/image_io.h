#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include <stdio.h>
#include <stdlib.h>

void read_image(const char *filename, double **R, double **G, double **B, int *width, int *height);
void print_matrix(const char *name, double *matrix, int width, int height);

#endif
