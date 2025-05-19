#pragma once
#include <concepts>
#include <rpt/mVector.hpp>
#include <vector>

namespace rpt {

template <typename T> concept Sortable = std::totally_ordered<T>;

template <typename C>
concept IndexableContainer = requires(C c, size_t i) {
    { c[i] } -> std::convertible_to<typename C::value_type>;
    { c.size() } -> std::convertible_to<size_t>;
};

template <Sortable T, IndexableContainer Container> size_t partition(Container &vec, size_t low, size_t high) {
    const T &pivot = vec[high];
    size_t i       = low;

    for (size_t j = low; j < high; ++j) {
        if (vec[j] < pivot) {
            std::swap(vec[i], vec[j]);
            ++i;
        }
    }
    std::swap(vec[i], vec[high]); // Ставим pivot на правильное место
    return i;
}

template <Sortable T, IndexableContainer Container> void quickSort(Container &vec, size_t low, size_t high) {
    if (low < high) {
        size_t pivotIndex = partition<T>(vec, low, high);

        // Рекурсивно сортируем левую и правую части
        if (pivotIndex > 0) { // Защита от underflow (size_t не может быть <0)
            quickSort<T>(vec, low, pivotIndex - 1);
        }
        quickSort<T>(vec, pivotIndex + 1, high);
    }
}

template <IndexableContainer Container>
requires Sortable<typename Container::value_type>
void sort(Container &vec) {
    if (!vec.empty()) {
        quickSort<typename Container::value_type>(vec, 0, vec.size() - 1);
    }
}

} // namespace rpt
