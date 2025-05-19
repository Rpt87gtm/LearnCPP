#pragma once
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <queue>

namespace rpt {

template <typename T> class BinaryTree {
protected:
    struct TreeNode {
        explicit TreeNode(T data) : data(data) {}

        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;

        T data;
    };

private:
    std::unique_ptr<TreeNode> root;
    std::function<bool(const T &, const T &)> comparator;

    void insert(TreeNode *node, T value) {
        if (comparator(value, node->data)) {
            if (!node->left) {
                node->left = std::make_unique<TreeNode>(value);
            } else {
                insert(node->left.get(), value);
            }
        } else {
            if (!node->right) {
                node->right = std::make_unique<TreeNode>(value);
            } else {
                insert(node->right.get(), value);
            }
        }
    }

public:
    BinaryTree(std::function<bool(const T &, const T &)> comp = std::less<T>{}) : comparator(comp) {}

    BinaryTree(const BinaryTree &) = delete;

    BinaryTree(BinaryTree &&) noexcept = default;

    BinaryTree &operator=(const BinaryTree &) = delete;

    BinaryTree &operator=(BinaryTree &&) noexcept = default;

    ~BinaryTree() = default;

    void insert(T value) {
        if (!root) {
            root = std::make_unique<TreeNode>(value);
        } else {
            insert(root.get(), value);
        }
    }

    void breadthTraversal(std::function<void(const T &)> action) {
        if (!root) {
            return;
        }
        std::queue<TreeNode *> queue;

        queue.push(root.get());

        while (!queue.empty()) {
            TreeNode *current = queue.front();
            queue.pop();

            if (current->left) {
                queue.push(current->left.get());
            }
            if (current->right) {
                queue.push(current->right.get());
            }
            action(current->data);
        }
    };

    void levelBreadthTraversal(std::function<void(const T &)> action, std::function<void(int)> levelAction) {
        int level = 0;
        std::list<TreeNode *> current;
        std::list<TreeNode *> next;

        current.push_back(root.get());

        while (!current.empty()) {
            for (auto node: current) {

                if (node->left) {
                    next.push_back(node->left.get());
                }
                if (node->right) {
                    next.push_back(node->right.get());
                }
                action(node->data);
            }

            levelAction(level);
            current.clear();
            std::swap(current, next);
            level++;
        }
    }

    void levelBreadthTraversal(
      std::function<void(const T &)> nodeAction, std::function<void(int)> levelAction,
      std::function<void()> emptyAction) {

        int level = 0;
        std::queue<TreeNode *> current;
        std::queue<TreeNode *> next;

        current.push(root.get());

        while (!current.empty()) {
            bool levelHasNodes = false;

            while (!current.empty()) {
                TreeNode *node = current.front();
                current.pop();

                if (!node) {
                    emptyAction();
                    next.push(nullptr);
                    next.push(nullptr);
                    continue;
                }

                // Обрабатываем текущий узел
                nodeAction(node->data);
                levelHasNodes = true;

                // Добавляем потомков (даже если nullptr)
                next.push(node->left.get());
                next.push(node->right.get());
            }

            if (levelHasNodes) {
                levelAction(level);
                level++;
            } else {
                break;
            }

            std::swap(current, next);
        }
    }

    void print() {
        levelBreadthTraversal(
          [](const T &value) { std::cout << value << " "; },
          [](int level) { std::cout << "\n"; },
          []() { std::cout << "* "; });
    }
};

} // namespace rpt