#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <linalg/matrix.h>

#define EPSILON 1e-9

struct linalg_matrix* linalg_matrix_init(
    const size_t num_rows,
    const size_t num_cols,
    double vals[num_rows][num_cols]
) {
    struct linalg_matrix* matrix = (struct linalg_matrix*)malloc(
        sizeof(struct linalg_matrix) + sizeof(double) * num_rows * num_cols
    );
    if (matrix == NULL) {
        return NULL;
    }

    matrix->m_num_rows = num_rows;
    matrix->m_num_cols = num_cols;

    for (size_t i = 0; i < num_rows; ++i) {
        for (size_t j = 0; j < num_cols; ++j) {
            linalg_matrix_set(matrix, i, j, vals[i][j]);
        }
    }
    return matrix;
}

void linalg_matrix_print(const struct linalg_matrix* const matrix) {
    for (size_t i = 0; i < matrix->m_num_rows; ++i) {
        for (size_t j = 0; j < matrix->m_num_cols; ++j) {
            double val = linalg_matrix_get(matrix, i, j);
            if (fabs(val) < EPSILON) {
                val = 0.0;
            }
            printf("%7.2lf ", val);
        }
        printf("\n");
    }
    printf("\n");
}

int linalg_matrix_rref(struct linalg_matrix* const matrix) {
    const size_t rows = matrix->m_num_rows;
    const size_t cols = matrix->m_num_cols;
    size_t lead = 0;

    for (size_t r = 0; r < rows; ++r) {
        if (lead >= cols) {
            return 0;
        }

        size_t i = r;
        while (fabs(linalg_matrix_get(matrix, i, lead)) < EPSILON) {
            ++i;
            if (i == rows) {
                i = r;
                ++lead;
                if (lead == cols) {
                    return 0;
                }
            }
        }

        // Swap rows i and r
        if (i != r) {
            for (size_t j = 0; j < cols; ++j) {
                double temp = linalg_matrix_get(matrix, i, j);
                linalg_matrix_set(matrix, i, j, linalg_matrix_get(matrix, r, j));
                linalg_matrix_set(matrix, r, j, temp);
            }
        }

        // Scale pivot row
        double div = linalg_matrix_get(matrix, r, lead);
        if (fabs(div) > EPSILON) {
            for (size_t j = 0; j < cols; ++j) {
                linalg_matrix_set(
                    matrix,
                    r,
                    j,
                    linalg_matrix_get(matrix, r, j) / div
                );
            }
        }

        // Eliminate other rows
        for (size_t k = 0; k < rows; ++k) {
            if (k != r) {
                double mult = linalg_matrix_get(matrix, k, lead);
                for (size_t j = 0; j < cols; j++) {
                    linalg_matrix_set(
                        matrix, k, j,
                        linalg_matrix_get(matrix, k, j)
                        - mult * linalg_matrix_get(matrix, r, j)
                    );
                }
            }
        }
        ++lead;
    }
    return 0;
}
