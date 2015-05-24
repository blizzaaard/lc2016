#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void print(const vector<int>& result)
{
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << "^2";
        if (i != result.size() - 1)
            cout << '+';
    }
    cout << endl;
}

void helper(vector<int> *result, const vector<int>& trace, int n)
{
    if (0 == trace[n]) {
        int root = sqrt(n);
        result->push_back(root);
    } else {
        helper(result, trace, trace[n]);
        helper(result, trace, n - trace[n]);
    }
}

vector<int> square_number(int n)
{
    vector<int> trace(n + 1, 0);
        // 0 indicates this number is a square number

    vector<int> opt(n + 1, INT_MAX);
    opt[0] = 1;
    for (int i = 1; i <= n; ++i) {
        int root = sqrt(i);
        if (i == root * root) { // 'i' is a square number
            opt[i] = 1;
        } else { // 'i' is NOT a square number
            for (int k = 1; k <= i / 2; ++k) {
                if (opt[i] > opt[k] + opt[i - k]) {
                    opt[i] = opt[k] + opt[i - k];
                    trace[i] = k;
                }
            }
        }
    }

    // Generate the result from the trace vector

    vector<int> result;
    helper(&result, trace, n);

    return result;
}

int main()
{
    int A[] = { 52, 1, 0, 100, 1000, 8237, 300, 100, 8 };
    for (int i = 0; i < sizeof A / sizeof *A; ++i) {
        cout << A[i] << '=';
        print(square_number(A[i]));
        cout << endl;
    }
    return 0;
}
