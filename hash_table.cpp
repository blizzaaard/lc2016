#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

struct Node {

    string m_key;
    int    m_value;

    explicit Node(const string& key, int value)
    : m_key(key)
    , m_value(value)
    {
    }
};

class NodeList {

    list<Node> m_list;

  public:
    explicit NodeList()
    {
    }

    void insert(const string& key, const int value)
    {
        for (list<Node>::iterator it  = m_list.begin();
                                  it != m_list.end();
                                ++it)
        {
            if (it->m_key == key) {
                it->m_value = value;
                return;
            }
        }

        m_list.push_back(Node(key, value));
    }

    int erase(const string& key)
    {
        for (list<Node>::iterator it  = m_list.begin();
                                  it != m_list.end();
                                ++it)
        {
            if (it->m_key == key) {
                m_list.erase(it);
                return 0;
            }
        }

        return -1;
    }

    int find(int *value, const string& key) const
    {
        for (list<Node>::const_iterator it  = m_list.begin();
                                        it != m_list.end();
                                      ++it)
        {
            if (it->m_key == key) {
                *value = it->m_value;
                return 0;
            }
        }

        return -1;
    }

    void dump() const
    {
        for (list<Node>::const_iterator it  = m_list.begin();
                                        it != m_list.end();
                                      ++it)
        {
            cout << it->m_key << '(' << it->m_value << ')' << "->";
        }
    }
};

class HashTable_SC {
    // Separate chaining hash table

    int              m_size;
    vector<NodeList> m_table;
    hash<string>     m_hasher;

  public:
    explicit HashTable_SC(const int size)
    : m_size(size)
    , m_table(size, NodeList())
    {
    }

    void insert(const string& key, const int value)
    {
        int pos = m_hasher(key) % m_size;
        m_table[pos].insert(key, value);
    }

    int erase(const string& key)
    {
        int pos = m_hasher(key) % m_size;
        return m_table[pos].erase(key);
    }

    int find(int *value, const string& key) const
    {
        int pos = m_hasher(key) % m_size;
        return m_table[pos].find(value, key);
    }

    void dump() const
    {
        for (int i = 0; i < m_table.size(); ++i) {
            m_table[i].dump();
            cout << endl;
        }
    }
};

class HashTable_LP {
    // Linear probing hash table

    int            m_count;
    vector<Node *> m_table;
    hash<string>   m_hasher;

    void resize(int size)
    {
        cout << "resizing from " << m_table.size()
             << " to " << size << endl;

        // Rehashing

        HashTable_LP ht(size);
        for (int i = 0; i < m_table.size(); ++i) {
            if (m_table[i]) {
                ht.insert(m_table[i]->m_key, m_table[i]->m_value);
            }
        }

        // Exchange the new hash table with the old one

        swap(m_count, ht.m_count);
        swap(m_table, ht.m_table);
        swap(m_hasher, ht.m_hasher);
    }

  public:
    explicit HashTable_LP(const int size)
    : m_count(0)
    , m_table(size, 0)
    {
    }

    void insert(const string& key, const int value)
    {
        // Resize the hash table if necessary

        if (m_count >= m_table.size() / 2) {
            resize(m_table.size() * 2);
        }

        int i = m_hasher(key) % m_table.size();
        while (m_table[i]) {
            if (m_table[i]->m_key == key) {
                m_table[i]->m_value = value;
                ++m_count;
                return;
            }
            i = (i + 1) % m_table.size();
        }
        m_table[i] = new Node(key, value);
        ++m_count;
    }

    int erase(const string& key)
    {
        // Resize the hash table if necessary

        if (m_count <= m_table.size() / 4) {
            resize(m_table.size() / 2);
        }

        int i = m_hasher(key) % m_table.size();
        while (m_table[i]) {
            if (m_table[i]->m_key == key) {
                delete m_table[i];
                m_table[i] = 0;
                --m_count;
                return 0;
            }
            i = (i + 1) % m_table.size();
        }
        return -1;
    }

    int find(int *value, const string& key) const
    {
        int i = m_hasher(key) % m_table.size();
        while (m_table[i]) {
            if (m_table[i]->m_key == key) {
                *value = m_table[i]->m_value;
                return 0;
            }
            i = (i + 1) % m_table.size();
        }
        return -1;
    }

    void dump() const
    {
        cout << "size = " << m_table.size() << endl;
        for (int i = 0; i < m_table.size(); ++i) {
            if (m_table[i]) {
                cout << '\t'
                     << m_table[i]->m_key
                     << '('
                     << m_table[i]->m_value
                     << ')'
                     << endl;
            }
        }
    }
};

int main()
{
    HashTable_LP ht(1);
    ht.insert("abc", 123);
    ht.insert("def", 123);
    ht.insert("abc", 456);
    ht.insert("ghi", 789);
    ht.insert("jkl", 111);
    ht.insert("mno", 111);
    ht.dump();
    cout << ht.erase("abc") << endl;
    cout << ht.erase("xyz") << endl;
    ht.dump();
    {
        int value = -1;
        ht.find(&value, "abc");
        cout << value << endl;
    }
    {
        int value = -1;
        ht.find(&value, "jkl");
        cout << value << endl;
    }
    /*
    {
        HashTable_SC ht(1);
        ht.insert("abc", 123);
        ht.insert("def", 123);
        ht.insert("abc", 456);
        ht.insert("ghi", 789);
        ht.insert("jkl", 111);
        ht.dump();
        cout << ht.erase("abc") << endl;
        cout << ht.erase("xyz") << endl;
        ht.dump();
        {
            int value = -1;
            ht.find(&value, "abc");
            cout << value << endl;
        }
        {
            int value = -1;
            ht.find(&value, "jkl");
            cout << value << endl;
        }
    }
    */
    return 0;
}
