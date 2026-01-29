#include "layers.h"

typedef struct {
    DenseLayer** layers;
    int num_layers;
} Model;

Model* create_model(int num_layers);
void free_model(Model* m);

// The engine of the network
Matrix* model_forward(Model* m, Matrix* input);
void model_backward(Model* m, Matrix* loss_gradient);
void model_update(Model* m, float learning_rate);