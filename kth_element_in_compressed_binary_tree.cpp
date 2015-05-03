// 有一个binary directed acyclic graph， 每个node存有一个字符，有一个左节点和一
// 个右节点。
//
// Node {
//     Node L;
//     Node R;
//     char ch;
// };
//
// 这样如果in-order traverse这个DAG，就会得到一个string。例子如下：假设一个DAG
// 只有两个node，分别装着A和B这两个字符。假设Node A的左右两条边都指向Node B:
//
// A (root node)
// ||
// B
//
// 那么这个存储的string就是BAB
//
// 现在假设已经有了一个这样的DAG, 请写一个函数，返回这个string的第k个字符。要求
// 复杂度不能是exponential的。。。
//
// 我先写了个in order 的遍历。面试官就问我如果n个node,string最长可以是多少
// 我觉得是2^n-1
// 面试官说，那么traverse的话最坏情况复杂度就是O(2^n)，不符合要求～


#include <iostream>

using namespace std;

struct Node {

    char  m_value;
    Node *m_left;
    Node *m_right;
    int   m_count;

    explicit Node(int value)
    : m_value(value)
    , m_left(0)
    , m_right(0)
    , m_count(-1)
    {
    }
};

void print(Node *node)
{
    if (!node) return;
    print(node->m_left);
    cout << node->m_value << '(' << node->m_count << ')' << endl;
    print(node->m_right);
}

int populateCount(Node *node)
{
    if (!node) return 0;
    int leftCount  = populateCount(node->m_left);
    int rightCount = node->m_left == node->m_right ? leftCount
                   : populateCount(node->m_right);
    node->m_count = leftCount + rightCount + 1;
    return node->m_count;
}

Node *kthElement(Node* node, int k)
{
    if (!node) return 0;
    int leftCount = node->m_left ? node->m_left->m_count : 0;
    if (k == leftCount) return node;
    else if (k < leftCount) return kthElement(node->m_left, k);
    else return kthElement(node->m_right, k - leftCount - 1);
}

int main()
{
    Node node0('a'); Node node1('b'); Node node2('c'); Node node3('d');
    node0.m_left = &node1; node0.m_right = &node1;
    node1.m_left = &node2; node1.m_right = &node2;
    node2.m_left = &node3; node2.m_right = &node3;
    populateCount(&node0);
    print(&node0);
    for (int i = 0; i < 20; ++i) {
        Node *result = kthElement(&node0, i);
        if (result) cout << result->m_value << endl;
        else cout << "NULL" << endl;
    }
    return 0;
}
