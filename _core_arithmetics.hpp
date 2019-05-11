/*
    author dzhiblavi
 */

#ifndef _core_arithmetics
#define _core_arithmetics

#include <stdint.h>
#include <cstddef>

#ifdef __APPLE__
#define _asm_add asm_add
#define _asm_sub asm_sub
#define _asm_mul asm_mul
#define _asm_short_add asm_short_add
#define _asm_short_sub asm_short_sub
#endif

namespace _core {
    extern "C" {
        uint64_t _asm_add(uint64_t *, uint64_t const *, size_t);
        uint64_t _asm_sub(uint64_t *, uint64_t const *, size_t);
        uint64_t _asm_mul(uint64_t *, uint64_t const *, uint64_t const *, size_t, size_t);
        uint64_t _asm_short_add(uint64_t *, uint64_t, size_t);
        uint64_t _asm_short_sub(uint64_t *, uint64_t, size_t);
    }

    const __uint128_t t64 = __uint128_t(1) << 64;
    
    void set_constant_divisor(uint64_t d);
    uint64_t divd(__uint128_t n, uint64_t d, uint64_t& rm);
    uint64_t _pow10(size_t);
    uint64_t _fast_short_div(uint64_t *, uint64_t, size_t);
}

#endif /* _core_arithmetics.hpp */
