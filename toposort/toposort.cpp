#include <list>
#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& result)
{
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
}

class Graph {

    // INSTANCE DATA
    vector< list<int> > m_adj;

    // PRIVATE METHODS
    bool toposortImp(vector<int> *result, vector<int>& state, int v)
    {
        if (1 == state[v]) {
            // cycle detected
            result->clear();
            return false;
        } else if (0 == state[v]) {
            state[v] = 1; // mark temp when visiting
            for (list<int>::iterator it  = m_adj[v].begin();
                                     it != m_adj[v].end();
                                   ++it)
            {
                if (!toposortImp(result, state, *it)) return false;
            }
            state[v] = 2;
            result->push_back(v);
        }
        return true;
    }

  public:
    // CREATORS
    Graph(int V)
    : m_adj(V)
    {
    }

    // PUBLIC METHODS
    void addEdge(int v, int w)
    {
        m_adj[v].push_back(w);
    }

    void toposort()
    {
        vector<int> result;

        vector<int> state(m_adj.size(), 0);
            // 0 - unmarked; 1 - temp marked; 2 - perm marked

        for (int v = 0; v < m_adj.size(); ++v) {
            if (0 == state[v]) {
                if (!toposortImp(&result, state, v)) {
                    cout << "cycle detected" << endl;
                    return;
                }
            }
        }
        print(result);
    }
};

int main()
{
    Graph g(13);

    g.addEdge(0, 1); g.addEdge(0, 5); g.addEdge(0, 6);
    g.addEdge(2, 0); g.addEdge(2, 3);
    g.addEdge(3, 5);
    g.addEdge(5, 4);
    g.addEdge(6, 4); g.addEdge(6, 9);
    g.addEdge(7, 6);
    g.addEdge(8, 7);
    g.addEdge(9, 10); g.addEdge(9, 11); g.addEdge(9, 12);
    g.addEdge(11, 12);
//    g.addEdge(10, 7);

    g.toposort();

    return 0;
}
