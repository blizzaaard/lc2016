#include <cassert>
#include <list>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {

    string    m_label;
    list<int> m_adj;

    explicit Node(const string& label)
    : m_label(label)
    {
    }
};

class Graph {

    unordered_map<string, int> m_ids;
    vector<Node>               m_nodes;

    void dumpImp(vector<int>& visited, int id) const
    {
        cout << label(id) << '(' << id << ')' << endl;
        if (1 == visited[id]) {
            cout << "Cycle detected\t" << endl;
        } else if (0 == visited[id]) {
            visited[id] = 1; // mark as visiting
            for (list<int>::const_iterator
                        it  = m_nodes[id].m_adj.begin();
                        it != m_nodes[id].m_adj.end();
                      ++it)
            {
                dumpImp(visited, *it);
            }
            visited[id] = 2; // mark as visited
        }
    }

  public:
    void addEdge(const string& node1, const string& node2)
    {
        if (-1 == id(node1)) {
            m_ids.insert(make_pair(node1, m_nodes.size()));
            m_nodes.push_back(Node(node1));
        }
        if (-1 == id(node2)) {
            m_ids.insert(make_pair(node2, m_nodes.size()));
            m_nodes.push_back(Node(node2));
        }
        m_nodes[id(node1)].m_adj.push_back(id(node2));
    }

    void dump() const
    {
        vector<int> visited(m_nodes.size(), 0);
        for (int i = 0; i < m_nodes.size(); ++i) {
            if (0 == visited[i]) dumpImp(visited, i);
        }
    }

    void debug() const
    {
        for (int i = 0; i < m_nodes.size(); ++i) {
            cout << label(i) << '(' << i << ')' << '\t';
            for (list<int>::const_iterator
                        it  = m_nodes[i].m_adj.begin();
                        it != m_nodes[i].m_adj.end();
                      ++it)
            {
                cout << label(*it) << '(' << *it << ')' << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

    int id(const string& label) const
    {
        unordered_map<string, int>::const_iterator it = m_ids.find(label);
        if (it == m_ids.end()) {
            return -1;
        }
        return it->second;
    }

    const string& label(int id) const
    {
        assert(id < m_nodes.size());
        return m_nodes[id].m_label;
    }
};

int main()
{
    Graph g;

    g.addEdge("abc", "def");
    g.addEdge("def", "ghi");
    g.addEdge("ghi", "jkl");
    g.dump();

    return 0;
}
