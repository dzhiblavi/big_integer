/*
    author dzhiblavi
 */

#ifndef vector_hpp
#define vector_hpp

#include <cstddef>
#include <type_traits>
#include <cstring>
#include <memory>
#include <shared_ptr.hpp>

template<typename T>
T* _allocate_new_zone(T const* __restrict _src, size_t size, size_t alloc) {
    auto _alloc_data = static_cast<T *> (operator new(alloc * sizeof(T)));
    std::copy(_src, _src + size, _alloc_data);
    return _alloc_data;
}

/*
 * small object
 * copy-on-write
 * */
template<typename T, size_t _INIT_SO_SIZE = 6>
class vector {
public:
    using value_type = T;
    using reference = T &;
    using const_reference = T const &;
    using pointer = T *;
    using const_pointer = T const *;
    using shared_pointer = shared_ptr<T>;

private:
    T _small[_INIT_SO_SIZE];
    shared_pointer _shp;
    pointer _data = _small;

    size_t _size = 0;
    size_t _capacity = _INIT_SO_SIZE;

    void _set_unique_large_data(pointer __restrict _allocated, size_t new_capacity) {
        _shp.reset(_allocated);
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
            std::destroy(_alloc_data, _alloc_data + _size);
            operator delete(_alloc_data);
            throw;
        }
        std::destroy(_data, _data + _size);
        _set_unique_large_data(_alloc_data, new_capacity);
    }

    void _resize_short_path(size_t new_size) {
        if (new_size > _size) {
            std::uninitialized_fill(_data + _size, _data + new_size, T());
        } else if (new_size < _size) {
            std::destroy(_data + new_size, _data + _size);
        }
    }

    void _resize_long_path(size_t new_size) {
        pointer _alloc_data = _allocate_new_zone(_data, _size, new_size);
        try {
            std::uninitialized_fill(_alloc_data + _size, _alloc_data + new_size, T());
        } catch (...) {
            std::destroy(_alloc_data, _alloc_data + _size);
            operator delete(_alloc_data);
            throw;
        }
        std::destroy(_data, _data + _size);
        _set_unique_large_data(_alloc_data, new_size);
    }

public:
    vector() = default;

    template<typename = typename std::enable_if<std::is_default_constructible_v<T>>::type>
    explicit vector(size_t initial_size) {
        if (initial_size <= _INIT_SO_SIZE) {
            std::uninitialized_fill(_data, _data + initial_size, T());
        } else {
            auto _alloc_data = static_cast<pointer> (operator new(initial_size * sizeof(T)));
            try {
                std::uninitialized_fill(_alloc_data, _alloc_data + initial_size, T());
            } catch (...) {
                operator delete (_alloc_data);
            }
            _set_unique_large_data(_alloc_data, initial_size);
        }
        _size = initial_size;
    }

    ~vector() noexcept {
        std::destroy(_data, _data + _size);
    }

    vector(vector &&rhs) {
        swap(rhs);
    }

    vector(vector const &rhs) {
        if (rhs._size <= _INIT_SO_SIZE) {
            std::copy(rhs._data, rhs._data + rhs._size, _data);
        } else {
            _shp = rhs._shp;
            _data = rhs._data;
            _capacity = rhs._capacity;
        }
        _size = rhs._size;
    }

    vector& swap(vector &v) {
        if (small() && v.small()) {
            std::swap_ranges(_data, _data + _INIT_SO_SIZE, v._data);
        } else if (small()) {
            std::copy(_small, _small + _size, v._small);
            std::swap(_shp, v._shp);
            std::swap(_data, v._data);
            _capacity = v._capacity;
            v._set_unique_small_data();
        } else if (v.small()) {
            v.swap(*this);
        } else {
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
            std::copy(rhs._data, rhs._data + rhs._size, _small);
            std::destroy(_data, _data + _size);
            _shp.reset();
            _set_unique_small_data();
        } else {
            if (_shp.unique()) {
                std::destroy(_data, _data + _size);
            }
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
        if (!_shp.unique()) {
            _set_unique_large_data(_allocate_new_zone(_data, _size, _capacity), _capacity);
        }
    }

    void push_back(const_reference x) {
        if (_size < _capacity) {
            _push_back_short_path(x);
        } else {
            _push_back_long_path(x);
        }
        ++_size;
    }

    void pop_back() noexcept {
        --_size;
        _data[_size].~T();
    }

    void resize(size_t new_size) {
        if (new_size <= _capacity) {
            _resize_short_path(new_size);
        } else {
            _resize_long_path(new_size);
        }
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
