#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

void print(const vector<string>& result)
{
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << ' ';
    }
    cout << endl;
}

void helper(vector<string>& result, vector<int>& hash, const string& palindrome)
{
    bool empty = true;
    for (int i = 0; i < 256; ++i) {
        if (0 != hash[i]) {
            hash[i] -= 2;
            helper(result, hash, static_cast<char>(i)
                               + palindrome
                               + static_cast<char>(i));
            hash[i] += 2;
            empty = false;
        }
    }
    if (empty) {
        // The hash is of all zeros which means that there's no more charactor
        // needs to be added to the palindrome

        result.push_back(palindrome);
    }
}

vector<string> makePalindrome(const string& str)
{
    vector<string> result;

    // Construct the dict mapping each charactor to its number of occurrences

    vector<int> hash(256, 0);
    for (int i = 0; i < str.size(); ++i) {
        ++hash[str[i]];
    }

    // Check if there's at most one charactor that occurs odd times

    int index = -1;
    for (int i = 0; i < 256; ++i) {
        if (hash[i] % 2) {
            if (-1 != index) return result;
            index = i;
        }
    }

    if (-1 != index) {
        // There is the centric charactor
        hash[index] = 0;
        helper(result, hash, string(1, static_cast<char>(index)));
    } else {
        // There is no centric charactor
        helper(result, hash, "");
    }

    return result;
}

int main()
{
    print(makePalindrome("abc"));
    print(makePalindrome("aab"));
    print(makePalindrome("carecra"));
    print(makePalindrome("aabbcc"));
    return 0;
}
