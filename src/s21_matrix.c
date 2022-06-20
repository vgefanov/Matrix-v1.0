#include "s21_matrix.h"

// создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result) {
    result->matrix = NULL;
    int mat = INCORRECT_MATRIX;
    if (rows > 0 && columns > 0) {
        result->rows = rows;
        result->columns = columns;
        result->matrix = calloc(rows, sizeof(double *));
        if (result->matrix) {
            for (int i = 0; i < rows; i++) {
                result->matrix[i] = calloc(columns, sizeof(double));
            }
            mat = OK;
        }
    }
    return mat;
}

// очистка матриц
void s21_remove_matrix(matrix_t *A) {
    if (A->matrix != NULL) {
        for (int i = 0; i < A->rows; i++) {
            if (A->matrix[i] != NULL) free(A->matrix[i]);
        }
        free(A->matrix);
    }
}

// сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int result = SUCCESS;
    if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0 && A->rows == B->rows &&
        A->columns == B->columns) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) result = FAILURE;
            }
        }
    } else {
        result = FAILURE;
    }
    return result;
}

// сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int sum = OK;
    if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
        if (A->rows == B->rows && A->columns == B->columns) {
            s21_create_matrix(A->rows, A->columns, result);
            for (int i = 0; i < result->rows; i++) {
                for (int j = 0; j < result->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                }
            }
        } else {
            sum = CALCULATION_ERROR;
        }
    } else {
        sum = INCORRECT_MATRIX;
    }
    return sum;
}

// вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int sub = OK;
    if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
        if (A->rows == B->rows && A->columns == B->columns) {
            s21_create_matrix(A->rows, A->columns, result);
            for (int i = 0; i < result->rows; i++) {
                for (int j = 0; j < result->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                }
            }
        } else {
            sub = CALCULATION_ERROR;
        }
    } else {
        sub = INCORRECT_MATRIX;
    }
    return sub;
}

// умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int mult_num = OK;
    if (A->rows > 0 && A->columns > 0) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
    } else {
        mult_num = INCORRECT_MATRIX;
    }
    return mult_num;
}

// умножение двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int mult_mat = OK;
    if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
        if (A->columns == B->rows) {
            s21_create_matrix(A->rows, B->columns, result);
            for (int i = 0; i < result->rows; i++) {
                for (int j = 0; j < result->columns; j++) {
                    result->matrix[i][j] = 0;
                    for (int k = 0; k < B->rows; k++)
                        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        } else {
            mult_mat = CALCULATION_ERROR;
        }
    } else {
        mult_mat = INCORRECT_MATRIX;
    }
    return mult_mat;
}

// транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
    int trans = OK;
    if (A->rows > 0 && A->columns > 0) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[j][i];
            }
        }
    } else {
        trans = INCORRECT_MATRIX;
    }
    return trans;
}

// // минор матрицы и матрица алгебраических дополнений
// int s21_calc_complements(matrix_t *A, matrix_t *result) {
// int compl = OK;
// if (A->rows > 0 && A->columns > 0) {
//     if (A->rows == A->columns) {
//         s21_create_matrix(A->rows - 1, A->columns - 1, result);
//         for (int i = 0; i < result->rows; i++) {
//             for (int j = 0; j < result->columns; j++) {
//                 matrix_t minor = minor(A, i, j);
//                 result->matrix[i][j] = 
//     }
// }
// }

// matrix_t minor(matrix_t *A, int rows, int columns) {
//     matrix_t result;
//     int k_rows = 0;
//     int k_columns = 0;
//     s21_create_matrix(A->rows - 1, A->columns - 1, &result);
//     for (int i = 0; i < A->rows; i++) {
//         if (i != rows) {
//             for (int j = 0; j < A->columns; j++) {
//                 if (j != columns) {
//                     result.matrix[k_rows][k_columns] = A->matrix[i][j];
//                     k_columns++;
//                 }
//             }
//             k_rows++;
//         }
//     }
//     return result;
// }

// double matr

// // определитель матрицы
// int s21_determinant(matrix_t *A, double *result);

// // обратная матрица
// int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// void copy_matrix_tst1(double src[3][3], matrix_t *dst) {
//     for (int row = 0; row < dst->rows; row++) {
//         for (int col = 0; col < dst->columns; col++) {
//             dst->matrix[row][col] = src[row][col];
//         }
//     }
// }

// void copy_matrix_tst2(double src[2][2], matrix_t *dst) {
//     for (int row = 0; row < dst->rows; row++) {
//         for (int col = 0; col < dst->columns; col++) {
//             dst->matrix[row][col] = src[row][col];
//         }
//     }
// }

// int main() {
//     matrix_t result;
//     double a[3][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
//     matrix_t x;
//     s21_create_matrix(3, 3, &x);
//     copy_matrix_tst1(a, &x);
//     // for (int i = 0; i < 3; i++) {
//     //     for (int j = 0; j < 3; j++) {
//     //         printf("%.1f\n", x.matrix[i][j]);
//     //     }
//     // }
//     double b[2][2] = {{1.0, 2.0}, {4.0, 5.0}};
//      matrix_t y;
//     s21_create_matrix(2, 2, &y);
//     copy_matrix_tst2(b, &y);
//     // for (int i = 0; i < 2; i++) {
//     //     for (int j = 0; j < 2; j++) {
//     //         printf("%.1f\n", y.matrix[i][j]);
//     //     }
//     // }
//     int p = s21_sum_matrix(&x, &y, &result);
//     // for (int i = 0; i < 3; i++) {
//     //     for (int j = 0; j < 3; j++) {
//     //         printf("%.1f\n", result.matrix[i][j]);
//     //     }
//     // }
//     printf("%d", p);
//     return 0;
// }
