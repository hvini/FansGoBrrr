#include <stdio.h>
#include <utils.h>
#include "layers.h"
#include "matrix.h"
#include "model.h"
#include "loss.h"

int main() {
    srand(42);

    Matrix* x_train = create_matrix(2, 4);
    float inputs[] = {0, 0, 1, 1,
                    0, 1, 0, 1};

    for (int i = 0; i < 8; i++) x_train->data[i] = inputs[i];

    Matrix* y_train = create_matrix(1, 4);
    float targets[] = {0, 1, 1, 0};
    for (int i = 0; i < 4; i++) y_train->data[i] = targets[i];
    
    Model* model = create_model(2);
    model->layers[0] = create_dense_layer(2, 8, ACT_RELU);
    model->layers[1] = create_dense_layer(8, 1, ACT_SIGMOID);

    randomize_matrix(model->layers[0]->W, -1.0, 1.0);
    randomize_matrix(model->layers[1]->W, -1.0, 1.0);
    fill_matrix(model->layers[0]->b, 0.0f);
    fill_matrix(model->layers[1]->b, 0.0f);

    float learning_rate = 0.1f;

    for (int epoch = 0; epoch < 10000; epoch++) {
        Matrix* pred = model_forward(model, x_train);

        float loss = mse_loss(pred, y_train);

        Matrix* grad = mse_loss_gradient(pred, y_train);
        model_backward(model, grad);

        model_update(model, learning_rate);

        free_matrix(grad);
        if (epoch % 1000 == 0) {
            printf("Epoch %d - Loss: %f\n", epoch, loss);
        }
    }

    printf("\n--- Final Inference ---\n");
    Matrix* final_pred = model_forward(model, x_train);

    for (int i = 0; i < 4; i++) {
        float x1 = x_train->data[0 * 4 + i];
        float x2 = x_train->data[1 * 4 + i];
        float prediction = final_pred->data[i];
        float target = y_train->data[i];

        printf("Input: (%0.0f, %0.0f) | Target: %0.0f | Prediction: %f\n", 
                x1, x2, target, prediction);
    }

    free_matrix(x_train);
    free_matrix(y_train);
    free_model(model);

    return 0;
}

