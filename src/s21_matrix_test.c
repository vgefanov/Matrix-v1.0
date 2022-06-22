#include "s21_matrix.h"

#include <check.h>

typedef struct {
    int rows;
    int columns;
    int result_code;
} test_struct_i3;

typedef struct {
    int result_code;
    double m1[3][3];
    double m2[3][3];
} test_struct_i1m2;

typedef struct {
    int result_code;
    double m1[3][3];
    double m2[3][3];
    double mres[3][3];
} test_struct_i1m3;

typedef struct {
    int result_code;
    double num;
    double m1[3][3];
    double mres[3][3];
} test_struct_i1d1m2;

typedef struct {
    int result_code;
    double num;
    double m1[3][3];
} test_struct_i1d1m1;

void copy_matrix_tst(double src[3][3], matrix_t *dst) {
    for (int row = 0; row < dst->rows; row++) {
        for (int col = 0; col < dst->columns; col++) {
            dst->matrix[row][col] = src[row][col];
        }
    }
}

matrix_t matrix_insert(int rows, int columns, const double *val) {
    matrix_t matrix;
    s21_create_matrix(rows, columns, &matrix);
    int num = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix.matrix[i][j] = val[num];
            num++;
        }
    }
    return matrix;
}

// s21_create_matrix

test_struct_i3 test_pack_create[] = {
    {2, 4, OK},
    {-2, 4, INCORRECT_MATRIX},
    {2, -4, INCORRECT_MATRIX},
    {0, 15, INCORRECT_MATRIX},
    {15, 0, INCORRECT_MATRIX},
    {0, -10, INCORRECT_MATRIX},
    {-10, 0, INCORRECT_MATRIX},
    {0, 0, INCORRECT_MATRIX},
    {1, 1, OK},
};

START_TEST(test_create) {
    matrix_t m1;
    int check = s21_create_matrix(test_pack_create[_i].rows, test_pack_create[_i].columns, &m1);
    s21_remove_matrix(&m1);
    ck_assert_int_eq(check, test_pack_create[_i].result_code);
}
END_TEST

// s21_eq_matrix

test_struct_i1m2 test_pack_eq[] = {
    {
        SUCCESS,
        {
            {0.0, 1.0, 2.0},
            {3.0, 4.0, 5.0},
            {6.0, 7.0, 8.0},
        },
        {
            {0.0, 1.0, 2.0},
            {3.0, 4.0, 5.0},
            {6.0, 7.0, 8.0},
        },
    },
    {
        SUCCESS,
        {
            {987654321.123456789, 1111111111111.1111111111111, 2.0},
            {3.0000001, 4.111111111, 5123454321.5123454321},
            {666666666666.0, 7.0, 987654321.9123456789},
        },
        {
            {987654321.123456780, 1111111111111.1111111111111, 2.0},
            {3.0000001, 4.111111100, 5123454321.5123454321},
            {666666666666.0, 7.0, 987654321.912345600},
        },
    },
    {
        FAILURE,
        {
            {987654321.1234567, 1111111111111.111111, 2.0000005},
            {3.0000001, 4.1111111, 5123454321.5123454},
            {666666666666.0, 7.0, 987654321.9123456},
        },
        {
            {987654321.1234567, 1111111111111.111111, 2.0},
            {3.0000001, 4.1111111, 5123454321.5123454},
            {666666666666.0, 7.0, 987654321.9123456},
        },
    },
    {
        FAILURE,
        {
            {3.3333333, -5, 0},
            {6, 3.3333334, 0},
            {0, 0, 0},
        },
        {
            {3.3333333, -5, 0},
            {6, 3.3333335, 0},
            {0, 0, 0},
        },
    },
};

START_TEST(test_eq) {
    matrix_t m1;
    matrix_t m2;
    s21_create_matrix(3, 3, &m1);
    copy_matrix_tst(test_pack_eq[_i].m1, &m1);
    s21_create_matrix(3, 3, &m2);
    copy_matrix_tst(test_pack_eq[_i].m2, &m2);
    int result_code = s21_eq_matrix(&m1, &m2);
    s21_remove_matrix(&m1);
    s21_remove_matrix(&m2);
    ck_assert_int_eq(result_code, test_pack_eq[_i].result_code);
}
END_TEST

