#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

// Constructor & destructor
Matrix* create_matrix(int rows, int cols) {
    Matrix *ptr_m;
    
    ptr_m = (Matrix*) malloc(sizeof(Matrix));
    if (ptr_m == NULL) {
      return NULL;
    }
    
    ptr_m->rows = rows;
    ptr_m->cols = cols;
    
    ptr_m->data = (float*) malloc(rows * cols * sizeof(float));
    if (ptr_m->data == NULL) {
      free(ptr_m);
      return NULL;
    }
    
    return ptr_m;
}

void free_matrix(Matrix* m) {
    if (m != NULL) {
      free(m->data);
      free(m);
    }
}

// Initialization
void fill_matrix(Matrix* m, float value) {
    int rows = m->rows;
    int cols = m->cols;
    int size = rows * cols;
    for (int i = 0; i < size; i++) {
      m->data[i] = value;
    }
}

void randomize_matrix(Matrix* m, float min, float max) {
    float random_num;
    int rows = m->rows;
    int cols = m->cols;
    int size = rows * cols;
    for (int i = 0; i < size; i++) {
      random_num = ((float)rand() / RAND_MAX) * (max - min) + min;
      m->data[i] = random_num;
    }
}

// Operations
Matrix* copy_matrix(const Matrix* src) {
    int rows = src->rows;
    int cols = src->cols;
    int size = rows * cols;
    Matrix *target;

    target = create_matrix(rows, cols);
    if (target == NULL) {
      return NULL;
    }

    for (int i = 0; i < size; i++) {
      target->data[i] = src->data[i];
    }

    return target;
}

Matrix* transpose_matrix(const Matrix* m) {
    int rows = m->rows;
    int cols = m->cols;
    Matrix *transposed;

    transposed = create_matrix(cols, rows);
    if (transposed == NULL) {
      return NULL;  
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        transposed->data[j * rows + i] = m->data[i * cols + j];
      }
    }

    return transposed;
}

Matrix* dot_matrix(const Matrix* a, const Matrix* b) {
    int a_rows = a->rows;
    int a_cols = a->cols;
    int b_rows = b->rows;
    int b_cols = b->cols;
    Matrix *dot;
    
    if (a_cols != b_rows) {
      return NULL;
    }

    dot = create_matrix(a_rows, b_cols);
    if (dot == NULL) {
      return NULL;
    }

    fill_matrix(dot, 0.0);
    for (int i = 0; i < a_rows; i++) {
      for (int j = 0; j < b_cols; j++) {
        for (int k = 0; k < a_cols; k++) {
          dot->data[i * b_cols + j] += a->data[i * a_cols + k] * b->data[k * b_cols + j];
        }
      }
    }

    return dot;
}

// Element-wise
void apply_function(Matrix* m, float (*func)(float)) {
    int rows = m->rows;
    int cols = m->cols;
    int size = rows * cols;
    for (int i = 0; i < size; i++) {
      m->data[i] = func(m->data[i]);
    }
}

// Utilities
void print_matrix(const Matrix* m) {
    int rows = m->rows;
    int cols = m->cols;
    for (int i = 0; i < rows; i++) {
      printf("[ ");
      for(int j = 0; j < cols; j++) {
        printf("%6.2f", m->data[i * cols + j]);
      }
      printf("]\n");
    }
}

