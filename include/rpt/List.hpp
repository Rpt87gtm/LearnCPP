#include <stdexcept>

namespace rpt {

template <typename T> struct ListNode {
public:
    ListNode(T value) : m_value(value) {}

    ~ListNode() {}

    ListNode *next;
    ListNode *prev;
    T m_value;
};

template <typename T> class List {
public:
    List() {}

    ~List() {
        while (m_size > 0) {
            popBack();
        }
    }

    void pushBack(T value) {
        auto *node = new ListNode<T>(value);

        if (m_size == 0) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;

            tail = node;
        }

        m_size++;
    }

    void popBack() {
        if (m_size == 0) {
            throw std::runtime_error("List is empty");
        }

        if (m_size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            auto node  = tail->prev;
            node->next = nullptr;
            delete tail;
            tail = node;
        }

        m_size--;
    }

    T at(size_t index) {
        if (index >= m_size) {
            throw std::runtime_error("Index out of bounds");
        }
        auto node = head;
        for (int i = 0; i < index; i++) {
            node = node->next;
        }

        return node->m_value;
    }

private:
    size_t m_size     = 0;
    ListNode<T> *head = nullptr;
    ListNode<T> *tail = nullptr;
};

} // namespace rpt