START_TEST(test_eq_2) {
    matrix_t A, B;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(3, 2, a);
    double b[6] = {1, -1, 1, 2, 3, 4};
    B = matrix_insert(2, 3, b);
    int result_code = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    ck_assert_int_eq(result_code, 0);
}
END_TEST

// s21_sum_matrix

test_struct_i1m3 test_pack_sum[] = {{OK,
                                     {
                                         {1, 2, 3},
                                         {0, 4, 5},
                                         {0, 0, 6},
                                     },
                                     {
                                         {1, 0, 0},
                                         {2, 0, 0},
                                         {3, 4, 1},
                                     },
                                     {
                                         {2, 2, 3},
                                         {2, 4, 5},
                                         {3, 4, 7},
                                     }},
                                    {OK,
                                     {
                                         {0.0, -1.111111, 2.222222},
                                         {-3.3, 4.444444, -5.555555},
                                         {6.6, 7.777777, 8.888888},
                                     },
                                     {
                                         {0.0, 1.111111, 2.222222},
                                         {3.3, 5.0, 5.555555},
                                         {6.6, -7.777777, 8.888888},
                                     },
                                     {
                                         {0.0, 0.0, 4.444444},
                                         {0.0, 9.444444, 0.0},
                                         {13.2, 0.0, 17.777776},
                                     }}};

START_TEST(test_sum) {
    matrix_t m1;
    matrix_t m2;
    matrix_t m3;
    s21_create_matrix(3, 3, &m1);
    copy_matrix_tst(test_pack_sum[_i].m1, &m1);
    s21_create_matrix(3, 3, &m2);
    copy_matrix_tst(test_pack_sum[_i].m2, &m2);
    int result_code = s21_sum_matrix(&m1, &m2, &m3);
    for (int i = 0; i < m3.rows; i++) {
        for (int j = 0; j < m3.columns; j++) {
            ck_assert_double_eq_tol(m3.matrix[i][j], test_pack_sum[_i].mres[i][j], EPS);
        }
    }
    s21_remove_matrix(&m1);
    s21_remove_matrix(&m2);
    s21_remove_matrix(&m3);
    ck_assert_int_eq(result_code, test_pack_sum[_i].result_code);
}
END_TEST

START_TEST(test_sum_2) {
    matrix_t A, B, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(3, 2, a);
    double b[6] = {1, -1, 1, 2, 3, 4};
    B = matrix_insert(2, 3, b);
    int result_code = s21_sum_matrix(&A, &B, &res);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    ck_assert_int_eq(result_code, 2);
}
END_TEST

START_TEST(test_sum_3) {
    matrix_t A, B, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(0, 0, a);
    double b[6] = {1, -1, 1, 2, 3, 4};
    B = matrix_insert(2, 3, b);
    int result_code = s21_sum_matrix(&A, &B, &res);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    ck_assert_int_eq(result_code, 1);
}
END_TEST

// s21_sub_matrix

test_struct_i1m3 test_pack_sub[] = {
    {
        OK,
        {
            {0.0, 1.0, 2.0},
            {3.0, 4.0, 5.0},
            {6.0, 7.0, 8.0},
        },
        {
            {0.0, 1.0, 2.0},
            {3.0, 4.0, 5.0},
            {6.0, 7.0, 8.0},
        },
        {
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
        },
    },
};

