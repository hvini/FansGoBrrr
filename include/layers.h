#ifndef LAYERS_H
#define LAYERS_H

#include "matrix.h"

// -------- Activation Types -------- //
typedef enum {
    ACT_NONE,
    ACT_SIGMOID,
    ACT_RELU,
    ACT_TANH
} ActivationType;


// -------- Dense Layer Structure -------- //
typedef struct {
    Matrix *W;        // weights    (out_features x in_features)
    Matrix *b;        // biases     (out_features x 1)

    Matrix *input;    // cache for backprop
    Matrix *output;   // cache for backprop

    Matrix *dW;       // gradient of W
    Matrix *db;       // gradient of b

    ActivationType activation;
} DenseLayer;


// -------- Constructors / Destructors -------- //
DenseLayer* create_dense_layer(int in_features, int out_features, ActivationType act);
void free_dense_layer(DenseLayer *layer);


// -------- Forward / Backward -------- //
Matrix* dense_forward(DenseLayer *layer, Matrix *input);
Matrix* dense_backward(DenseLayer *layer, Matrix *grad_output);
void dense_update_weights(DenseLayer* layer, float learning_rate);


// -------- Activation Functions (internal) -------- //
float act_forward(float x, ActivationType act);
float act_backward(float x, ActivationType act);

#endif // LAYERS.h
