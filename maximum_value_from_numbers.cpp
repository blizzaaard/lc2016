// 10 1 1 1
// 10 * (1 + 1 + 1) = 30
//
// 1 1 2 1
// (1 + 1) * (2 + 1) = 6

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maximumValue(const vector<int>& nums)
{
    int n = nums.size();
    if (0 == n) return 0;
    vector<vector<int> > opt(n, vector<int>(n, 0));
    opt[0][0] = nums[0];
    for (int j = 1; j < nums.size(); ++j) {
        opt[j][j] = nums[j];
        for (int i = j - 1; i >= 0; --i) {
            for (int k = i; k < j; ++k) {
                opt[i][j] = max(opt[i][j],
                                max(opt[i][k] * opt[k + 1][j],
                                    opt[i][k] + opt[k + 1][j]));
//                cout << "opt[" << i << "][" << j << "] = "
//                     << opt[i][j] << endl;
            }
        }
    }
    return opt[0][n - 1];
}

int main()
{
    {
        vector<int> nums;
        nums.push_back(10);
        nums.push_back(1);
        nums.push_back(1);
        nums.push_back(1);
        cout << maximumValue(nums) << endl;
    }
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(1);
        cout << maximumValue(nums) << endl;
    }

    return 0;
}
