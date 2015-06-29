#include <vector>
#include <iostream>

using namespace std;

int solution (const vector<int>& a)
{
    int n = a.size(), want = 1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == want) {
            ++want;
        }
    }
    cout << want << endl;
    return n - want + 1;
}

int main()
{
    vector<int> a;
    a.push_back(1);
    a.push_back(3);
    a.push_back(5);
    a.push_back(6);
    a.push_back(2);
    a.push_back(7);
    a.push_back(4);
    cout << solution(a) << endl;
    return 0;
}
