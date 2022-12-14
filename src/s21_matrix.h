#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-07

typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
} matrix_t;

// создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result);

// очистка матриц
void s21_remove_matrix(matrix_t *A);

// сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// умножение двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);

// минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result);
matrix_t reduced_matrix(matrix_t *A, int rows, int columns);
double matrix_minor(matrix_t *A);

// определитель матрицы
int s21_determinant(matrix_t *A, double *result);

// обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_
