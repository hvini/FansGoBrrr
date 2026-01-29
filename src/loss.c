#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "loss.h"
#include "matrix.h"

float mse_loss(Matrix* y_pred, Matrix* y_true) {
    int size = y_pred->rows * y_pred->cols;
    float error = 0.0f;
    for (int i = 0; i < size; i++) {
        float diff = y_pred->data[i] - y_true->data[i];
        error += diff * diff;
    }
    return error / (float)size;
}

Matrix* mse_loss_gradient(Matrix* y_pred, Matrix* y_true) {
    Matrix* grad = create_matrix(y_pred->rows, y_pred->cols);
    int n = y_pred->rows * y_pred->cols;

    for (int i = 0; i < n; i++) {
        grad->data[i] = (2.0f / n) * (y_pred->data[i] - y_true->data[i]);
    }

    return grad;
}