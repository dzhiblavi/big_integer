/*
    author dzhiblavi
 */

#include <big_integer.hpp>
#include <cstring>
#include <cstdlib>
#include <cassert>

big_integer big_integer::from_unsigned_long(uint64_t val) {
    big_integer ret;
    if (val) {
        ret._data.push_back(val);
    }
    return ret;
}

big_integer::big_integer(int64_t val)
        : _sgn(val < 0) {
    if (val) {
        _data.push_back((digit_t) (val < 0 ? -val : val));
    }
}

big_integer::big_integer(big_integer &&bi) noexcept {
    swap(bi);
}

big_integer::big_integer(const std::string &val) {
    big_integer tmp;
    _sgn = (val[0] == '-');
    auto i = (size_t) _sgn;
    big_integer pow10 = _core::_pow10(18);
    for (; i + 19 <= val.size(); i += 18) {
        tmp *= pow10;
        tmp += _read_digit(val, i, 18);
    }
    if (i < val.size()) {
        tmp *= _core::_pow10(val.size() - i);
        tmp += _read_digit(val, i, val.size() - i);
    }
    tmp._sgn = _sgn;
    swap(tmp);
    _normalize();
}

big_integer &big_integer::operator=(big_integer &&bi) noexcept {
    swap(bi);
    return *this;
}

void big_integer::swap(big_integer &bi) noexcept {
    std::swap(_data, bi._data);
    std::swap(_sgn, bi._sgn);
}

uint64_t big_integer::_read_digit(const std::string &s, size_t j, size_t len) noexcept {
    digit_t ret = 0;
    for (size_t i = 0; i < len; ++i) {
        ret = ret * 10 + (s[j + i] - '0');
    }
    return ret;
}

big_integer &big_integer::operator+=(const big_integer &bi) {
    if (is_zero()) {
        return *this = bi;
    }
    _data.detach();
    if (_sgn == bi._sgn) {
        if (_data.size() < bi._data.size()) {
            _data.resize(bi._data.size());
        }
        if (_core::_asm_add(_data.data(), bi._data.data(), bi._data.size())) {
            if (_data.size() == bi._data.size()) {
                _data.push_back(1);
            } else if (_core::_asm_short_add(_data.data() + bi._data.size(), 1, _data.size() - bi._data.size())) {
                _data.push_back(1);
            }
        }
    } else {
        _sgn ^= 1;
        (*this) -= bi;
        _sgn ^= 1;
    }
    _normalize();
    return *this;
}

big_integer &big_integer::operator-=(const big_integer &bi) {
    if (is_zero()) {
        return *this = -bi;
    }
    _data.detach();
    if (_sgn == bi._sgn) {
        int cmp = _compare(_data.data(), bi._data.data(), _data.size(), bi._data.size());
        if (cmp == 0) {
            return *this = big_integer();
        } else if (cmp > 0) {
            if (_core::_asm_sub(_data.data(), bi._data.data(), bi._data.size())) {
                _core::_asm_short_sub(_data.data() + bi._data.size(), 1, _data.size() - bi._data.size());
            }
        } else {
            big_integer tmp(bi);
            tmp -= *this;
            tmp._sgn ^= 1;
            swap(tmp);
        }
    } else {
        _sgn ^= 1;
        *this += bi;
        _sgn ^= 1;
    }
    _normalize();
    return *this;
}

big_integer &big_integer::operator*=(const big_integer &bi) {
    if (_data.size() < 128 || bi._data.size() < 128) {
        return _naive_mul(bi);
    }
    return *this = _karat_mul(*this, bi);
}

big_integer &big_integer::_naive_mul(big_integer const &bi) {
    _data.detach();
    if (is_zero() || bi.is_zero()) {
        _data.resize(0);
        _sgn = false;
        return *this;
    }
    vector<digit_t> dt(_data.size() + bi._data.size());
    _core::_asm_mul(dt.data(), _data.data(), bi._data.data(), _data.size(), bi._data.size());
    std::swap(_data, dt);
    _sgn ^= bi._sgn;
    _normalize();
    return *this;
}

