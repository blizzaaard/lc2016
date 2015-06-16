#include <cassert>
#include <iostream>

using namespace std;

struct Node {

    Node *m_parent;
    Node *m_left;
    Node *m_right;
    int   m_value;

    explicit Node(int value)
    : m_parent(0)
    , m_left(0)
    , m_right(0)
    , m_value(value)
    {
    }
};

Node *predecessor(Node *node)
{
    if (!node) return 0;
    if (node->m_left) {
        node = node->m_left;
        while (node->m_right) {
            node = node->m_right;
        }
        return node;
    } else {
        Node *parent = node->m_parent;
        while (parent && parent->m_left == node) {
            node   = parent;
            parent = parent->m_parent;
        }
        return parent;
    }
}

Node *successor(Node *node)
{
    if (!node) return 0;
    if (node->m_right) {
        node = node->m_right;
        while (node->m_left) {
            node = node->m_left;
        }
        return node;
    } else {
        Node *parent = node->m_parent;
        while (parent && parent->m_right == node) {
            node   = parent;
            parent = parent->m_parent;
        }
        return parent;
    }
}

int main()
{
    Node node4(4);
    Node node2(2); Node node6(6);
    Node node1(1); Node node3(3);
    Node node5(5); Node node7(7);

    node4.m_left = &node2; node4.m_right = &node6;
    node2.m_left = &node1; node2.m_right = &node3;
    node6.m_left = &node5; node6.m_right = &node7;

    node2.m_parent = &node4; node6.m_parent = &node4;
    node1.m_parent = &node2; node3.m_parent = &node2;
    node5.m_parent = &node6; node7.m_parent = &node6;

    assert(&node2 == successor(&node1));
    assert(&node3 == successor(&node2));
    assert(&node4 == successor(&node3));
    assert(&node5 == successor(&node4));
    assert(&node6 == successor(&node5));
    assert(&node7 == successor(&node6));
    assert(0      == successor(&node7));

    assert(0      == predecessor(&node1));
    assert(&node1 == predecessor(&node2));
    assert(&node2 == predecessor(&node3));
    assert(&node3 == predecessor(&node4));
    assert(&node4 == predecessor(&node5));
    assert(&node5 == predecessor(&node6));
    assert(&node6 == predecessor(&node7));

    return 0;
}
