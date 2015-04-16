#include <iostream>

#include <vector>
#include <list>

using namespace std;

class Graph {

    vector< list<int> > m_adj;

    void dfs(vector<int>& state, int v)
    {
        for (list<int>::iterator it  = m_adj[v].begin();
                                 it != m_adj[v].end();
                               ++it)
        {
            if (0 != state[*it]) continue;
            state[*it] = 1 == state[v] ? 2 : 1;
            dfs(state, *it);
        }
    }

  public:
    Graph(int V)
    : m_adj(V)
    {
    }

    void addEdge(int v, int u)
    {
        m_adj[v].push_back(u);
    }

    void bipartite()
    {
        vector<int> state(m_adj.size(), 0);
            // 0 - unmarked; 1 - red; 2 - black

        for (int v = 0; v < m_adj.size(); ++v) {
            if (0 == state[v]) {
                state[v] = 1;
                dfs(state, v);
            }
        }

        for (int v = 0; v < m_adj.size(); ++v) {
            if (1 == state[v]) cout << v << " ";
        }
        cout << endl;
        for (int v = 0; v < m_adj.size(); ++v) {
            if (2 == state[v]) cout << v << " ";
        }
        cout << endl;
    }
};

int main()
{
    Graph g(13);

    g.addEdge(0, 1); g.addEdge(1, 0);
    g.addEdge(0, 2); g.addEdge(2, 0);
    g.addEdge(0, 5); g.addEdge(5, 0);
    g.addEdge(0, 6); g.addEdge(6, 0);
    g.addEdge(1, 3); g.addEdge(3, 1);
    g.addEdge(3, 5); g.addEdge(5, 3);
    g.addEdge(4, 5); g.addEdge(5, 4);
    g.addEdge(4, 6); g.addEdge(6, 4);
    g.addEdge(6, 7); g.addEdge(7, 6);
    g.addEdge(7, 8); g.addEdge(8, 7);
    g.addEdge(8, 10); g.addEdge(10, 8);
    g.addEdge(9, 10); g.addEdge(10, 9);
    g.addEdge(9, 11); g.addEdge(11, 9);
    g.addEdge(10, 12); g.addEdge(12, 10);
    g.addEdge(11, 12); g.addEdge(12, 11);

    g.bipartite();

    return 0;
}