START_TEST(test_sub) {
    matrix_t m1;
    matrix_t m2;
    matrix_t m3;
    s21_create_matrix(3, 3, &m1);
    copy_matrix_tst(test_pack_sub[_i].m1, &m1);
    s21_create_matrix(3, 3, &m2);
    copy_matrix_tst(test_pack_sub[_i].m2, &m2);
    int result_code = s21_sub_matrix(&m1, &m2, &m3);
    for (int i = 0; i < m3.rows; i++) {
        for (int j = 0; j < m3.columns; j++) {
            ck_assert_double_eq_tol(m3.matrix[i][j], test_pack_sub[_i].mres[i][j], EPS);
        }
    }
    s21_remove_matrix(&m1);
    s21_remove_matrix(&m2);
    s21_remove_matrix(&m3);
    ck_assert_int_eq(result_code, test_pack_sub[_i].result_code);
}
END_TEST

START_TEST(test_sub_2) {
    matrix_t A, B, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(3, 2, a);
    double b[6] = {1, -1, 1, 2, 3, 4};
    B = matrix_insert(2, 3, b);
    int result_code = s21_sub_matrix(&A, &B, &res);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    ck_assert_int_eq(result_code, 2);
}
END_TEST

START_TEST(test_sub_3) {
    matrix_t A, B, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(0, 0, a);
    double b[6] = {1, -1, 1, 2, 3, 4};
    B = matrix_insert(2, 3, b);
    int result_code = s21_sub_matrix(&A, &B, &res);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    ck_assert_int_eq(result_code, 1);
}
END_TEST

// s21_mult_number

test_struct_i1d1m2 test_pack_multnum[] = {
    {
        OK,
        2.0,
        {
            {1, 2, 3},
            {0, 4, 2},
            {2, 3, 4},
        },
        {
            {2, 4, 6},
            {0, 8, 4},
            {4, 6, 8},
        },
    },
    {OK,
     1.5,
     {
         {1.1, -2.22, 3.333},
         {-4.4444, 5.55555, -6.666666},
         {7.7777777, 8.88888888, 9.999999999},
     },
     {{1.65, -3.33, 4.9995}, {-6.6666, 8.333325, -9.999999}, {11.66666655, 13.33333332, 14.9999999985}}}};

START_TEST(test_multnum) {
    matrix_t m1;
    matrix_t mres;
    s21_create_matrix(3, 3, &m1);
    copy_matrix_tst(test_pack_multnum[_i].m1, &m1);
    int result_code = s21_mult_number(&m1, test_pack_multnum[_i].num, &mres);
    for (int i = 0; i < mres.rows; i++) {
        for (int j = 0; j < mres.columns; j++) {
            ck_assert_double_eq_tol(mres.matrix[i][j], test_pack_multnum[_i].mres[i][j], EPS);
        }
    }
    s21_remove_matrix(&m1);
    s21_remove_matrix(&mres);
    ck_assert_int_eq(result_code, test_pack_multnum[_i].result_code);
}
END_TEST

START_TEST(test_multnum_2) {
    matrix_t A, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(0, 0, a);
    int result_code = s21_mult_number(&A, 2, &res);
    s21_remove_matrix(&A);
    ck_assert_int_eq(result_code, 1);
}
END_TEST

// s21_mult_matrix

test_struct_i1m3 test_pack_multmatrix[] = {
    {OK,
     {
         {0, 9, 1},
         {1, 3, 7},
         {2, 7, 0},
     },
     {
         {0, 9, 8},
         {0, 9, 9},
         {1, 9, 6},
     },
     {
         {1, 90, 87},
         {7, 99, 77},
         {0, 81, 79},
     }},
};

START_TEST(test_multmatrix) {
    matrix_t m1;
    matrix_t m2;
    matrix_t mres;
    s21_create_matrix(3, 3, &m1);
    copy_matrix_tst(test_pack_multmatrix[_i].m1, &m1);
    s21_create_matrix(3, 3, &m2);
    copy_matrix_tst(test_pack_multmatrix[_i].m2, &m2);
    int result_code = s21_mult_matrix(&m1, &m2, &mres);
    for (int i = 0; i < mres.rows; i++) {
        for (int j = 0; j < mres.columns; j++) {
            ck_assert_double_eq_tol(mres.matrix[i][j], test_pack_multmatrix[_i].mres[i][j], EPS);
        }
    }
    s21_remove_matrix(&m1);
    s21_remove_matrix(&m2);
    s21_remove_matrix(&mres);
    ck_assert_int_eq(result_code, test_pack_multmatrix[_i].result_code);
}
END_TEST

