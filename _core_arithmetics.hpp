/*
    author dzhiblavi
 */

#ifndef _core_arithmetics
#define _core_arithmetics

#include <stdint.h>
#include <cstddef>

namespace _core {
    const __uint128_t t64 = __uint128_t(1) << 64;
    
    void set_constant_divisor(uint64_t d);
    uint64_t divd(__uint128_t n, uint64_t d, uint64_t& rm);
    uint64_t _pow10(size_t);

    uint64_t _fast_add(uint64_t *, uint64_t const *, size_t);
    uint64_t _fast_sub(uint64_t *, uint64_t const *, size_t);
    uint64_t _fast_mul(uint64_t *, uint64_t const *, uint64_t const *, size_t, size_t);
    uint64_t _fast_short_add(uint64_t *, uint64_t, size_t);
    uint64_t _fast_short_sub(uint64_t *, uint64_t, size_t);
    uint64_t _fast_short_div(uint64_t *, uint64_t, size_t);
}

#endif /* _core_arithmetics.hpp */
