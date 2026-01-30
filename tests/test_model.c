#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "model.h"
#include "matrix.h"
#include "layers.h"

#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

#define RUN_TEST(test_fn) do { \
    printf("Running %-30s... ", #test_fn); \
    test_fn(); \
    printf(GREEN "PASSED\n" RESET); \
} while (0)

void test_model_forward_flow() {
    // Setup: 2 layers
    // Input(2) -> Hidden(2) -> Output(1)
    Model* m = create_model(2);
    m->layers[0] = create_dense_layer(2, 2, ACT_NONE);
    m->layers[1] = create_dense_layer(2, 1, ACT_NONE);

    // Initialize Layer 0: Identity-ish weights, 0 bias
    m->layers[0]->W->data[0] = 1.0f; m->layers[0]->W->data[1] = 0.0f;
    m->layers[0]->W->data[2] = 0.0f; m->layers[0]->W->data[3] = 1.0f;
    m->layers[0]->b->data[0] = 0.0f; m->layers[0]->b->data[1] = 0.0f;

    // Initialize Layer 1: Summing weights [1.0, 1.0], 0 bias
    m->layers[1]->W->data[0] = 1.0f; m->layers[1]->W->data[1] = 1.0f;
    m->layers[1]->b->data[0] = 0.0f;

    // Input: [0.5, 0.5]
    Matrix* input = create_matrix(2, 1);
    input->data[0] = 0.5f; input->data[1] = 0.5f;

    // Forward pass
    // L0 output should be [0.5, 0.5]
    // L1 output should be (1.0 * 0.5) + (1.0 * 0.5) = 1.0
    Matrix* output = model_forward(m, input);

    if (fabsf(output->data[0] - 1.0f) > 1e-5) {
        printf("Fail: Expected 1.0, got %f\n", output->data[0]);
        assert(0);
    }

    free_matrix(input);
    free_model(m);
    // Note: In model_forward, intermediate matrices might need careful 
    // management if dense_forward allocates new memory every time.
}

void test_model_backward_gradient_update() {
    Model* m = create_model(1);
    m->layers[0] = create_dense_layer(1, 1, ACT_NONE);
    m->layers[0]->W->data[0] = 1.0f;
    
    // Dummy forward to populate cache
    Matrix* input = create_matrix(1, 1);
    input->data[0] = 10.0f;
    model_forward(m, input);

    // Dummy loss gradient [1.0]
    Matrix* loss_grad = create_matrix(1, 1);
    loss_grad->data[0] = 1.0f;

    // Backward pass
    model_backward(m, loss_grad);

    // After backward, dW should be input * grad = 10.0 * 1.0 = 10.0
    assert(m->layers[0]->dW->data[0] == 10.0f);

    // Update weights with LR = 0.1
    // New W = 1.0 - (0.1 * 10.0) = 0.0
    model_update(m, 0.1f);
    assert(m->layers[0]->W->data[0] == 0.0f);

    free_matrix(input);
    free_matrix(loss_grad);
    free_model(m);
}

int main() {
    RUN_TEST(test_model_forward_flow);
    RUN_TEST(test_model_backward_gradient_update);
    printf(GREEN "\nAll model tests passed!\n" RESET);
    return 0;
}