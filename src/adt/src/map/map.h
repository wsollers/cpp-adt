#ifndef MAP_H
#define MAP_H

#include <cstdlib>
#include <stdint.h>
#include <optional>

namespace Maps {

// A map is a collection of key-value pairs

template <typename K, typename V, int32_t capacity> class Map {
public:
  virtual ~Map() = default;

  // Insert a key-value pair
  virtual void insert(K key, V value) = 0;

  // Remove a key-value pair
  virtual void remove(K key) = 0;

  // Check if the map is empty
  virtual bool isEmpty() const = 0;

  // Get the number of key-value pairs in the map
  virtual size_t getSize() const = 0;

  // Check if the map contains a key
  virtual bool contains(K key) const = 0;

  // Get the value associated with a key
  virtual V get(K key) const = 0;

  // Set the value associated with a key
  virtual void set(K key, V value) = 0;
};

template <typename K, typename V> class MapEntry {
public:
  MapEntry() : key{}, value() {}
  MapEntry(K key, V value) : key(key), value(value) {}

  K getKey() const { return key; }

  V getValue() const { return value; }
private:
  K key;
  V value;
};

template <typename K, typename V, int32_t capacity> class ArrayMap : public Map<K, V, capacity> {
public:

  ArrayMap() : size(0), entries{} {}

  void insert(K key, V value) override {
    if (size == capacity) {
      return;
    }
    entries[size++] = MapEntry<K,V>(key, value);
  }

  void remove(K key) override {
    for (size_t i = 0; i < size; i++) {
      if (entries[i].has_value() && entries[i].value().getKey() == key) {
        for (size_t j = i; j < size - 1; j++) {
          entries[j] = entries[j + 1];
        }
        size--;
        return;
      }
    }
  }

  bool isEmpty() const override {
    return size == 0;
  }

  size_t getSize() const override {
    return size;
  }

  bool contains(K key) const override {
    for (size_t i = 0; i < size; i++) {
      if (entries[i].has_value() && entries[i].value().getKey() == key) {
        return true;
      }
    }
    return false;
  }

  V get(K key) const override {
    for (size_t i = 0; i < size; i++) {
      if (entries[i].has_value()  && entries[i].value().getKey() == key) {
        return entries[i].value().getValue();
      }
    }
    return V();
  }

  void set(K key, V value) override {
    for (size_t i = 0; i < size; i++) {
      if ( entries[i].has_value() && entries[i].value().getKey() == key) {
        entries[i] = MapEntry<K,V>(key, value);
        return;
      }
    }
  }

private:

  size_t size;
  std::optional<MapEntry<K,V>> entries[capacity];

};


template <typename K, typename V, int32_t capacity> class HashMap : public Map<K, V, capacity> {
};

} // namespace Maps

#endif // MAP_H
