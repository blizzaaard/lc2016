#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(const string& str, int start, int end)
{
    while (start < end) {
        if (str[start] != str[end]) return false;
        ++start;
        --end;
    }
    return true;
}

string makePalindrome(const string& str)
{
    string result(str);

    int n = str.size();
    if (n < 2) return str;

    int i = 0;
    for (; i < n; ++i) {
        if (isPalindrome(str, i, n - 1)) break;
    }

    for (int j = i - 1; j >= 0; --j) {
        result.push_back(str[j]);
    }

    return result;
}

int main()
{
    cout << makePalindrome("ab") << endl;
    cout << makePalindrome("aba") << endl;
    cout << makePalindrome("abab") << endl;
    cout << makePalindrome("cat") << endl;
    cout << makePalindrome("baloo") << endl;
    cout << makePalindrome("banana") << endl;
    return 0;
}
