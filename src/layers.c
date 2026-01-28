#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "layers.h"

DenseLayer* create_dense_layer(int in_features, int out_features, ActivationType act) {
    Matrix* W;
    Matrix* b;
    Matrix* dW;
    Matrix* db;

    DenseLayer* ptr_dl = (DenseLayer*) malloc(sizeof(DenseLayer));
    if (ptr_dl == NULL) {
      return NULL;
    }

    ptr_dl->W = ptr_dl->b = ptr_dl->dW = ptr_dl->db = NULL;
    ptr_dl->input = ptr_dl->output = NULL;

    ptr_dl->W = create_matrix(out_features, in_features);
    ptr_dl->b = create_matrix(out_features, 1);
    ptr_dl->dW = create_matrix(out_features, in_features);
    ptr_dl->db = create_matrix(out_features, 1);

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
            res->data[i * res->cols + j] += layer->b->data[i]
        }
    }
    
    if (layer->activation != ACT_NONE) {
        int size = res->rows * res->cols;
        for (int i = 0; i < size; i++) {
            res->data[i] = act_foward(res->data[i], layer->activation);
        }
    }
    
    layer->input = input;
    layer->output = res;

    return res;
}

Matrix* dense_backward(DenseLayer *layer, Matrix *grad_output, float learning_rate) {

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

}