big_integer big_integer::_karat_mul(big_integer const &ai, big_integer const &bi) {
    size_t k = (ai._data.size() > bi._data.size() ? ai._data.size() : bi._data.size()) / 2;
    big_integer ah(ai._higher(k));
    big_integer al(ai._lower(k));
    big_integer bh(bi._higher(k));
    big_integer bl(bi._lower(k));
    big_integer ahbh = ah * bh;
    big_integer albl = al * bl;
    big_integer alal = (al + ah) * (bl + bh);
    alal -= albl;
    alal -= ahbh;
    alal._shift_left(k);
    big_integer blbl = ahbh;
    blbl._shift_left(k << 1);
    big_integer ret = albl + alal + blbl;
    ret._sgn = ai._sgn ^ bi._sgn;
    ret._normalize();
    return ret;
}

big_integer big_integer::from_uint128_t(__uint128_t x) {
    big_integer ret;
    while (x) {
        ret._data.push_back(x & UINT64_MAX);
        x >>= 64;
    }
    return ret;
}

big_integer big_integer::_division_impl(big_integer const& bi) {
    _data.detach();
    if (is_zero()) {
        _data.resize(0);
        _sgn = false;
        return big_integer();
    }
    int cmp = _compare(_data.data(), bi._data.data(), _data.size(), bi._data.size());
    if (cmp < 0) {
        big_integer ret;
        swap(ret);
        return ret;
    } else if (cmp == 0) {
        return *this = big_integer((int64_t) (_sgn ^ bi._sgn ? -1 : 1));
    }
    if (bi._data.size() == 1) {
        uint64_t x;
        div_long_short(bi._data[0], x);
        bool olsgn = _sgn;
        _sgn ^= bi._sgn;
        return big_integer(olsgn ? -(int64_t)x : (int64_t)x);
    }
    big_integer v(bi);
    v._data.detach();
    bool old_sgn = _sgn;
    _sgn = false;
    v._sgn = false;

    static big_integer BASE = from_uint128_t(_core::t64);
    big_integer d = from_uint128_t(_core::t64 / (__uint128_t(1) + __uint128_t(v._data.back())));
    if (d >= BASE) d = BASE - 1;

    size_t n = v._data.size();
    size_t m = _data.size() - n;

    *this *= d;
    v *= d;
    _data.resize(n + m + 1);
    v._data.resize(n + 1);
    big_integer q, cq, r, vq;
    q._data.resize(m + 1);

    big_integer vdata2 = from_unsigned_long(v._data[n - 2]);
    big_integer vdata1 = from_unsigned_long(v._data[n - 1]);
    _core::set_constant_divisor(v._data[n - 1]);
    digit_t rm;

    for (size_t j = m + 1; j-- > 0;) {
        cq = from_uint128_t(_core::divd(__uint128_t(_data[j + n]) * _core::t64 + __uint128_t(_data[j + n - 1]), v._data[n - 1], rm));
        r = from_unsigned_long(rm);
        while (cq == BASE || cq * vdata2 > BASE * r + from_unsigned_long(_data[j + n - 2])) {
            --cq;
            r += vdata1;
        }
        vq = v * cq;
        vq._data.resize(n + 1);
        q._data[j] = (!cq._data.empty() ? cq._data[0] : 0);
        _core::_asm_sub(_data.data() + j, vq._data.data(), n + 1);
    }
    q._normalize();
    _normalize();
    q._sgn = old_sgn ^ bi._sgn;
    _sgn = old_sgn;
    swap(q);
    q.div_long_short(d._data[0], d._data[0]);
    return q;
}

big_integer &big_integer::operator/=(const big_integer &bi) {
    _division_impl(bi);
    return *this;
}

big_integer &big_integer::operator%=(const big_integer &bi) {
    *this = _division_impl(bi);
    return *this;
}

big_integer &big_integer::div_long_short(digit_t x, digit_t& rm) {
    _core::set_constant_divisor(x);
    rm = _core::_fast_short_div(_data.data(), x, _data.size());
    _normalize();
    return *this;
}

big_integer &big_integer::operator++() {
    *this += (digit_t) (1);
    return *this;
}

const big_integer big_integer::operator++(int) {
    big_integer ret(*this);
    ++(*this);
    return ret;
}

