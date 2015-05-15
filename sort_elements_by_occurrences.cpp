#include <vector>

using namespace std;

struct Comp {

    bool operator<(const int lhs, const int rhs)
    {
    }
};

vector<int> sort(const vector<int>& nums)
{
    vector<int> result;
    priority_queue<int, vector<int>, Comp> heap
}
