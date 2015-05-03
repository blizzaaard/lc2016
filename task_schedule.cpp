// [1,2,1,2], N=3
//
// 1 2 1 2     --> 4
// 1 2 _ _ 1 2 --> 6

// [1,2,1,2], N=2
//
// 1, 2, 1, 2    --> 4
// 1, 2, _, 1, 2 --> 5

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void print(const vector<int>& tasks)
{
    for (int i = 0; i < tasks.size(); ++i) {
        cout << tasks[i] << ' ';
    }
    cout << endl;
}

// 1 2 1 2
//
// 1 2 _ _ 1 2

int schedule(const vector<int>& tasks, int n)
{
    vector<int> result;
    unordered_map<int, int> dict;
    for (int i = 0; i < tasks.size(); ++i) {
        unordered_map<int, int>::iterator it = dict.find(tasks[i]);
        if (dict.end() != it) {
            int j = it->second + n + 1;
            while (result.size() < j) result.push_back('_');
        }
        result.push_back(tasks[i]);
        dict.insert(make_pair(tasks[i], i));
    }
    print(result);
    return result.size();
}

int main()
{
    {
        vector<int> tasks;
        tasks.push_back(1);
        tasks.push_back(2);
        tasks.push_back(1);
        tasks.push_back(2);
        cout << schedule(tasks, 3) << endl;
    }
    {
        vector<int> tasks;
        tasks.push_back(1);
        tasks.push_back(2);
        tasks.push_back(1);
        tasks.push_back(2);
        cout << schedule(tasks, 2) << endl;
    }
    {
        vector<int> tasks;
        tasks.push_back(1);
        cout << schedule(tasks, 4) << endl;
    }

    return 0;
}
