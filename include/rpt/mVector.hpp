#pragma once
#include <algorithm>
#include <format>
#include <iostream>
#include <stdexcept>

namespace rpt {

template <typename T> class mVector {
public:
    using value_type = T;

    mVector() : m_arr(nullptr), m_size(0), m_allocated(0) {}

    mVector(std::initializer_list<T> init) : m_arr(new T[init.size()]), m_size(init.size()), m_allocated(init.size()) {
        std::copy(init.begin(), init.end(), m_arr);
    }

    mVector(const mVector &other)
    : m_arr(new T[other.m_allocated])
    , m_size(other.m_size)
    , m_allocated(other.m_allocated) {
        std::copy(other.m_arr, other.m_arr + m_size, m_arr);
    }

    mVector(mVector &&other) noexcept : m_arr(other.m_arr), m_size(other.m_size), m_allocated(other.m_allocated) {
        other.m_arr       = nullptr;
        other.m_size      = 0;
        other.m_allocated = 0;
    }

    mVector &operator=(const mVector &other) {
        if (this != &other) {
            T *tmp = new T[other.m_allocated];
            std::copy(other.m_arr, other.m_arr + other.m_size, tmp);

            delete[] m_arr;
            m_arr       = tmp;
            m_size      = other.m_size;
            m_allocated = other.m_allocated;
        }
        return *this;
    }

    mVector &operator=(mVector &&other) noexcept {
        if (this != &other) {
            delete[] m_arr;
            m_arr       = other.m_arr;
            m_size      = other.m_size;
            m_allocated = other.m_allocated;

            other.m_arr       = nullptr;
            other.m_size      = 0;
            other.m_allocated = 0;
        }
        return *this;
    }

    void pushBack(T value) {
        if (m_size >= m_allocated) {
            allocate(1 + m_allocated * m_coef);
        }
        m_arr[m_size] = value; // NOLINT
        m_size += 1;
    }

    T popBack() {
        if (m_size <= 0) {
            throw std::out_of_range("Vector is empty");
        }
        m_size -= 1;
        return m_arr[m_size]; // NOLINT
    }

    [[nodiscard]] T &at(size_t pos) const {
        if (pos < 0 || pos >= m_size) {
            throw std::out_of_range(std::format("Position: \"{}\" out of range (0,{})", pos, m_size));
        }
        return m_arr[pos];
    }

    T &front() {
        if (m_size == 0) {
            throw std::out_of_range("size is 0");
        }
        return m_arr[0];
    }

    T &back() {
        if (m_size == 0) {
            throw std::out_of_range("size is 0");
        }
        return m_arr[m_size - 1];
    }

    T &operator[](size_t pos) {
        if (pos < 0 || pos >= m_size) {
            throw std::out_of_range(std::format("Position: \"{}\" out of range (0,{})", pos, m_size)); // NOLINT
        }
        return m_arr[pos]; // NOLINT
    }

    const T &operator[](size_t pos) const { return m_arr[pos]; } // NOLINT

    T *begin() noexcept { return m_arr; }

    T *end() noexcept { return m_arr + m_size; }

    const T *cbegin() noexcept { return m_arr; }

    const T *cend() noexcept { return m_arr + m_size; }

    size_t size() const { return m_size; }

    size_t allocated() const { return m_allocated; }

    void allocate(size_t newSize) {
        T *tmp             = new T[newSize]; // NOLINT
        size_t rebase_size = std::min(m_allocated, newSize);

        for (size_t i = 0; i < rebase_size; i++) {
            tmp[i] = std::move(m_arr[i]); // NOLINT
        }
        delete[] m_arr;
        m_arr       = tmp;
        m_allocated = newSize;
    }

    bool empty() const noexcept { return m_size == 0; }

    ~mVector() { delete[] m_arr; }

private:
    T *m_arr;
    size_t m_size      = 0;
    size_t m_allocated = 0;
    int m_coef         = 2;
};
} // namespace rpt
