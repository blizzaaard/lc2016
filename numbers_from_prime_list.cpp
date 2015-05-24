// Generate numbers from a list of primes

#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& result)
{
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << ' ';
    }
    cout << endl;
}

void helper(vector<int>&       result,
            int                value,
            const vector<int>& primes,
            int                index)
{
    if (index == primes.size()) return;
    for (int i = index; i < primes.size(); ++i) {
        if (i == index || primes[i] != primes[i - 1]) { // to avoid duplicates
            result.push_back(value * primes[i]);
            helper(result, value * primes[i], primes, i + 1);
        }
    }
}

vector<int> generate(vector<int>& primes)
{
    vector<int> result;
    sort(primes.begin(), primes.end());
    helper(result, 1, primes, 0);
    return result;
}

int main()
{
    {
        vector<int> primes;
        primes.push_back(2);
        primes.push_back(2);
        print(generate(primes));
    }
    {
        vector<int> primes;
        primes.push_back(2);
        primes.push_back(3);
        primes.push_back(5);
        primes.push_back(7);
        primes.push_back(11);
        primes.push_back(13);
        print(generate(primes));
    }
    return 0;
}
