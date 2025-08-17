#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    float* data;  // Row-major layout: data[i * cols + j]
} Matrix;

// Constructor & destructor
Matrix* create_matrix(int rows, int cols);
void free_matrix(Matrix* m);

// Initialization
void fill_matrix(Matrix* m, float value);
void randomize_matrix(Matrix* m, float min, float max);

// Operations
Matrix* copy_matrix(const Matrix* src);
Matrix* transpose_matrix(const Matrix* m);
Matrix* dot_matrix(const Matrix* a, const Matrix* b); // Matrix multiplication

// Element-wise
void apply_function(Matrix* m, float (*func)(float));

// Utilities
void print_matrix(const Matrix* m);

#endif // MATRIX_H