big_integer &big_integer::operator--() {
    *this -= 1;
    return *this;
}

const big_integer big_integer::operator--(int) {
    big_integer ret(*this);
    --(*this);
    return ret;
}

big_integer big_integer::operator-() const {
    if (is_zero())
        return *this;
    big_integer ret(*this);
    ret._sgn ^= 1;
    return ret;
}

big_integer big_integer::operator+() const {
    big_integer ret(*this);
    return ret;
}

big_integer big_integer::operator~() {
    return -*this - 1;
}

big_integer &big_integer::operator<<=(size_t s) {
    detach();
    size_t l64 = s % 64;
    size_t f64 = s / 64;
    *this *= ((digit_t) 1 << l64);
    if (!f64) {
        return *this;
    }
    _shift_left(f64);
    _normalize();
    return *this;
}

big_integer &big_integer::operator>>=(size_t s) {
    detach();
    size_t l64 = s % 64;
    size_t f64 = s / 64;
    *this /= ((digit_t) 1 << l64);
    if (f64) {
        _shift_right(f64);
    }
    _normalize();
    if (_sgn)
        --(*this);
    return *this;
}

void big_integer::_to_moved_repr() {
    if (!_sgn || is_zero()) {
        return;
    }
    for (size_t i = 0; i < _data.size(); ++i) {
        _data[i] = ~_data[i];
    }
    _sgn = false;
    ++(*this);
    _sgn = true;
}

void big_integer::_to_signed_repr() {
    if (!_sgn || is_zero()) {
        return;
    }
    _sgn = false;
    --(*this);
    _sgn = true;
    for (size_t i = 0; i < _data.size(); ++i) {
        _data[i] = ~_data[i];
    }
}

big_integer &big_integer::_apply_bitwise(big_integer const &bi, digit_t (*f)(digit_t, digit_t)) {
    big_integer tb(bi);
    tb._data.detach();
    _data.detach();
    if (_data.size() != tb._data.size()) {
        size_t msz = _data.size() > tb._data.size() ? _data.size() : tb._data.size();
        _data.resize(msz);
        tb._data.resize(msz);
    }
    _to_moved_repr();
    tb._to_moved_repr();
    for (size_t i = 0; i < _data.size(); ++i) {
        _data[i] = f(_data[i], tb._data[i]);
    }
    _sgn = (bool) f((digit_t) _sgn, (digit_t) tb._sgn);
    _normalize();
    _to_signed_repr();
    _normalize();
    return *this;
}

big_integer &big_integer::operator&=(big_integer const &bi) {
    return *this = _apply_bitwise(bi, [](digit_t a, digit_t b) -> digit_t { return a & b; });
}

big_integer &big_integer::operator|=(big_integer const &bi) {
    return *this = _apply_bitwise(bi, [](digit_t a, digit_t b) -> digit_t { return a | b; });
}

big_integer &big_integer::operator^=(big_integer const &bi) {
    return *this = _apply_bitwise(bi, [](digit_t a, digit_t b) -> digit_t { return a ^ b; });
}

big_integer operator<<(big_integer bi, size_t x) {
    bi <<= x;
    return bi;
}

big_integer operator>>(big_integer bi, size_t x) {
    bi >>= x;
    return bi;
}

bool operator==(const big_integer &a, const big_integer &b) {
    return a._sgn == b._sgn && !big_integer::_compare(a._data.data(), b._data.data(), a._data.size(), b._data.size());
}

bool operator!=(const big_integer &a, const big_integer &b) {
    return !(a == b);
}

bool operator<(const big_integer &a, const big_integer &b) {
    if (a._sgn != b._sgn) return a._sgn;
    return a._sgn ^ (big_integer::_compare(a._data.data(), b._data.data(), a._data.size(), b._data.size()) < 0);
}

bool operator>(const big_integer &a, const big_integer &b) {
    if (a._sgn != b._sgn) return b._sgn;
    return a._sgn ^ (big_integer::_compare(a._data.data(), b._data.data(), a._data.size(), b._data.size()) > 0);
}

bool operator<=(const big_integer &a, const big_integer &b) {
    if (a._sgn != b._sgn) return a._sgn;
    return a._sgn ^ (big_integer::_compare(a._data.data(), b._data.data(), a._data.size(), b._data.size()) <=0);
}

