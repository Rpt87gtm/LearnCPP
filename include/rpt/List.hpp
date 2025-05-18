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

    List(std::initializer_list<T> init) {
        for (auto value: init) {
            pushBack(value);
        }
    }

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

    void pushFront(T value) {
        auto *node = new ListNode<T>(value);

        if (m_size == 0) {
            head = node;
            tail = node;
        } else {
            head->prev = node;
            node->next = head;

            head = node;
        }

        m_size++;
    }

    T popBack() {
        if (m_size == 0) {
            throw std::runtime_error("List is empty");
        }
        T value = tail->m_value;

        if (m_size == 1) {
            delete tail;
            head = nullptr;
            tail = nullptr;
        } else {
            auto node  = tail->prev;
            node->next = nullptr;
            delete tail;
            tail = node;
        }

        m_size--;
        return value;
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
