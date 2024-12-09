#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>
#include <algorithm>

namespace Heaps {

// Purely abstract HeapADT<T>
template <typename T>
class HeapADT {
public:
    virtual ~HeapADT() = default;

    // Virtual methods for heap functionality
    virtual void insert(const T& value) = 0;
    virtual void remove() = 0;
    virtual const T& top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual std::size_t size() const = 0;
    virtual void clear() = 0;
};

// MinHeap implementation
template <typename T>
class MinHeap : public HeapADT<T> {
private:
    std::vector<T> data;

    void heapifyUp(std::size_t index) {
        while (index > 0) {
            std::size_t parent = (index - 1) / 2;
            if (data[index] >= data[parent]) break;
            std::swap(data[index], data[parent]);
            index = parent;
        }
    }

    void heapifyDown(std::size_t index) {
        std::size_t size = data.size();
        while (index < size) {
            std::size_t left = 2 * index + 1;
            std::size_t right = 2 * index + 2;
            std::size_t smallest = index;

            if (left < size && data[left] < data[smallest]) smallest = left;
            if (right < size && data[right] < data[smallest]) smallest = right;

            if (smallest == index) break;

            std::swap(data[index], data[smallest]);
            index = smallest;
        }
    }

public:
    void insert(const T& value) override {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    void remove() override {
        if (isEmpty()) throw std::runtime_error("Heap is empty");
        data[0] = data.back();
        data.pop_back();
        heapifyDown(0);
    }

    const T& top() const override {
        if (isEmpty()) throw std::runtime_error("Heap is empty");
        return data[0];
    }

    bool isEmpty() const override {
        return data.empty();
    }

    std::size_t size() const override {
        return data.size();
    }

    void clear() override {
        data.clear();
    }
};

// MaxHeap implementation
template <typename T>
class MaxHeap : public HeapADT<T> {
private:
    std::vector<T> data;

    void heapifyUp(std::size_t index) {
        while (index > 0) {
            std::size_t parent = (index - 1) / 2;
            if (data[index] <= data[parent]) break;
            std::swap(data[index], data[parent]);
            index = parent;
        }
    }

    void heapifyDown(std::size_t index) {
        std::size_t size = data.size();
        while (index < size) {
            std::size_t left = 2 * index + 1;
            std::size_t right = 2 * index + 2;
            std::size_t largest = index;

            if (left < size && data[left] > data[largest]) largest = left;
            if (right < size && data[right] > data[largest]) largest = right;

            if (largest == index) break;

            std::swap(data[index], data[largest]);
            index = largest;
        }
    }

public:
    void insert(const T& value) override {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    void remove() override {
        if (isEmpty()) throw std::runtime_error("Heap is empty");
        data[0] = data.back();
        data.pop_back();
        heapifyDown(0);
    }

    const T& top() const override {
        if (isEmpty()) throw std::runtime_error("Heap is empty");
        return data[0];
    }

    bool isEmpty() const override {
        return data.empty();
    }

    std::size_t size() const override {
        return data.size();
    }

    void clear() override {
        data.clear();
    }
};

} // namespace Heaps

#endif // HEAP_H
