#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& seq)
{
    for (int i = 0; i < seq.size(); ++i) {
        cout << seq[i] << ' ';
    }
    cout << endl;
}

vector<int> generateReverseFibonacci(int first, int second)
{
    vector<int> result;

    if (first < 0 || second < 0) {
        return result;
    }
    result.push_back(first);
    result.push_back(second);

    while (second > 0) {
        int next = first - second;
        first = second;
        second = next;
        if (second >= 0) {
            result.push_back(second);
        }
    }
    return result;
}

int main()
{
    {
        // result = NULL
        // return empty vector when the second number is negative
        vector<int> result = generateReverseFibonacci(1, -1);
        assert(result.empty());
    }
    {
        // result = NULL
        // return empty vector when the first number is negative
        vector<int> result = generateReverseFibonacci(-1, 1);
        assert(result.empty());
    }
    {
        // result = 0 0
        // return empty vector when the first and the second number are
        // negative
        vector<int> result = generateReverseFibonacci(-1, -1);
        assert(result.empty());
    }
    {
        // result = 0 0
        // stop when the second number is 0
        vector<int> result = generateReverseFibonacci(0, 0);
        assert(2 == result.size());
    }
    {
        vector<int> result = generateReverseFibonacci(1, 0);
        // result = 1 0
        // stop when the second number is 0
        assert(2 == result.size());
    }
    {
        vector<int> result = generateReverseFibonacci(0, 1);
        // result = 0 1
        // stop when the second number is smaller than the first one
        assert(2 == result.size());
    }
    {
        // result = 80 50 30 20 10 10 0
        vector<int> result = generateReverseFibonacci(80, 50);
        assert(7 == result.size());
    }
    {
        // result = 80 30 50
        // stop when the second number is smaller than the first one
        vector<int> result = generateReverseFibonacci(80, 30);
        assert(3 == result.size());
    }
    return 0;
}
