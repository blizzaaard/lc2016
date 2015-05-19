#include <iostream>
#include <vector>

using namespace std;

struct Node {

    int   m_value;
    Node *m_left;
    Node *m_right;
};

Node *LCA(Node *node, Node *p, Node *q)
{
    if (!node) return 0;
    if (node == p || node == q) return node;
    Node* left  = LCA(node->m_left,  p, q);
    Node* right = LCA(node->m_right, p, q);
    if (left && right) return node;
    return left ? left : right;
}

int main()
{
    return 0;
}
