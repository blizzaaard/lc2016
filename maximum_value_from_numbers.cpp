#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maximumValue(const vector<int>& nums)
{
    int n = nums.size();
    if (0 == n) return 0;
    else if (1 == n) return nums[0];
    vector<int> opt(n, 0);
    opt[0] = nums[0];
    opt[1] = max(nums[0] + nums[1], nums[0] * nums[1]);
    for (int i = 2; i < nums.size(); ++i) {
        opt[i] = max(nums[i] * opt[i - 1],
                     max(nums[i] + opt[i - 1],
                         max((nums[i] * nums[i - 1]) + opt[i - 2],
                             (nums[i] + nums[i - 1]) * opt[i - 2])));
    }
    return opt[n - 1];
}

int main()
{
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(1);
    cout << maximumValue(nums) << endl;

    return 0;
}
