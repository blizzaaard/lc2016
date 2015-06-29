#include <cassert>
#include <queue>
#include <iostream>

using namespace std;

struct Node {

    Node *m_left;
    Node *m_right;
    int   m_value;

    explicit Node(int value)
    : m_left(0)
    , m_right(0)
    , m_value(value)
    {
    }
};

class Solution {

  public:
    Node *deepest(Node *root)
    {
        if (!root) return 0;

        queue<Node *> queue;
        queue.push(root);

        int numCurr = 1;
        int numNext = 0;

        while (!queue.empty()) {
            Node *node = queue.front();
            queue.pop();
            if (node->m_left) {
                queue.push(node->m_left);
                ++numNext;
            }
            if (node->m_right) {
                queue.push(node->m_right);
                ++numNext;
            }
            if (0 == --numCurr) {
                if (0 == numNext) return node;
                swap(numCurr, numNext);
            }
        }

        return root;
    }
};

int main()
{
    Solution s;

    {
        Node node0(0);
        Node node1(1), node2(2);
        Node node3(3), node4(4), node5(5), node6(6);
        node0.m_left = &node1; node0.m_right = &node2;
        node1.m_left = &node3; node1.m_right = &node4;
        node2.m_left = &node5;
        node5.m_left = &node6;

        assert(&node6 == s.deepest(&node0));
    }
    {
        Node node0(0);
        Node node1(1), node2(2);
        Node node3(3), node4(4), node5(5), node6(6);
        node0.m_left = &node1; node0.m_right = &node2;
        node1.m_left = &node3; node1.m_right = &node4;
        node2.m_left = &node5; node2.m_right = &node6;

        assert(&node6 == s.deepest(&node0));
    }
    {
        Node node0(0);
        Node node1(1), node2(2);
        Node node3(3), node4(4), node5(5), node6(6);
        node0.m_left  = &node1; node0.m_right = &node2;
        node1.m_left  = &node3;
        node3.m_right = &node4;
        node2.m_left  = &node5; node2.m_right = &node6;

        assert(&node4 == s.deepest(&node0));
    }

    return 0;
}
