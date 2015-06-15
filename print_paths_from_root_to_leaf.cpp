#include <iostream>
#include <vector>

using namespace std;

struct Node {

    Node *m_left;
    Node *m_right;
    int   m_value;

    explicit Node(int value)
    : m_value(value)
    , m_left(0)
    , m_right(0)
    {
    }
};

void print(const vector<int>& path)
{
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << endl;
}

void helper(Node *node, vector<int>& path)
{
    if (!node) return;

    path.push_back(node->m_value);
    if (!node->m_left && !node->m_right) {
        print(path);
    } else {
        helper(node->m_left,  path);
        helper(node->m_right, path);
    }
    path.pop_back();
}

void printPaths(Node *node)
{
    vector<int> path;
    helper(node, path);
}

int main()
{
    //    1
    //   / \
    //  2   3
    //     /
    //    4
    //     \
    //      5
    Node node1(1); Node node2(2); Node node3(3);
    Node node4(4); Node node5(5);

    node1.m_left = &node2; node1.m_right = &node3;
    node3.m_left = &node4; node4.m_right = &node5;

    printPaths(&node1);
    return 0;
}
