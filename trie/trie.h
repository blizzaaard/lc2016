
#include <string>
#include <vector>

struct Node {

    int  m_value;
    bool m_hasValue;
    std::vector<Node *> m_next;

    explicit Node(int R)
    : m_value(0)
    , m_hasValue(false)
    , m_next(R, 0)
    {
    }
};

class Trie {

    int   m_radix;
    Node *m_root;

    Trie(int radix)
    : m_radix(radix)
    , m_root(0)
    {
    }

    void set(const std::string& key, int value)
    {
        int d = 0, len = key.size();
        Node **pp = &m_root;
        while (d <= len) {
            if (!*pp) *pp = new Node(m_radix);
            if (d == len) {
                (*pp)->m_hasValue = true;
                (*pp)->m_value    = value;
                return;
            }
            pp = &(*pp)->m_next[key[d]];
            ++d;
        }
    }
};

int main()
{
}
