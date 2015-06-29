#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>

using namespace std;

struct Pair {

    char d_char;
    int  d_count;
};

struct Comp {

    bool operator()(const Pair& lhs, const Pair& rhs) const
    {
        return lhs.d_count < rhs.d_count;
    }
};

class Solution {

  public:
    string rearrange(const string& str)
    {
        int index = 0;
        string result(str.size(), 0);

        unordered_map<char, int> hash;
        for (int i = 0; i < str.size(); ++i) {
            ++hash[str[i]];
        }

        priority_queue<Pair, vector<Pair>, Comp> maxHeap;

        for (unordered_map<char, int>::const_iterator it  = hash.begin();
                                                      it != hash.end();
                                                    ++it)
        {
            Pair p;
            p.d_char  = it->first;
            p.d_count = it->second;
            maxHeap.push(p);
        }

        while (!maxHeap.empty()) {
            Pair p1 = maxHeap.top();
            maxHeap.pop();

            if (maxHeap.empty()) {
                if (0 != index && result[index - 1] == p1.d_char) {
                    return "";
                } else {
                    result[index++] = p1.d_char;
                    return result;
                }
            }

            Pair p2 = maxHeap.top();
            maxHeap.pop();

            if (0 != index && result[index - 1] != p1.d_char) {
                result[index++] = p1.d_char;
                result[index++] = p2.d_char;
            } else {
                result[index++] = p2.d_char;
                result[index++] = p1.d_char;
            }

            --p1.d_count;
            --p2.d_count;

            if (0 < p1.d_count) maxHeap.push(p1);
            if (0 < p2.d_count) maxHeap.push(p2);
        }

        return result;
    }
};

int main()
{
    Solution s;

    cout << s.rearrange("aaabbbccc") << endl;
    cout << s.rearrange("aaabbbcccc") << endl;
    cout << s.rearrange("aaabbbccccc") << endl;
    cout << s.rearrange("aaabbbcccccc") << endl;
    cout << s.rearrange("aaabbbccccccc") << endl;
    cout << s.rearrange("aaabbbcccccccc") << endl;
    cout << s.rearrange("aaabbbccccccccc") << endl;
    cout << s.rearrange("aaabbbcccccccccc") << endl;
    cout << s.rearrange("aaaabbbcccccccccc") << endl;
    cout << s.rearrange("aaaaabbbcccccccccc") << endl;
    cout << s.rearrange("aaaaaabbbcccccccccc") << endl;
    cout << s.rearrange("aaaaaaabbbcccccccccc") << endl;

    return 0;
}
