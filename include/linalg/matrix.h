#ifndef C_LINEAR_ALGEBRA_MATRIX_H
#define C_LINEAR_ALGEBRA_MATRIX_H

#include <stdlib.h>

#define linalg_matrix_at(m, i, j) \
    i * m.m_num_cols + j

struct linalg_matrix {
    size_t m_num_rows;
    size_t m_num_cols;
    double m_vals[];
};

extern struct linalg_matrix* linalg_matrix_init(
    size_t num_rows,
    size_t num_cols,
    double vals[num_rows][num_cols]
);

static inline void linalg_matrix_destroy(struct linalg_matrix* const matrix) {
    free(matrix);
}

static inline void linalg_matrix_set(
    struct linalg_matrix* const matrix,
    const size_t i,
    const size_t j,
    const double val
) {
    matrix->m_vals[linalg_matrix_at(*matrix, i, j)] = val;
}

static inline double linalg_matrix_get(
    const struct linalg_matrix* const matrix,
    const size_t i,
    const size_t j
) {
    return matrix->m_vals[linalg_matrix_at(*matrix, i, j)];
}

extern void linalg_matrix_print(const struct linalg_matrix* matrix);

extern int linalg_matrix_rref(struct linalg_matrix* matrix);

#endif // #ifndef C_LINEAR_ALGEBRA_MATRIX_H
