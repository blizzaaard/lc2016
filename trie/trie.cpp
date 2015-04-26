
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void print(const std::vector< std::pair<std::string, int> >& result)
{
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i].first << "\t" << result[i].second << std::endl;
    }
    std::cout << std::endl;
}

struct Node {

    int  m_value;
    std::vector<Node *> m_next;

    explicit Node(int R)
    : m_value(-1)
    , m_next(R, 0)
    {
    }
};

class Trie {

    int   m_radix;
    Node *m_root;

    Node *getImp(const std::string& key) const
    {
        int index = 0, keyLen = key.size();
        Node *node = m_root;
        while (index <= keyLen) {
            if (!node) return 0;
            if (index == keyLen) return node;
            node = node->m_next[key[index]];
            ++index;
        }
        return 0;
    }

    void dump(std::vector< std::pair<std::string, int> > *result,
              const std::string&                          path,
              Node                                       *node) const
    {
        if (!node) return;
        if (-1 != node->m_value) {
            result->resize(result->size() + 1);
            result->back().first  = path;
            result->back().second = node->m_value;
        }
        for (char c = 0; c < node->m_next.size(); ++c) {
            if (node->m_next[c]) dump(result, path + c, node->m_next[c]);
        }
    }

  public:
    Trie(int radix)
    : m_radix(radix)
    , m_root(0)
    {
    }

    void set(const std::string& key, int value)
    {
        int index = 0, keyLen = key.size();
        Node **pp = &m_root;
        while (index <= keyLen) {
            if (!*pp) *pp = new Node(m_radix);
            if (index == keyLen) {
                (*pp)->m_value = value;
                return;
            }
            pp = &(*pp)->m_next[key[index]];
            ++index;
        }
    }

    int remove(const std::string& key)
    {
        int index = 0, keyLen = key.size();
        Node *node = m_root;
        std::stack< std::pair<Node *, char> > stack;
        while (index <= keyLen) {
            if (!node) return -1;
            if (index == keyLen) {
                // The key doesn't exist
                if (-1 == node->m_value) return -1;

                // Remove the node for the key

                node->m_value = -1;
                while (node) {
                    // Do not remove the node if it has an associated value

                    if (-1 != node->m_value) return 0;

                    // Do not remove the node if it has a child

                    bool hasChild = false;
                    for (int i = 0; i < node->m_next.size(); ++i) {
                        if (node->m_next[i]) {
                            hasChild = true;
                            break;
                        }
                    }
                    if (hasChild) return 0;

                    delete node;

                    if (stack.empty()) return 0;
                    std::pair<Node *, char> top = stack.top();
                    stack.pop();
                    node = top.first;
                    node->m_next[top.second] = 0;
                }
            }
            stack.push(std::make_pair(node, key[index]));
            node = node->m_next[key[index]];
            ++index;
        }
        return -1;
    }

    int get(const std::string& key) const
    {
        Node *node = getImp(key);
        return node && node->m_value >= 0 ? node->m_value : -1;
    }

    std::vector< std::pair<std::string, int> > dump() const
    {
        std::vector< std::pair<std::string, int> > result;
        std::string path;
        dump(&result, path, m_root);
        return result;
    }

    std::vector< std::pair<std::string, int> > dump(const std::string& prefix) const
    {
        Node *node = getImp(prefix);
        std::vector< std::pair<std::string, int> > result;
        std::string path(prefix);
        dump(&result, path, node);
        return result;
    }
};

int main()
{
    Trie trie(256);
    trie.set("she", 0);
    trie.set("sells", 1);
    trie.set("sea", 2);
    trie.set("shells", 3);
    trie.set("by", 4);
    trie.set("the", 5);
    trie.set("seashore", 6);

    trie.remove("shells");
    trie.remove("sells");

    print(trie.dump());

    print(trie.dump("s"));
    print(trie.dump("sz"));

    return 0;
}
