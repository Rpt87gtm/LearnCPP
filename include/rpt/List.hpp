#include <memory>
#include <stdexcept>

namespace rpt {

template <typename T> class List {
private:
    struct ListNode {
        T m_value;
        std::unique_ptr<ListNode> next;
        ListNode *prev;

        explicit ListNode(T value) : m_value(std::move(value)), prev(nullptr) {}
    };

public:
    using value_type = T;

    List() = default;

    List(std::initializer_list<T> init) {
        try {
            for (const auto &value: init) {
                pushBack(value);
            }
        } catch (...) {
            clear();
            throw;
        }
    }

    ~List() = default;

    void clear() {
        while (m_size > 0) {
            popBack();
        }
    }

    void pushBack(T value) {
        auto new_node = std::make_unique<ListNode>(std::move(value));
        auto *raw_ptr = new_node.get();

        if (m_size == 0) {
            head = std::move(new_node);
            tail = raw_ptr;
        } else {
            raw_ptr->prev = tail;
            tail->next    = std::move(new_node);
            tail          = raw_ptr;
        }
        m_size++;
    }

    void pushFront(T value) {
        auto new_node = std::make_unique<ListNode>(std::move(value));
        if (m_size == 0) {
            head = std::move(new_node);
            tail = head.get();
        } else {
            head->prev     = new_node.get();
            new_node->next = std::move(head);
            head           = std::move(new_node);
        }
        m_size++;
    }

    T popBack() {
        if (m_size == 0) {
            throw std::runtime_error("List is empty");
        }
        T value = std::move(tail->m_value);
        if (m_size == 1) {
            head.reset();
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next.reset();
        }
        m_size--;
        return value;
    }

    T popFront() {
        if (m_size == 0) {
            throw std::runtime_error("List is empty");
        }
        T value = std::move(head->m_value);
        if (m_size == 1) {
            head.reset();
            tail = nullptr;
        } else {
            std::unique_ptr<ListNode> old_head = std::move(head);
            head                               = std::move(old_head->next);
            head->prev                         = nullptr;
        }
        m_size--;
        return value;
    }

    [[nodiscard]] T &at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("List index out of range");
        }

        ListNode *current = head.get();
        for (size_t i = 0; i < index; ++i) {
            current = current->next.get();
        }

        return current->m_value;
    }

    [[nodiscard]] const T &at(size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("List index out of range");
        }

        ListNode *current = head.get();
        for (size_t i = 0; i < index; ++i) {
            current = current->next.get();
        }

        return current->m_value;
    }

    T &operator[](size_t index) { return at(index); }

    const T &operator[](size_t index) const { return at(index); }

    size_t size() const noexcept { return m_size; }

    bool empty() const noexcept { return m_size == 0; }

    class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T *;
        using reference         = T &;

        explicit Iterator(ListNode *node) : current(node) {}

        pointer *operator->() const noexcept { return &current->m_value; }

        reference &operator*() const noexcept { return current->m_value; }

        Iterator &operator++() noexcept {
            current = current->next.get();
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator &operator--() noexcept {
            current = current->prev;
            return *this;
        }

        Iterator operator--(int) noexcept {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const Iterator &other) const noexcept { return current == other.current; }

        bool operator!=(const Iterator &other) const noexcept { return !(*this == other); }

    private:
        ListNode *current = nullptr;
    };

    class ReverseIterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T *;
        using reference         = T &;

        explicit ReverseIterator(ListNode *node) : current(node) {}

        T *operator->() const noexcept { return &current->m_value; }

        T &operator*() const noexcept { return current->m_value; }

        ReverseIterator &operator++() noexcept {
            current = current->prev;
            return *this;
        }

        ReverseIterator operator++(int) noexcept {
            ReverseIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        ReverseIterator &operator--() noexcept {
            current = current ? current->next.get() : nullptr;
            return *this;
        }

        ReverseIterator operator--(int) noexcept {
            ReverseIterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const ReverseIterator &other) const noexcept { return current == other.current; }

        bool operator!=(const ReverseIterator &other) const noexcept { return current != other.current; }

    private:
        ListNode *current = nullptr;
    };

    Iterator begin() noexcept { return Iterator(head.get()); }

    Iterator end() noexcept { return Iterator(nullptr); }

    Iterator begin() const noexcept { return Iterator(head.get()); }

    Iterator end() const noexcept { return Iterator(nullptr); }

    ReverseIterator rbegin() noexcept { return ReverseIterator(tail); }

    ReverseIterator rend() noexcept { return ReverseIterator(nullptr); }

    ReverseIterator rbegin() const noexcept { return ReverseIterator(tail); }

    ReverseIterator rend() const noexcept { return ReverseIterator(nullptr); }

private:
    size_t m_size = 0;
    std::unique_ptr<ListNode> head;
    ListNode *tail = nullptr;
};

} // namespace rpt
