#ifndef LOSS_H
#define LOSS_H

#include "matrix.h"

float mse_loss(Matrix* y_pred, Matrix* y_true);

Matrix* mse_loss_gradient(Matrix* y_pred, Matrix* y_true);

float cross_entropy_loss(Matrix* y_pred, Matrix* y_true);
Matrix* cross_entropy_gradient(Matrix* y_pred, Matrix* y_true);

#endif // LOSS_H