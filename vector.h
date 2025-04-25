#include <iostream>
#include <vector>
#include <mutex>
#include <string>

template <class T>
class ts_vector {
private:
    std::vector<T> _vec;
    mutable std::mutex _m;

public:
    void push_back(const T& value) {
        std::lock_guard<std::mutex> lk(this->_m);
        _vec.push_back(value);
    }

    void erase(const size_t index) {
        std::lock_guard<std::mutex> lk(this->_m);
        if (index < _vec.size()) {
            _vec.erase(_vec.begin() + index);
        }
    }

    void erase_element(const T* element) {
        std::lock_guard<std::mutex> lk(this->_m);
        for (size_t i = 0; i < _vec.size(); ++i) {
            if (_vec[i] == element) {
                _vec.erase(_vec.begin() + i);
                --i;
            }
        }
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return _vec.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return _vec.size();
    }

    T& operator[](size_t index) const {
        std::lock_guard<std::mutex> lk(this->_m);
        return _vec[index];
    }

    auto begin() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return _vec.begin();
    }

    auto end() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return _vec.end();
    }

    void clear() {
        std::lock_guard<std::mutex> lk(this->_m);
        _vec.clear();
    }

    std::vector<T> copy_of_original() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return _vec;
    }
};
