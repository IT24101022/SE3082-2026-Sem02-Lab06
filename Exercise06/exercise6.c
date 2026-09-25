#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000
#define STRIP_SIZE 32

int main() {

    double *A = malloc(N * sizeof(double));
    double *B = malloc(N * sizeof(double));
    double *C = malloc(N * sizeof(double));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        A[i] = i * 1.0;
        B[i] = 2.0;
    }

    // Strip mining + OpenMP
    #pragma omp parallel for
    for (int start = 0; start < N; start += STRIP_SIZE) {

        int end = start + STRIP_SIZE;

        if (end > N)
            end = N;

        // Process one strip
        #pragma omp simd
        for (int i = start; i < end; i++) {
            C[i] = A[i] * B[i];
        }
    }

    // Display some results
    printf("C[0] = %.2f\n", C[0]);
    printf("C[1] = %.2f\n", C[1]);
    printf("C[2] = %.2f\n", C[2]);
    printf("C[999999] = %.2f\n", C[999999]);

    free(A);
    free(B);
    free(C);

    return 0;
}
