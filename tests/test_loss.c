#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "../include/loss.h"
#include "../include/matrix.h"

#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"

#define RUN_TEST(test_fn) do { \
    printf("Running %-30s... ", #test_fn); \
    test_fn(); \
    printf(GREEN "PASSED\n" RESET); \
} while (0)

void assert_float_near(float actual, float expected) {
    float diff = fabsf(actual - expected);
    if (diff > 1e-5) {
        printf(RED "Expected %f but got %f\n" RESET, expected, actual);
        assert(0);
    }
}

void test_mse_loss_zero() {
    Matrix* pred = create_matrix(2, 1);
    Matrix* true_val = create_matrix(2, 1);
    
    pred->data[0] = 1.0f; pred->data[1] = 2.0f;
    true_val->data[0] = 1.0f; true_val->data[1] = 2.0f;

    // Loss should be 0 when identical
    assert_float_near(mse_loss(pred, true_val), 0.0f);

    free_matrix(pred); free_matrix(true_val);
}

void test_mse_loss_calculation() {
    Matrix* pred = create_matrix(2, 1);
    Matrix* true_val = create_matrix(2, 1);
    
    pred->data[0] = 3.0f;     // diff = 2, sq = 4
    pred->data[1] = 5.0f;     // diff = 5, sq = 25
    true_val->data[0] = 1.0f;
    true_val->data[1] = 0.0f;

    // Expected: (4 + 25) / 2 = 14.5
    assert_float_near(mse_loss(pred, true_val), 14.5f);

    free_matrix(pred); free_matrix(true_val);
}

void test_mse_gradient_calculation() {
    int n = 2;
    Matrix* pred = create_matrix(n, 1);
    Matrix* true_val = create_matrix(n, 1);
    
    pred->data[0] = 2.0f; 
    true_val->data[0] = 1.0f; // diff = 1.0

    // Grad formula: (2/n) * (pred - true)
    // Grad[0] = (2/2) * (2.0 - 1.0) = 1.0
    
    Matrix* grad = mse_loss_gradient(pred, true_val);
    
    assert_float_near(grad->data[0], 1.0f);

    free_matrix(pred); free_matrix(true_val); free_matrix(grad);
}

int main() {
    RUN_TEST(test_mse_loss_zero);
    RUN_TEST(test_mse_loss_calculation);
    RUN_TEST(test_mse_gradient_calculation);
    
    printf(GREEN "\nAll loss tests passed!\n" RESET);
    return 0;
}