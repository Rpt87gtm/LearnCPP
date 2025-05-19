#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <rpt/List.hpp>
#include <rpt/trees/tree.hpp>
#include <string>

TEST_CASE("print tree2", "[Tree]") {
    rpt::BinaryTree<int> tree;

    tree.insert(5);
    tree.insert(2);
    tree.insert(9);
    tree.insert(5);
    tree.insert(1);
    tree.insert(4);

    tree.insert(12);
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(6);
    tree.insert(8);
    tree.insert(6);

    tree.insert(-1);
    tree.insert(-1);

    tree.insert(-21);

    tree.print();
}

TEST_CASE("bread travel", "[Tree]") {
    rpt::BinaryTree<int> tree;

    class Sumer {
        int m_sum = 0;

    public:
        explicit Sumer() = default;

        void add(int value) { m_sum += value; }

        int get() const { return m_sum; }
    };

    tree.insert(1);

    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    Sumer sum;

    tree.breadthTraversal([&sum](const int &value) { sum.add(value); });

    REQUIRE(sum.get() == 21);
}
