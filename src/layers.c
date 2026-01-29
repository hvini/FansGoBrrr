#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "layers.h"

DenseLayer* create_dense_layer(int in_features, int out_features, ActivationType act) {
    DenseLayer* ptr_dl = (DenseLayer*) malloc(sizeof(DenseLayer));
    if (ptr_dl == NULL) {
      return NULL;
    }

    ptr_dl->W = ptr_dl->b = ptr_dl->dW = ptr_dl->db = NULL;
    ptr_dl->input = ptr_dl->output = NULL;

    ptr_dl->W = create_matrix(out_features, in_features);
    ptr_dl->b = create_matrix(out_features, 1);
    ptr_dl->dW = create_matrix(out_features, in_features);
    fill_matrix(ptr_dl->dW, 0);
    ptr_dl->db = create_matrix(out_features, 1);
    fill_matrix(ptr_dl->db, 0);

    if (!ptr_dl->W || !ptr_dl->b || !ptr_dl->dW || !ptr_dl->db) {
        free_dense_layer(ptr_dl);
        return NULL;
    }

    ptr_dl->activation = act;

    return ptr_dl;
}

void free_dense_layer(DenseLayer *layer) {
    if (layer == NULL) return;

    free_matrix(layer->W);
    free_matrix(layer->b);
    free_matrix(layer->dW);
    free_matrix(layer->db);
    
    free_matrix(layer->output);
    
    layer->input = NULL; 

    free(layer);
}

Matrix* dense_forward(DenseLayer *layer, Matrix *input) {
    Matrix* res = dot_matrix(layer->W, input);

    for (int i = 0; i < res->rows; i++) {
        for (int j = 0; j < res->cols; j++) {
            res->data[i * res->cols + j] += layer->b->data[i];
        }
    }
    
    if (layer->activation != ACT_NONE) {
        int size = res->rows * res->cols;
        for (int i = 0; i < size; i++) {
            res->data[i] = act_forward(res->data[i], layer->activation);
        }
    }
    
    layer->input = input;
    if (layer->output != NULL) {
        free_matrix(layer->output);
    }
    layer->output = res;

    return res;
}

Matrix* dense_backward(DenseLayer *layer, Matrix *grad_output) {
    int size = grad_output->rows * grad_output->cols;
    for(int i = 0; i < size; i++) {
        float y = layer->output->data[i];
        float gradient = grad_output->data[i];
        grad_output->data[i] = gradient * act_backward(y, layer->activation);    
    }

    Matrix* input_T = transpose_matrix(layer->input);
    Matrix* dW_temp = dot_matrix(grad_output, input_T);

    int grad_size = layer->dW->rows * layer->dW->cols;
    for (int i = 0; i < grad_size; i++) {
        layer->dW->data[i] += dW_temp->data[i];
    }

    free_matrix(input_T);
    free_matrix(dW_temp);

    for (int i = 0; i < grad_output->rows; i++) {
        float sum = 0.0f;
        for (int j = 0; j < grad_output->cols; j++) {
            sum += grad_output->data[i * grad_output->cols + j];
        }
        layer->db->data[i] += sum;
    }

    Matrix* W_T = transpose_matrix(layer->W);
    Matrix* dX = dot_matrix(W_T, grad_output);

    free_matrix(W_T);

    return dX;
}

void dense_update_weights(DenseLayer* layer, float learning_rate) {
    int w_size = layer->W->rows * layer->W->cols;
    for (int i = 0; i < w_size; i++) {
        layer->W->data[i] -= learning_rate * layer->dW->data[i];
        layer->dW->data[i] = 0;
    }

    int b_size = layer->b->rows;
    for (int i = 0; i < b_size; i++) {
        layer->b->data[i] -= learning_rate * layer->db->data[i];
        layer->db->data[i] = 0;
    }
}

float act_forward(float x, ActivationType act) {
    switch(act) {
        case ACT_SIGMOID: return 1.0f / (1.0f + expf(-x));
        case ACT_RELU: return x > 0 ? x : 0;
        case ACT_TANH: return tanhf(x);
        case ACT_NONE:
        default: return x;
    }
}

float act_backward(float x, ActivationType act) {
    switch(act) {
        case ACT_SIGMOID: return x * (1.0f - x);
        case ACT_RELU: return x > 0 ? 1.0f : 0.0f;
        case ACT_TANH: return 1.0f - (x * x);
        case ACT_NONE:
        default: return 1.0f;
    }
}