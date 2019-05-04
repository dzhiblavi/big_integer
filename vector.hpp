/*
    author dzhiblavi
 */

#ifndef vector_hpp
#define vector_hpp

#include <cstddef>
#include <type_traits>
#include <cstring>
#include <memory>
#include "shared_ptr.hpp"

template<typename T>
void _destruct(T *__restrict, size_t,
               typename std::enable_if<std::is_trivially_destructible<T>::value>::type * = 0) noexcept {}

template<typename T>
void _destruct(T *__restrict _data, size_t size,
               typename std::enable_if<!std::is_trivially_destructible<T>::value>::type * = 0) noexcept {
    for (size_t i = 0; i < size; ++i)
        _data[i].~T();
}

template<typename T>
void _copy_construct(T *__restrict _dst, T const *__restrict src, size_t size,
                     typename std::enable_if<std::is_trivially_copy_constructible<T>::value>::type * = 0) noexcept {
    memcpy(_dst, src, size * sizeof(T));
}

template<typename T>
void _copy_construct(T *__restrict _dst, T const *__restrict src, size_t size,
                     typename std::enable_if<!std::is_trivially_copy_constructible<T>::value>::type * = 0) {
    size_t i = 0;
    try {
        for (; i < size; ++i)
            new(_dst + i) T(src[i]);
    } catch (...) {
        _destruct(_dst, i);
        throw;
    }
}

template<typename T>
void _default_construct(T *__restrict _dst, size_t size,
                        typename std::enable_if<std::is_trivially_constructible<T>::value>::type * = 0) noexcept {
    memset(_dst, 0, size * sizeof(T));
}

template<typename T>
void _default_construct(T *__restrict _dst, size_t size,
                        typename std::enable_if<std::is_default_constructible<T>::value
                                                & !std::is_trivially_constructible<T>::value>::type * = 0) {
    size_t i = 0;
    try {
        for (; i < size; ++i)
            new(_dst + i) T();
    } catch (...) {
        _destruct(_dst, i);
        throw;
    }
}

#define SAFE_POINTER

#ifdef STD_POINTER
template<typename T>
using shared = std::shared_ptr<T>;
#endif
#ifdef SAFE_POINTER
template<typename T>
using shared = shared_ptr<T>;
#endif

/*
 * default-constructible only
 * small object optimisation implemented
 * copy-on-write optimisation implemented
 * */
template<typename T, size_t _INIT_SO_SIZE = 6,
         typename = typename std::enable_if<std::is_default_constructible<T>::value>::type>
class vector {
public:
    using value_type = T;
    using reference = T &;
    using const_reference = T const &;
    using pointer = T *;
    using const_pointer = T const *;
    using shared_pointer = shared<T>;

private:
    T _small[_INIT_SO_SIZE];
    shared_pointer _shp;
    pointer _data = _small;

    size_t _size = 0;
    size_t _capacity = _INIT_SO_SIZE;

    void _free_data() noexcept {
        _destruct(_data, _size);
    }

    pointer _allocate_new_zone(const_pointer __restrict _src, size_t size, size_t alloc) {
        pointer _alloc_data = static_cast<T *> (operator new(alloc * sizeof(T)));
        try {
            _copy_construct(_alloc_data, _src, size);
        } catch (...) {
            operator delete(_alloc_data);
            throw;
        }
        return _alloc_data;
    }

    void _set_unique_large_data(pointer __restrict _allocated, size_t new_capacity) {
#ifdef STD_POINTER
        _shp.reset(_allocated, [] (pointer _ptr) { operator delete(_ptr); });
#endif
#ifdef SAFE_POINTER
        _shp.reset(_allocated);
#endif
        _data = _allocated;
        _capacity = new_capacity;
    }

    void _set_unique_small_data() {
        _shp.reset();
        _data = _small;
        _capacity = _INIT_SO_SIZE;
    }

    void _push_back_short_path(const_reference x) {
        new(_data + _size) T(x);
    }

    void _push_back_long_path(const_reference x) {
        size_t new_capacity = _capacity << 1;
        pointer _alloc_data = _allocate_new_zone(_data, _size, new_capacity);
        try {
            new(_alloc_data + _size) T(x);
        } catch (...) {
            _destruct(_alloc_data, _size);
            operator delete(_alloc_data);
            throw;
        }
        _free_data();
        _set_unique_large_data(_alloc_data, new_capacity);
    }