START_TEST(test_multmatrix_2) {
    matrix_t A, B, wait, res;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);
    s21_create_matrix(1, 1, &wait);
    A.matrix[0][0] = 2;
    B.matrix[0][0] = 5;
    wait.matrix[0][0] = 10;
    ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), OK);
    for (int i = 0; i < wait.rows; i++) {
        for (int j = 0; j < wait.columns; j++) {
            ck_assert_double_eq_tol(res.matrix[i][j], wait.matrix[i][j], EPS);
        }
    }
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&wait);
    s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_multmatrix_3) {
    matrix_t A, B, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(2, 3, a);
    double b[6] = {1, -1, 1, 2, 3, 4};
    B = matrix_insert(2, 3, b);
    int result_code = s21_mult_matrix(&A, &B, &res);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    ck_assert_int_eq(result_code, 2);
}
END_TEST

START_TEST(test_multmatrix_4) {
    matrix_t A, B, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(0, 0, a);
    double b[6] = {1, -1, 1, 2, 3, 4};
    B = matrix_insert(2, 3, b);
    int result_code = s21_mult_matrix(&A, &B, &res);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    ck_assert_int_eq(result_code, 1);
}
END_TEST

// s21_transpose

test_struct_i1m2 test_pack_transpose[] = {
    {
        OK,
        {
            {0.0, 1.0, 2.0},
            {3.0, 4.0, 5.0},
            {6.0, 7.0, 8.0},
        },
        {
            {0.0, 3.0, 6.0},
            {1.0, 4.0, 7.0},
            {2.0, 5.0, 8.0},
        },
    },
};

START_TEST(test_transpose) {
    matrix_t m1;
    matrix_t mres;
    s21_create_matrix(3, 3, &m1);
    copy_matrix_tst(test_pack_transpose[_i].m1, &m1);
    int result_code = s21_transpose(&m1, &mres);
    for (int i = 0; i < mres.rows; i++) {
        for (int j = 0; j < mres.columns; j++) {
            ck_assert_double_eq_tol(mres.matrix[i][j], test_pack_transpose[_i].m2[i][j], EPS);
        }
    }
    s21_remove_matrix(&m1);
    s21_remove_matrix(&mres);
    ck_assert_int_eq(result_code, test_pack_transpose[_i].result_code);
}
END_TEST

START_TEST(test_transpose_2) {
    matrix_t A, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(0, 0, a);
    int result_code = s21_transpose(&A, &res);
    s21_remove_matrix(&A);
    ck_assert_int_eq(result_code, 1);
}
END_TEST

// s21_calc_complements

test_struct_i1m2 test_pack_cmpl[] = {
    {
        OK,
        {
            {1.0, 2.0, 3.0},
            {0.0, 4.0, 2.0},
            {5.0, 2.0, 1.0},
        },
        {
            {0.0, 10.0, -20.0},
            {4.0, -14.0, 8.0},
            {-8.0, -2.0, 4.0},
        },
    },
};

START_TEST(test_cmpl) {
    matrix_t m1;
    matrix_t mres;
    s21_create_matrix(3, 3, &m1);
    copy_matrix_tst(test_pack_cmpl[_i].m1, &m1);
    int result_code = s21_calc_complements(&m1, &mres);
    for (int i = 0; i < mres.rows; i++) {
        for (int j = 0; j < mres.columns; j++) {
            ck_assert_double_eq_tol(mres.matrix[i][j], test_pack_cmpl[_i].m2[i][j], EPS);
        }
    }
    s21_remove_matrix(&m1);
    s21_remove_matrix(&mres);
    ck_assert_int_eq(result_code, test_pack_cmpl[_i].result_code);
}
END_TEST

