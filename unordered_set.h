#include <iostream>
#include <unordered_set>
#include <mutex>
#include <string>

template <class T, class Hash = std::hash<T>>
class ts_set {
private:
    std::unordered_set<T, Hash> _set;
    mutable std::mutex _m;

public:
    void insert(const T& value) {
        std::lock_guard<std::mutex> lk(this->_m);
        this->_set.insert(value);
    }

    void erase(const T& value) {
        std::lock_guard<std::mutex> lk(this->_m);
        this->_set.erase(value);
    }

    bool contains(const T& value) const {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_set.find(value) != this->_set.end();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_set.size();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_set.empty();
    }

    void clear() {
        std::lock_guard<std::mutex> lk(this->_m);
        this->_set.clear();
    }

    std::unordered_set<T, Hash> copy_of_original() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_set;
    }

    void swap(std::unordered_set<T, Hash>& newSet) {
        std::lock_guard<std::mutex> lk(this->_m);
        this->_set.swap(newSet);
    }
};
