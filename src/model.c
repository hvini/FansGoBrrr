#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "model.h"
#include "matrix.h"
#include "layers.h"

Model* create_model(int num_layers) {
    Model* m = (Model*)malloc(sizeof(Model));
    if (!m) return NULL;

    m->num_layers = num_layers;
    m->layers = (DenseLayer**)malloc(sizeof(DenseLayer*) * num_layers);
    if (!m->layers) {
        free(m);
        return NULL;
    }

    for (int i = 0; i < num_layers; i++) {
        m->layers[i] = NULL;
    }

    return m;
}

void model_update(Model* m, float learning_rate) {
    for (int i = 0; i < m->num_layers; i++) {
        dense_update_weights(m->layers[i], learning_rate);
    }
}

void free_model(Model* m) {
    if (!m) return;
    for (int i = 0; i < m->num_layers; i++) {
        if (m->layers[i]) {
            free_dense_layer(m->layers[i]);
        }
    }
    free(m->layers);
    free(m);
}

Matrix* model_forward(Model* m, Matrix* input) {
    Matrix* current_input = input;
    for (int i = 0; i < m->num_layers; i++) {
        current_input = dense_forward(m->layers[i], current_input);
    }

    return current_input;
}

void model_backward(Model* m, Matrix* loss_gradient) {
    Matrix* current_grad = loss_gradient;

    for (int i = m->num_layers - 1; i >= 0; i--) {
        Matrix* next_grad = dense_backward(m->layers[i], current_grad);

        if (current_grad != loss_gradient) {
            free_matrix(current_grad);
        }
        current_grad = next_grad;
    }

    free_matrix(current_grad);
}