START_TEST(test_cmpl_2) {
    matrix_t m;
    matrix_t mres;
    s21_create_matrix(1, 1, &m);
    int result_code = s21_calc_complements(&m, &mres);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mres);
    ck_assert_int_eq(result_code, OK);
}
END_TEST

START_TEST(test_cmpl_3) {
    matrix_t A, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(2, 3, a);
    int result_code = s21_calc_complements(&A, &res);
    s21_remove_matrix(&A);
    ck_assert_int_eq(result_code, 2);
}
END_TEST

START_TEST(test_cmpl_4) {
    matrix_t A, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(0, 0, a);
    int result_code = s21_calc_complements(&A, &res);
    s21_remove_matrix(&A);
    ck_assert_int_eq(result_code, 1);
}
END_TEST

// s21_determinant

test_struct_i1d1m1 test_pack_determinant[] = {
    {
        OK,
        43.0,
        {
            {1.0, 2.0, 3.0},
            {5.0, 3.0, 2.0},
            {-5.0, 3.0, 3.0},
        },
    },
    {OK,
     0,
     {
         {
             0,
             0,
             0,
         },
         {
             0,
             0,
             0,
         },
         {
             0,
             0,
             0,
         },
     }},
    {
        OK,
        0.0,
        {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0},
        },
    },
};

START_TEST(test_determinant) {
    matrix_t m1;
    s21_create_matrix(3, 3, &m1);
    copy_matrix_tst(test_pack_determinant[_i].m1, &m1);
    double det;
    int result_code = s21_determinant(&m1, &det);
    ck_assert_double_eq_tol(det, test_pack_determinant[_i].num, EPS);
    s21_remove_matrix(&m1);
    ck_assert_int_eq(result_code, test_pack_determinant[_i].result_code);
}
END_TEST

START_TEST(test_determinant_2) {
    matrix_t m;
    s21_create_matrix(1, 1, &m);
    m.matrix[0][0] = 1;
    double det;
    int result_code = s21_determinant(&m, &det);
    ck_assert_double_eq_tol(det, 1, EPS);
    s21_remove_matrix(&m);
    ck_assert_int_eq(result_code, OK);
}
END_TEST

START_TEST(test_determinant_3) {
    matrix_t A;
    double res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(2, 3, a);
    int result_code = s21_determinant(&A, &res);
    s21_remove_matrix(&A);
    ck_assert_int_eq(result_code, 2);
}
END_TEST

START_TEST(test_determinant_4) {
    matrix_t A;
    double res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(0, 0, a);
    int result_code = s21_determinant(&A, &res);
    s21_remove_matrix(&A);
    ck_assert_int_eq(result_code, 1);
}
END_TEST

// s21_inverse_matrix

test_struct_i1m2 test_pack_inverse[] = {
    {
        OK,
        {
            {2.0, 5.0, 7.0},
            {6.0, 3.0, 4.0},
            {5.0, -2.0, -3.0},
        },
        {
            {1.0, -1.0, 1.0},
            {-38.0, 41.0, -34.0},
            {27.0, -29.0, 24.0},
        },
    },
};

START_TEST(test_inverse) {
    matrix_t m1;
    matrix_t mres;
    s21_create_matrix(3, 3, &m1);
    copy_matrix_tst(test_pack_inverse[_i].m1, &m1);
    int result_code = s21_inverse_matrix(&m1, &mres);
    for (int i = 0; i < mres.rows; i++) {
        for (int j = 0; j < mres.columns; j++) {
            ck_assert_double_eq_tol(mres.matrix[i][j], test_pack_inverse[_i].m2[i][j], EPS);
        }
    }
    s21_remove_matrix(&m1);
    s21_remove_matrix(&mres);
    ck_assert_int_eq(result_code, test_pack_inverse[_i].result_code);
}
END_TEST

START_TEST(test_inverse_2) {
    matrix_t m;
    matrix_t mres;
    s21_create_matrix(1, 1, &m);
    m.matrix[0][0] = 5;
    int result_code = s21_inverse_matrix(&m, &mres);
    ck_assert_double_eq_tol(mres.matrix[0][0], 0.2, EPS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mres);
    ck_assert_int_eq(result_code, OK);
}
END_TEST

