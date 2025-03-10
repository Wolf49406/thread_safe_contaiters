#include <iostream>
#include <unordered_map>
#include <mutex>
#include <string>

template <class K, class V, class Hash = std::hash<K>>
class ts_map {
private:
    std::unordered_map<K, V, Hash> _map;
    mutable std::mutex _m;

public:
    auto begin() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_map.begin();
    }

    auto end() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_map.end();
    }

    void set(const K& key, const V& value) {
        std::lock_guard<std::mutex> lk(this->_m);
        this->_map[key] = value;
    }

    V& operator[](const K& key) {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_map[key];
    }

    V& get(const K& key) {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_map.at(key);
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_map.empty();
    }

    void clear() {
        std::lock_guard<std::mutex> lk(this->_m);
        this->_map.clear();
    }

    bool contains(const K& key) const {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_map.find(key) != this->_map.end();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_map.size();
    }

    void erase(const K& key) {
        std::lock_guard<std::mutex> lk(this->_m);
        this->_map.erase(key);
    }

    std::unordered_map<K, V> copy_of_original() const {
        std::lock_guard<std::mutex> lk(this->_m);
        return this->_map;
    }
};
