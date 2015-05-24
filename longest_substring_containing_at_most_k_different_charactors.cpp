/*
Given a string of lowercase letters:

given: aabbaaddc

Find the longest substring that contains at most 2 different characters.

return: aabbaa

*/

// aabbaaddc
// |
// ||
// | |
// |  |
// ...
// |    |
// |     |
//  |    |
// ...
//      ad
//      ||

// ddcaabbaa
// |
// ||


#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

string longestSubstring(const string& s)
{
    string result;

    unordered_map<char, int> dict;
    int maxLength = 0;
    int numDiff   = 0;

    unsigned int left  = 0;
    unsigned int right = 0;

    while (right < s.size()) {
        // Extending the window

        unordered_map<char, int>::iterator jt = dict.find(s[right]);
        if (dict.end() != jt) {
            // This is a character we've seen before

            ++jt->second;
        } else {
            // This is a new character we've never seen before

            if (1 >= numDiff) {
                ++numDiff;
                dict.insert(make_pair(s[right], 1));
            } else {
                // Since there are already 2 different characters in the
                // window, now shrink the window.

                while (left <= right) {
                    unordered_map<char, int>::iterator it = dict.find(s[left]);
                    ++left;
                    --it->second;
                    if (0 == it->second) {
                        dict.erase(it);
                        --numDiff;
                        break;
                    }
                }
                continue;
            }
        }

        // Update the maximum length

        int length = right - left + 1;
        if (length > maxLength) {
            maxLength = length;
            result = s.substr(left, right - left + 1);
        }

        ++right;
    }

    return result;
}

int main()
{
    string result = longestSubstring("");
    assert("" == result);
    cout << "Test Case 1 done" << endl;

    result = longestSubstring("a");
    assert("a" == result);
    cout << "Test Case 2 done" << endl;

    result = longestSubstring("aa");
    assert("aa" == result);
    cout << "Test Case 3 done" << endl;

    result = longestSubstring("ab");
    assert("ab" == result);
    cout << "Test Case 4 done" << endl;

    result = longestSubstring("aab");
    assert("aab" == result);
    cout << "Test Case 5 done" << endl;

    result = longestSubstring("aabbaaddc");
    assert("aabbaa" == result);
    cout << "Test Case 6 done" << endl;

    result = longestSubstring("xyab");
    assert("xy" == result);
    cout << "Test Case 7 done" << endl;

    result = longestSubstring("abcdefghiihgjkl");
    assert("hiih" == result);
    cout << "Test Case 8 done" << endl;

    result = longestSubstring("aabbbbbabaaaccbbbbaab");
    assert("aabbbbbabaaa" == result);
    cout << "Test Case 9 done" << endl;

    return 0;
}
