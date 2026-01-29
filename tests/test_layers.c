#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "../include/layers.h"

#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"

#define RUN_TEST(test_fn) do { \
    printf("Running %-30s... ", #test_fn); \
    test_fn(); \
    printf(GREEN "PASSED\n" RESET); \
} while (0)

// Helper to check if floats are "close enough" (handles precision issues)
void assert_float_near(float actual, float expected) {
    float diff = fabsf(actual - expected);
    if (diff > 1e-5) {
        printf(RED "Expected %f but got %f\n" RESET, expected, actual);
        assert(0);
    }
}

void test_dense_forward_linear() {
    // 2 inputs, 1 output
    DenseLayer* layer = create_dense_layer(2, 1, ACT_NONE);
    
    // Manually set weights to 0.5 and bias to 1.0
    layer->W->data[0] = 0.5f; layer->W->data[1] = 0.5f;
    layer->b->data[0] = 1.0f;

    // Input: [2, 4]^T
    Matrix* input = create_matrix(2, 1);
    input->data[0] = 2.0f; input->data[1] = 4.0f;

    // Expected: (0.5 * 2) + (0.5 * 4) + 1.0 = 1 + 2 + 1 = 4.0
    Matrix* output = dense_forward(layer, input);

    assert_float_near(output->data[0], 4.0f);
    
    // Verify caching
    assert(layer->input == input);
    assert(layer->output == output);

    free_matrix(input); 
    free_dense_layer(layer);
}

void test_dense_backward_gradients() {
    // 1 input, 1 output (simplest case)
    DenseLayer* layer = create_dense_layer(1, 1, ACT_NONE);
    layer->W->data[0] = 2.0f;
    layer->b->data[0] = 0.0f;

    Matrix* input = create_matrix(1, 1);
    input->data[0] = 3.0f;
    dense_forward(layer, input);

    // Incoming gradient from next layer is 1.0
    Matrix* grad_out = create_matrix(1, 1);
    grad_out->data[0] = 1.0f;

    // Run backprop
    Matrix* dX = dense_backward(layer, grad_out);

    // dW = grad_out * input^T = 1.0 * 3.0 = 3.0
    assert_float_near(layer->dW->data[0], 3.0f);
    // db = sum(grad_out) = 1.0
    assert_float_near(layer->db->data[0], 1.0f);
    // dX = W^T * grad_out = 2.0 * 1.0 = 2.0
    assert_float_near(dX->data[0], 2.0f);

    free_matrix(input); free_matrix(grad_out);
    free_matrix(dX); free_dense_layer(layer);
}

int main() {
    RUN_TEST(test_dense_forward_linear);
    RUN_TEST(test_dense_backward_gradients);
    printf(GREEN "\nAll layer tests passed!\n" RESET);
    return 0;
}