#include "svd_compression.h"
#include <lapacke.h>
#include <stdlib.h>

void apply_svd(double *A, int width, int height, int K) {
    int lda = height, ldu = height, ldvt = width;
    double *S = (double *)malloc(width * sizeof(double));
    double *U = (double *)malloc(height * height * sizeof(double));
    double *VT = (double *)malloc(width * width * sizeof(double));
    double *superb = (double *)malloc((height < width ? height : width) * sizeof(double));

    // Tính SVD
    LAPACKE_dgesvd(LAPACK_ROW_MAJOR, 'A', 'A', height, width, A, lda, S, U, ldu, VT, ldvt, superb);

    // Giữ lại K giá trị kỳ dị
    for (int i = K; i < width; i++) S[i] = 0;

    // Tái tạo ma trận
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            A[i * width + j] = 0;
            for (int l = 0; l < K; l++) {
                A[i * width + j] += U[i * height + l] * S[l] * VT[l * width + j];
            }
        }
    }

    free(S);
    free(U);
    free(VT);
    free(superb);
}
