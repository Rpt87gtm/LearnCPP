#include <memory>
#include <stdexcept>

namespace rpt {

template <typename T> class List {
public:
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

    size_t size() const noexcept { return m_size; }

private:
    struct ListNode {
        T m_value;
        std::unique_ptr<ListNode> next;
        ListNode *prev;

        explicit ListNode(T value) : m_value(std::move(value)), prev(nullptr) {}
    };

    size_t m_size = 0;
    std::unique_ptr<ListNode> head;
    ListNode *tail = nullptr;
};

} // namespace rpt
