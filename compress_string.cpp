#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Solution {

    string toString(int value)
    {
        ostringstream oss;
        oss << value;
        return oss.str();
    }

  public:
    string compress(const string& str)
    {
        string result;
        if (str.empty()) return result;
        int count = 1;
        for (int i = 1; i < str.size(); ++i) {
            if (str[i] == str[i - 1]) {
                ++count;
            } else {
                result += str[i - 1] + toString(count);
                count = 1;
            }
        }
        result += str[str.size() - 1] + toString(count);
        return result;
    }
};

int main()
{
    Solution s;

    cout << s.compress("aaabbcccc") << endl;
    cout << s.compress("a") << endl;

    return 0;
}