START_TEST(test_inverse_3) {
    matrix_t A, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(2, 3, a);
    int result_code = s21_inverse_matrix(&A, &res);
    s21_remove_matrix(&A);
    ck_assert_int_eq(result_code, 2);
}
END_TEST

START_TEST(test_inverse_4) {
    matrix_t A, res;
    double a[6] = {1, 4, 2, 5, 3, 6};
    A = matrix_insert(0, 0, a);
    int result_code = s21_inverse_matrix(&A, &res);
    s21_remove_matrix(&A);
    ck_assert_int_eq(result_code, 1);
}
END_TEST

// main

int main() {
    Suite *s = suite_create("s21_matrix test");
    SRunner *sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);
    TCase *tc = tcase_create("s21_matrix case");
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 10);

    // s21_create_matrix
    int test_pack_size = sizeof(test_pack_create) / sizeof(test_struct_i3);
    tcase_add_loop_test(tc, test_create, 0, test_pack_size);

    // s21_eq_matrix
    test_pack_size = sizeof(test_pack_eq) / sizeof(test_struct_i1m2);
    tcase_add_loop_test(tc, test_eq, 0, test_pack_size);
    tcase_add_loop_test(tc, test_eq_2, 0, test_pack_size);

    // s21_sum_matrix
    test_pack_size = sizeof(test_pack_sum) / sizeof(test_struct_i1m3);
    tcase_add_loop_test(tc, test_sum, 0, test_pack_size);
    tcase_add_test(tc, test_sum_2);
    tcase_add_test(tc, test_sum_3);

    // s21_sub_matrix
    test_pack_size = sizeof(test_pack_sub) / sizeof(test_struct_i1m3);
    tcase_add_loop_test(tc, test_sub, 0, test_pack_size);
    tcase_add_test(tc, test_sub_2);
    tcase_add_test(tc, test_sub_3);

    // s21_mult_number
    test_pack_size = sizeof(test_pack_multnum) / sizeof(test_struct_i1d1m2);
    tcase_add_loop_test(tc, test_multnum, 0, test_pack_size);
    tcase_add_test(tc, test_multnum_2);

    // s21_mult_matrix
    test_pack_size = sizeof(test_pack_multmatrix) / sizeof(test_struct_i1m3);
    tcase_add_loop_test(tc, test_multmatrix, 0, test_pack_size);
    tcase_add_test(tc, test_multmatrix_2);
    tcase_add_test(tc, test_multmatrix_3);
    tcase_add_test(tc, test_multmatrix_4);

    // s21_transpose
    test_pack_size = sizeof(test_pack_transpose) / sizeof(test_struct_i1m2);
    tcase_add_loop_test(tc, test_transpose, 0, test_pack_size);
    tcase_add_test(tc, test_transpose_2);

    // s21_calc_complements
    test_pack_size = sizeof(test_pack_cmpl) / sizeof(test_struct_i1m2);
    tcase_add_loop_test(tc, test_cmpl, 0, test_pack_size);
    tcase_add_test(tc, test_cmpl_2);
    tcase_add_test(tc, test_cmpl_3);
    tcase_add_test(tc, test_cmpl_4);

    // s21_determinant
    test_pack_size = sizeof(test_pack_determinant) / sizeof(test_struct_i1d1m1);
    tcase_add_loop_test(tc, test_determinant, 0, test_pack_size);
    tcase_add_test(tc, test_determinant_2);
    tcase_add_test(tc, test_determinant_3);
    tcase_add_test(tc, test_determinant_4);

    // s21_inverse_matrix
    test_pack_size = sizeof(test_pack_inverse) / sizeof(test_struct_i1m2);
    tcase_add_loop_test(tc, test_inverse, 0, test_pack_size);
    tcase_add_test(tc, test_inverse_2);
    tcase_add_test(tc, test_inverse_3);
    tcase_add_test(tc, test_inverse_4);

    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);
    return 0;
}
