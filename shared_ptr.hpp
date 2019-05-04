/*
    author dzhiblavi
 */

#ifndef shared_ptr_hpp
#define shared_ptr_hpp

template<typename T>
struct pointer_handler {
    using pointer = T*;

    pointer _ptr = nullptr;
    size_t cnt = 0;
};

template <typename T>
class shared_ptr {
    using value_type = T;
    using pointer = T *;

    pointer_handler<T> *_handler = nullptr;

    void _destruct_handler() {
        if (_handler && !--_handler->cnt) {
            operator delete(_handler->_ptr);
            delete _handler;
        }
    }

public:
    shared_ptr() = default;

    shared_ptr(shared_ptr const& rhs) {
        if (rhs._handler) {
            _handler = rhs._handler;
            ++_handler->cnt;
        }
    }

    shared_ptr(shared_ptr&& rhs) {
        swap(rhs);
    }

    shared_ptr(pointer _n_ptr) {
        _handler = new pointer_handler<T>;
        _handler->_ptr = _n_ptr;
        _handler->cnt = 1;
    }

    ~shared_ptr() {
        _destruct_handler();
    }

    shared_ptr &operator=(shared_ptr const& rhs) {
        if (this == &rhs)
            return *this;
        _destruct_handler();
        _handler = rhs._handler;
        if (rhs._handler)
            ++_handler->cnt;
        return *this;
    }

    shared_ptr &operator=(shared_ptr&& rhs) {
        swap(rhs);
        return *this;
    }

    void swap(shared_ptr& rhs) {
        std::swap(_handler, rhs._handler);
    }

    void reset() {
        shared_ptr().swap(*this);
    }

    void reset(pointer _n_ptr) {
        shared_ptr(_n_ptr).swap(*this);
    }

    bool unique() const {
        return !_handler || _handler->cnt == 1;
    }

    size_t use_count() const {
        return _handler ? _handler->cnt : 1;
    }

    pointer get() const {
        return _handler ? _handler->_ptr : nullptr;
    }
};

#endif /* shared_ptr_hpp */