    void _resize_short_path(size_t new_size) {
        if (new_size > _size)
            _default_construct(_data + _size, new_size - _size);
        else if (new_size < _size)
            _destruct(_data + new_size, _size - new_size);
    }

    void _resize_long_path(size_t new_size) {
        pointer _alloc_data = _allocate_new_zone(_data, _size, new_size);
        try {
            _default_construct(_alloc_data + _size, new_size - _size);
        } catch (...) {
            _destruct(_alloc_data, _size);
            operator delete(_alloc_data);
            throw;
        }
        _free_data();
        _set_unique_large_data(_alloc_data, new_size);
    }

public:
    vector() = default;

    explicit vector(size_t initial_size) {
        if (initial_size <= _INIT_SO_SIZE)
            _default_construct(_data, initial_size);
        else {
            pointer _alloc_data = static_cast<T *> (operator new(initial_size * sizeof(T)));
            try {
                _default_construct(_alloc_data, initial_size);
            } catch (...) {
                operator delete(_alloc_data);
                throw;
            }
            _set_unique_large_data(_alloc_data, initial_size);
        }
        _size = initial_size;
    }

    ~vector() noexcept {
        _free_data();
    }

    vector(vector &&rhs) {
        swap(rhs);
    }

    vector(vector const &rhs) {
        if (rhs._size <= _INIT_SO_SIZE)
            _copy_construct(_data, rhs._data, rhs._size);
        else {
            _shp = rhs._shp;
            _data = rhs._data;
            _capacity = rhs._capacity;
        }
        _size = rhs._size;
    }

    vector& swap(vector &v) {
        if (small() && v.small())
            for (size_t i = 0; i < std::max(_size, v._size); ++i)
                std::swap(_data[i], v._data[i]);
        else if (small()) {
            _copy_construct(v._small, _small, _size);
            std::swap(_shp, v._shp);
            std::swap(_data, v._data);
            _capacity = v._capacity;
            v._set_unique_small_data();
        } else if (v.small())
            v.swap(*this);
        else {
            std::swap(_shp, v._shp);
            std::swap(_data, v._data);
            std::swap(_capacity, v._capacity);
        }
        std::swap(_size, v._size);
        return *this;
    }

    vector& operator=(vector&& rhs) {
        swap(rhs);
        return *this;
    }

    vector& operator=(vector const &rhs) {
        if (rhs._size <= _INIT_SO_SIZE) {
            _copy_construct(_small, rhs._data, rhs._size);
            _free_data();
            _shp.reset();
            _set_unique_small_data();
        } else {
            if (_shp.unique())
                _free_data();
            _shp = rhs._shp;
            _data = rhs._data;
            _capacity = rhs._capacity;
        }
        _size = rhs._size;
        return *this;
    }

    bool unique() const {
        return _shp.unique();
    }

    size_t count() const {
        return _shp.use_count();
    }

    void detach() {
        if (!_shp.unique())
            _set_unique_large_data(_allocate_new_zone(_data, _size, _capacity), _capacity);
    }

    void push_back(const_reference x) {
        if (_size < _capacity)
            _push_back_short_path(x);
        else
            _push_back_long_path(x);
        ++_size;
    }

    void pop_back() noexcept {
        --_size;
        _destruct(_data + _size, 1);
    }

    void resize(size_t new_size) {
        if (new_size <= _capacity)
            _resize_short_path(new_size);
        else
            _resize_long_path(new_size);
        _size = new_size;
    }

    reference front() noexcept {
        return _data[0];
    }

    const_reference front() const noexcept {
        return _data[0];
    }

    reference back() noexcept {
        return _data[_size - 1];
    }

    const_reference back() const noexcept {
        return _data[_size - 1];
    }

    reference operator[](size_t i) {
        return _data[i];
    }

    const_reference operator[](size_t i) const noexcept {
        return _data[i];
    }

    pointer data() noexcept {
        return _data;
    }

    const_pointer data() const noexcept {
        return _data;
    }

    size_t size() const noexcept {
        return _size;
    }

    size_t capacity() const noexcept {
        return _capacity;
    }

    bool empty() const noexcept {
        return !_size;
    }

    bool small() const noexcept {
        return _data == _small;
    }
};

#endif /* vector.hpp */
