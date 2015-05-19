#include <iostream>
#include <vector>

using namespace std;

void print(const std::vector<int>& result)
{
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << ' ';
    }
    cout << endl;
}

int next(int prefix, int n, int suffix)
{
    int digit = 1;
    while (n / digit >= 10) {
        digit *= 10;
    }
    return (prefix * digit * 10 + n) * 10 + suffix;
}

vector<int> generate(int n)
{
    vector<int> result;
    if (n % 2) { // odd
        result.push_back(0);
        result.push_back(1);
        result.push_back(8);
        if (1 == n) return result;
    } else { // even
        result.push_back(11);
        result.push_back(88);
        result.push_back(69);
        result.push_back(96);
        if (2 == n) return result;
    }

    for (int i = 1; i < n; i += 2) {
        int size = result.size();
        for (int j = 0; j < size; ++j) {
            result.push_back(next(1, result[j], 1));
            result.push_back(next(8, result[j], 8));
            result.push_back(next(6, result[j], 9));
            result.push_back(next(9, result[j], 6));
        }
        result.erase(result.begin(), result.begin() + size);
    }

    return result;
}

int main()
{
    print(generate(1));
    print(generate(2));
    print(generate(3));
    print(generate(4));
    return 0;
}
