#include <assert.h>
#include <stdio.h>
#include "../include/matrix.h"

#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"

#define RUN_TEST(test_fn) do { \
    printf("Running %-30s... ", #test_fn); \
    test_fn(); \
    printf(GREEN "PASSED\n" RESET); \
} while (0)

// === Test functions ===

void test_fill_matrix() {
    Matrix* m = create_matrix(2, 2);
    fill_matrix(m, 3.14f);
    for (int i = 0; i < 4; i++) assert(m->data[i] == 3.14f);
    free_matrix(m);
}

void test_transpose_matrix() {
    Matrix* m = create_matrix(2, 3);
    for (int i = 0; i < 6; i++) m->data[i] = (float)i;
    Matrix* t = transpose_matrix(m);
    assert(t->rows == 3 && t->cols == 2);
    assert(t->data[0] == 0.0f);
    assert(t->data[1] == 3.0f);
    assert(t->data[2] == 1.0f);
    free_matrix(m);
    free_matrix(t);
}

void test_dot_matrix() {
    Matrix* a = create_matrix(2, 3);
    Matrix* b = create_matrix(3, 2);
    fill_matrix(a, 1.0);
    fill_matrix(b, 2.0);
    Matrix* r = dot_matrix(a, b);
    assert(r->rows == 2 && r->cols == 2);
    for (int i = 0; i < 4; i++) assert(r->data[i] == 6.0f);
    free_matrix(a); free_matrix(b); free_matrix(r);
}

int main() {
    RUN_TEST(test_fill_matrix);
    RUN_TEST(test_transpose_matrix);
    RUN_TEST(test_dot_matrix);

    printf(GREEN "\nAll matrix tests passed!\n" RESET);
    return 0;
}

