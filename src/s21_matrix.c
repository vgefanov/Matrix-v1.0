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

// минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int complements = OK;
    if (A->rows > 0 && A->columns > 0) {
        if (A->rows == A->columns) {
            s21_create_matrix(A->rows, A->columns, result);
            if (A->rows == 1) {
                result->matrix[0][0] = 1;
            } else {
                for (int i = 0; i < result->rows; i++) {
                    for (int j = 0; j < result->columns; j++) {
                        matrix_t minor = reduced_matrix(A, i, j);
                        if ((i + j) % 2 == 0) {
                            result->matrix[i][j] = matrix_minor(&minor);
                        } else {
                            result->matrix[i][j] = -1 * matrix_minor(&minor);
                        }
                        s21_remove_matrix(&minor);
                    }
                }
            }
        } else {
            complements = CALCULATION_ERROR;
        }
    } else {
        complements = INCORRECT_MATRIX;
    }
    return complements;
}

matrix_t reduced_matrix(matrix_t *A, int rows, int columns) {
    matrix_t result = {};
    s21_create_matrix(A->rows - 1, A->columns - 1, &result);
    int k_rows = 0;
    for (int i = 0; i < A->rows; i++) {
        if (i != rows) {
            int k_columns = 0;
            for (int j = 0; j < A->columns; j++) {
                if (j != columns) {
                    result.matrix[k_rows][k_columns] = A->matrix[i][j];
                    k_columns++;
                }
            }
            k_rows++;
        }
    }
    return result;
}

double matrix_minor(matrix_t *A) {
    double element = 0.0;
    if (A->rows == 1) {
        element = A->matrix[0][0];
    } else if (A->rows == 2) {
        element = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
        int sign = 1;
        for (int i = 0; i < A->columns; i++) {
            matrix_t B = reduced_matrix(A, 0, i);
            element += (A->matrix[0][i] * matrix_minor(&B) * sign);
            sign *= -1;
            s21_remove_matrix(&B);
        }
    }
    element = (fabs(element) > EPS) ? element : 0.0;
    return element;
}

// определитель матрицы
int s21_determinant(matrix_t *A, double *result) {
    int det = OK;
    if (A->rows > 0 && A->columns > 0) {
        if (A->rows == A->columns) {
            *result = matrix_minor(A);
        } else {
            det = CALCULATION_ERROR;
            *result = NAN;
        }
    } else {
        det = INCORRECT_MATRIX;
        *result = NAN;
    }
    return det;
}

// обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int inv = OK;
    if (A->rows > 0 && A->columns > 0) {
        double det = 0.0;
        int src = s21_determinant(A, &det);
        if (!src && det) {
            matrix_t min, trans;
            s21_calc_complements(A, &min);
            s21_transpose(&min, &trans);
            s21_mult_number(&trans, 1 / det, result);
            s21_remove_matrix(&min);
            s21_remove_matrix(&trans);
        } else {
            inv = CALCULATION_ERROR;
        }
    } else {
        inv = INCORRECT_MATRIX;
    }
    return inv;
}

// int main() { return 0; }
