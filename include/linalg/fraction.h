#ifndef C_LINEAR_ALGEBRA_FRACTION_H
#define C_LINEAR_ALGEBRA_FRACTION_H

// ISO Includes
#include <stddef.h>
#include <stdio.h>

struct linalg_frac {
    long long int f_num;
    long long int f_den;
};

extern int linalg_frac_init(
    struct linalg_frac* frac,
    long long int num,
    long long int den
);

static inline void linalg_frac_print(const struct linalg_frac frac) {
    printf("%lld/%lld", frac.f_num, frac.f_den);
}

static inline int linalg_frac_sprint(
    const struct linalg_frac frac,
    char* str
) {
    return sprintf(str, "%lld/%lld", frac.f_num, frac.f_den) != -1 ? 0 : -1;
}

extern struct linalg_frac linalg_frac_simp(struct linalg_frac frac);

extern struct linalg_frac linalg_frac_add(
    struct linalg_frac lhs,
    struct linalg_frac rhs
);

extern struct linalg_frac linalg_frac_sub(
    struct linalg_frac lhs,
    struct linalg_frac rhs
);

static inline struct linalg_frac linalg_frac_mult(
    const struct linalg_frac lhs,
    const struct linalg_frac rhs
) {
    return (struct linalg_frac){
        .f_num = lhs.f_num * rhs.f_num,
        .f_den = lhs.f_den * rhs.f_den
    };
}

static inline struct linalg_frac linalg_frac_div(
    const struct linalg_frac lhs,
    const struct linalg_frac rhs
) {
    // Apply keep, change, flip
    return (struct linalg_frac){
        .f_num = lhs.f_num * rhs.f_den,
        .f_den = lhs.f_den * rhs.f_num
    };
}

#endif // #ifndef C_LINEAR_ALGEBRA_FRACTION_H