bool operator>=(const big_integer &a, const big_integer &b) {
    if (a._sgn != b._sgn) return b._sgn;
    return a._sgn ^ (big_integer::_compare(a._data.data(), b._data.data(), a._data.size(), b._data.size()) >= 0);
}

big_integer operator+(big_integer a, const big_integer &b) {
    a += b;
    return a;
}

big_integer operator-(big_integer a, const big_integer &b) {
    a -= b;
    return a;
}

big_integer operator*(big_integer a, const big_integer &b) {
    a *= b;
    return a;
}

big_integer operator/(big_integer a, const big_integer &b) {
    a /= b;
    return a;
}

big_integer operator%(big_integer a, const big_integer &b) {
    a %= b;
    return a;
}

big_integer operator&(big_integer a, const big_integer &b) {
    a &= b;
    return a;
}

big_integer operator|(big_integer a, const big_integer &b) {
    a |= b;
    return a;
}

big_integer operator^(big_integer a, const big_integer &b) {
    a ^= b;
    return a;
}

std::string to_string(const big_integer &bi) {
    if (bi.is_zero()) return "0";
    big_integer tmp(std::move(bi));
    tmp._data.detach();
    std::string ret;
    ret.reserve(bi._data.size() * 20);
    uint64_t rm;
    _core::set_constant_divisor(_core::_pow10(18));
    while (!tmp.is_zero()) {
        rm = _core::_fast_short_div(tmp._data.data(), _core::_pow10(18), tmp._data.size());
        tmp._normalize();
        for (size_t i = 0; i < 18; ++i) {
            ret.push_back(char('0' + rm % 10));
            rm /= 10;
        }
    }
    while (!ret.empty() && ret.back() == '0') {
        ret.pop_back();
    }
    if (bi._sgn) {
        ret.push_back('-');
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

bool big_integer::is_zero() const noexcept {
    return _data.empty() && !_sgn;
}

bool big_integer::unique() const {
    return _data.unique();
}

size_t big_integer::count() const {
    return _data.count();
}

void big_integer::detach() {
    _data.detach();
}

std::ostream &operator<<(std::ostream &os, const big_integer &bi) {
    os << to_string(bi);
    return os;
}

std::istream &operator>>(std::istream &is, big_integer &bi) {
    std::string source;
    is >> source;
    bi = big_integer(source);
    return is;
}

void big_integer::_normalize() {
    if (is_zero()) return;
    while (!_data.empty() && !_data.back()) {
        _data.pop_back();
    }
    if (_data.empty()) _sgn = false;
}

int big_integer::_compare(big_integer::const_ptr p, big_integer::const_ptr q, size_t szp, size_t szq) {
    if (szp != szq) {
        return (szp < szq ? -1 : 1);
    }
    for (size_t i = szp; i-- > 0;) {
        if (p[i] != q[i]) {
            return p[i] < q[i] ? -1 : 1;
        }
    }
    return 0;
}

big_integer big_integer::_higher(size_t k) const {
    if (k >= _data.size()) {
        return big_integer();
    }
    big_integer re;
    re._data.resize(_data.size() - k);
    memcpy(re._data.data(), _data.data() + k, DIGIT_SIZE * re._data.size());
    return re;
}

big_integer big_integer::_lower(size_t k) const {
    if (k >= _data.size()) {
        return *this;
    }
    big_integer re;
    re._data.resize(k);
    memcpy(re._data.data(), _data.data(), DIGIT_SIZE * re._data.size());
    return re;
}

big_integer &big_integer::_shift_left(size_t k) {
    if (!k) {
        return *this;
    }
    _data.resize(_data.size() + k);
    memmove(_data.data() + k, _data.data(), DIGIT_SIZE * (_data.size() - k));
    memset(_data.data(), 0, DIGIT_SIZE * k);
    return *this;
}

big_integer &big_integer::_shift_right(size_t k) {
    if (!k) {
        return *this;
    }
    memmove(_data.data(), _data.data() + k, DIGIT_SIZE * (_data.size() - k));
    _data.resize(_data.size() - k);
    return *this;
}
