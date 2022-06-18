#include "s21_matrix.h"

// создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result) {
    result->matrix = NULL;
    result->matrix_type = INCORRECT_MATRIX;
    if (rows > 0 && columns > 0) {
        result->rows = rows;
        result->columns = columns;
        result->matrix = calloc(rows, sizeof(double *));
        if (result->matrix) {
            for (int i = 0; i < rows; i++) {
                result->matrix[i] = calloc(columns, sizeof(double));
            }
            result->matrix_type = TRUE_MATRIX;
        }
    }
    return result->matrix_type;
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
    if (A->rows == B->rows && A->columns == B->columns) {
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
    result->matrix = NULL;
    result->matrix_type = TRUE_MATRIX;
    if (A->rows == B->rows && A->columns == B->columns) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
    } else {
        result->matrix_type = CALCULATION_ERROR;
    }
    return result->matrix_type;
}

// // вычитание матриц
// int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// // умножение матрицы на число
// int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// // умножение двух матриц
// int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// // транспонирование матрицы
// int s21_transpose(matrix_t *A, matrix_t *result);

// // минор матрицы и матрица алгебраических дополнений
// int s21_calc_complements(matrix_t *A, matrix_t *result);

// // определитель матрицы
// int s21_determinant(matrix_t *A, double *result);

// // обратная матрица
// int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// int main() { return 0; }
