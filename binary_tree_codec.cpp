// Serialization/Deserialization of a Binary Tree

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node {

    int   m_value;
    Node *m_left;
    Node *m_right;

    explicit Node(int value) : m_value(value), m_left(0), m_right(0)
    {
    }
};

string toString(int value)
{
    ostringstream oss;
    oss << value;
    return oss.str();
}

int toInt(const string& value)
{
    int result;
    istringstream iss(value);
    iss >> result;
    return result;
}

void print(Node *node)
{
    if (node) {
        print(node->m_left);
        cout << node->m_value << ' ';
        print(node->m_right);
    }
}

void encode(ostream& stream, Node *node)
{
    if (!node) {
        stream << "# ";
        return;
    }
    stream << (toString(node->m_value) + ' ');
    encode(stream, node->m_left);
    encode(stream, node->m_right);
}

Node *decode(istream& stream)
{
    string value;
    stream >> value;
    if (!stream) return 0;
    if ("#" == value) return 0;
    Node *node = new Node(toInt(value));
    node->m_left = decode(stream);
    node->m_right = decode(stream);
    return node;
}

int main()
{
    //     3
    //    / \
    //   1   5
    //  / \   \
    // 0   2  100

    Node *node0 = new Node(3);
    Node *node1 = new Node(1); Node *node2 = new Node(5);
    Node *node3 = new Node(0); Node *node4 = new Node(2);
    Node *node6 = new Node(100);
    node0->m_left = node1; node0->m_right = node2;
    node1->m_left = node3; node1->m_right = node4;
    node2->m_right = node6;

    print(node0); cout << endl;
    ostringstream oss;
    encode(oss, node0);
    cout << oss.str() << endl;

    istringstream iss(oss.str());
    print(decode(iss)); cout << endl;

    return 0;
}
