// ISO Includes
#include <errno.h>

// Local Includes
#include <linalg/fraction.h>

static long long int gcd(long long int a, long long int b) {
    while (b != 0) {
        const long long int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a >= 0 ? a : -a;
}

int linalg_frac_init(
    struct linalg_frac* const frac,
    const long long int num,
    const long long int den
) {
    if (den == 0) {
        errno = EINVAL;
        return -1;
    }

    frac->f_num = num;
    frac->f_den = den;

    return 0;
}

struct linalg_frac linalg_frac_simp(struct linalg_frac frac) {
    const long long int common_fact = gcd(frac.f_num, frac.f_den);
    frac.f_num /= common_fact;
    frac.f_den /= common_fact;

    if (frac.f_den < 0) {
        frac.f_num = -frac.f_num;
        frac.f_den = -frac.f_den;
    }

    return frac;
}
