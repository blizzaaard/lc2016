// insert/remove a node into/from a binary search tree

#include <iostream>

using namespace std;

struct Node {

    int   m_value;
    Node *m_left;
    Node *m_right;

    explicit Node(int value)
    : m_value(value)
    , m_left(0)
    , m_right(0)
    {
    }
};

void print(Node *node)
{
    if (!node) return;
    print(node->m_left);
    cout << node->m_value << ' ';
    print(node->m_right);
}

Node *min(Node *node)
    // Get the min node in the tree rooted at the specified 'node'.
{
    if (!node) return 0;
    if (!node->m_left) return node;
    return min(node->m_left);
}

Node *removeMin(Node *node)
    // Remove the min node from the tree rooted at the specified 'node' and
    // return the root of the tree.
    //
    // NOTE: do NOT free the min node since we just want to transplant the min
    // node.
{
    if (!node) return 0;
    if (!node->m_left) return node->m_right;
    node->m_left = removeMin(node->m_left);
    return node;
}

Node *remove(Node *node, int value)
{
    if (!node) return 0;
    if (value < node->m_value) {
        node->m_left = remove(node->m_left, value);
    } else if (value > node->m_value) {
        node->m_right = remove(node->m_right, value);
    } else {
        if (!node->m_left) return node->m_right;
        if (!node->m_right) return node->m_left;
        Node *temp = node;
        node = min(node->m_right);
        node->m_right = removeMin(temp->m_right);
        node->m_left = temp->m_left;
        delete temp;
    }
    return node;
}

Node *insert(Node *node, int value)
{
    if (!node) return new Node(value);
    if (value < node->m_value) return insert(node->m_left, value);
    else if (value > node->m_value) return insert(node->m_right, value);
    return node;
}

int main()
{
    Node *node0 = new Node(3);
    Node *node1 = new Node(1); Node *node2 = new Node(5);
    Node *node3 = new Node(0); Node *node4 = new Node(2);
    Node *node5 = new Node(4); Node *node6 = new Node(6);
    Node *node7 = new Node(7);
    node0->m_left = node1; node0->m_right = node2;
    node1->m_left = node3; node1->m_right = node4;
    node2->m_left = node5; node2->m_right = node6;
    node6->m_left = node7;

    print(node0); cout << endl;

    print(remove(node0, 6)); cout << endl;
    print(remove(node0, 1)); cout << endl;
    print(remove(node0, 0)); cout << endl;
    print(remove(node0, 3)); cout << endl;

    return 0;
}
