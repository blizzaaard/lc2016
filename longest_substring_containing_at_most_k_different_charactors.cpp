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

#include <iostream>

#include <unordered_map>
#include <string>
#include <cassert>

using namespace std;

// To execute C++, please define "int main()"

string longestSubstringLength(const string& s)
{
  unordered_map<char, int> dict;
  unsigned int left = 0;
  int maxLength = 0;
  int numDiff = 0;

  string result;

  for (unsigned int right = 0; right < s.size(); ++right) {
    unordered_map<char, int>::iterator jt = dict.find(s[right]);
    if (dict.end() == jt) {
      // extending the window
      if (1 >= numDiff) {
        numDiff++;
        dict.insert(make_pair(s[right], 1));
        int length = right - left + 1;
        if (length > maxLength) {
          maxLength = length;
          result = s.substr(left, right - left + 1);
        }
      } else {
          --right;
        // shrinking the window
        while (left <= right) {
          unordered_map<char, int>::iterator it =
            dict.find(s[left]);
          ++left;
          --it->second;
          if (0 == it->second) {
            dict.erase(it);
            --numDiff;
            break;
          }
        }
      }
    } else {
      // same char as previous
      ++jt->second;
      int length = right - left + 1;
      if (length > maxLength) {
        maxLength = length;
        result = s.substr(left, right - left + 1);
      }
    }
  }
    
  return result;
}

int main() {
  
  
  string result = longestSubstringLength("");
  assert("" == result);
  cout << "Test Case 1 done" << endl;
  
  result = longestSubstringLength("a");
  assert("a" == result);
  cout << "Test Case 2 done" << endl;
  
  result = longestSubstringLength("aa");
  assert("aa" == result);
  cout << "Test Case 3 done" << endl;
  
  result = longestSubstringLength("ab");
  assert("ab" == result);
  cout << "Test Case 4 done" << endl;
  
  result = longestSubstringLength("aab");
  assert("aab" == result);
  cout << "Test Case 5 done" << endl;
  
  result = longestSubstringLength("aabbaaddc");
  assert("aabbaa" == result);
  cout << "Test Case 6 done" << endl;

  result = longestSubstringLength("xyab");
  assert("xy" == result);
  cout << "Test Case 7 done" << endl;

  result = longestSubstringLength("abcdefghiihgjkl");
  assert("hiih" == result);
  cout << "Test Case 8 done" << endl;

  result = longestSubstringLength("aabbbbbabaaaccbbbbaab");
  assert("aabbbbbabaaa" == result);
  cout << "Test Case 9 done" << endl;

  return 0;
}

// abcdefghiihgjkl (hiih)
// aabbbbbabaaaccbbbbaab (aabbbbbabaaa)
