#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string toString(int value)
{
    ostringstream oss;
    oss << value;
    return oss.str();
}

string encode(const string& input)
{
    string result;
    if (input.empty()) return result;
    char prev = input[0];
    int count = 1;
    for (int i = 1; i < input.size(); ++i) {
        if (input[i] != prev) {
            result += prev;
            result += toString(count);
            prev  = input[i];
            count = 1;
        } else {
            ++count;
        }
    }
    result += prev;
    result += toString(count);
    return result;
}

string decode(const string& input)
{
    string result;
    if (input.empty()) return result;
    char prev  = 0;
    int  count = 0;
    for (int i = 0; i < input.size(); ++i) {
        if ('a' <= input[i] && input[i] <= 'z') {
            if (0 != count) result.append(count, prev);
            prev = input[i];
            count = 0;
        } else {
            count = count * 10 + input[i] - '0';
        }
    }
    if (0 != count) result.append(count, prev);
    return result;
}

int main()
{
    cout << encode("") << endl;
    cout << encode("a") << endl;
    cout << encode("ab") << endl;
    cout << encode("aab") << endl;
    cout << encode("abb") << endl;
    cout << encode("aabb") << endl;
    cout << encode("aabbbbbbbbbbbbccc") << endl;

    cout << decode("") << endl;
    cout << decode("a1") << endl;
    cout << decode("a1b1") << endl;
    cout << decode("a2b1") << endl;
    cout << decode("a1b2") << endl;
    cout << decode("a2b2") << endl;
    cout << decode("a2b12c3") << endl;

    return 0;
}
