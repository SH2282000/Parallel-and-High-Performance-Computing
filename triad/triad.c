#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NITERS 10000000

double **matrix_new(int rows, int cols)
{
    double **matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }
    return matrix;
}

void matrix_delete(double **matrix)
{
    for(int i = 0; matrix[i] != NULL; i++) { free(matrix[i]); }
    free(matrix);
}
void matrix_print(int rows, int cols, double **matrix)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}
void matrix_vector_mul(int rows, int cols, double **matrix, double *x, double *y)
{
    for (int i = 0; i < rows; i++) {
        y[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            y[i] += matrix[i][j] * x[i];
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    size_t iteration;
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        iteration = atoi(argv[1]);
    }

    for (size_t n = 0; n < iteration; n+=100) {
        double *a = (double *)malloc(sizeof(double) * n);
        double *b = (double *)malloc(sizeof(double) * n);
        double *c = (double *)malloc(sizeof(double) * n);
        double *d = (double *)malloc(sizeof(double) * n);

        struct timespec start, end;

        for (size_t i = 0; i < n; i++) {
            b[i] = i;
            c[i] = i;
            d[i] = i;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        // Put the triad here
        for (size_t j = 0; j < n; j++) {
            for (size_t i = 0; i < n; i++) {
                a[i] = b[i] + c[i] * d[i];
            }
        }
        // Make sure to prevent dead code elimination (DCE).
        clock_gettime(CLOCK_MONOTONIC, &end);

        long long seconds = end.tv_sec - start.tv_sec;
        long long nanos   = end.tv_nsec - start.tv_nsec + (seconds * 1000000000LL);

        double mflops = 2.0 * NITERS * n / (nanos * 1.0e-9) / 1.0e6;

        printf("\n%zu,%f,%f,%f", n, nanos / 1000000000.0, mflops, a[n - 1]);

        free(a);
        free(b);
        free(c);
        free(d);
    }

    return EXIT_SUCCESS;
}
