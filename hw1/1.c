#include <stdio.h>
#include <stdlib.h>

// 打印矩陣
void dump_matrix(double *matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%lf ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

// 轉置矩陣
double* transpose_matrix(double *matrix, int rows, int cols) {
    double *transposed = (double*)malloc(rows * cols * sizeof(double));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j * rows + i] = matrix[i * cols + j];
        }
    }
    return transposed;
}

// 矩陣相加
double* add_matrices(double *matrixA, double *matrixB, int rows, int cols) {
    double *result = (double*)malloc(rows * cols * sizeof(double));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i * cols + j] = matrixA[i * cols + j] + matrixB[i * cols + j];
        }
    }
    return result;
}

// 矩陣相乘
double* multiply_matrices(double *matrixA, int rowsA, int colsA, double *matrixB, int rowsB, int colsB) {
    if (colsA != rowsB) {
        printf("矩陣無法相乘，列數與行數不匹配\n");
        return NULL;
    }

    double *result = (double*)malloc(rowsA * colsB * sizeof(double));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            result[i * colsB + j] = 0;
            for (int k = 0; k < colsA; ++k) {
                result[i * colsB + j] += matrixA[i * colsA + k] * matrixB[k * colsB + j];
            }
        }
    }
    return result;
}

int main() {
    // 示例矩陣
    double matrixA[6] = {1, 2, 3, 4, 5, 6}; // 2x3矩陣
    double matrixB[6] = {7, 8, 9, 10, 11, 12}; // 2x3矩陣

    printf("矩陣 A:\n");
    dump_matrix(matrixA, 2, 3);

    printf("矩陣 B:\n");
    dump_matrix(matrixB, 2, 3);

    double *transposedA = transpose_matrix(matrixA, 2, 3);
    printf("轉置後的矩陣 A:\n");
    dump_matrix(transposedA, 3, 2);
    free(transposedA);

    double *added = add_matrices(matrixA, matrixB, 2, 3);
    printf("A 和 B 相加的結果:\n");
    dump_matrix(added, 2, 3);
    free(added);

    double matrixC[6] = {1, 4, 2, 5, 3, 6}; // 3x2矩陣
    double *multiplied = multiply_matrices(matrixA, 2, 3, matrixC, 3, 2);
    printf("A 和 C 相乘的結果:\n");
    dump_matrix(multiplied, 2, 2);
    free(multiplied);

    return 0;
}
