// Maximum sum such that no two elements are adjacent
//
// Given an array of positive numbers, find the maximum sum of a subsequence
// with the constraint that no 2 numbers in the sequence should be adjacent in
// the array. So 3 2 7 10 should return 13 (sum of 3 and 10) or 3 2 5 10 7
// should return 15 (sum of 3, 5 and 7). Answer the question in most efficient
// way.


#include <iostream>
#include <vector>

using namespace std;

int maximumSum(const vector<int>& nums)
{
    int n = nums.size();
    if (0 == n) return 0;

    vector<int> opt(n, 0);
    opt[0] = nums[0];
    opt[1] = nums[0] > nums[1] ? nums[0] : nums[1];

    if (n < 3) return opt[n - 1];

    for (int i = 2; i < n; ++i) {
        opt[i] = max(nums[i], max(nums[i] + opt[i - 2], opt[i - 1]));
    }
    return opt[n - 1];
}

int main()
{
    {
        vector<int> nums;
        nums.push_back(5);
        nums.push_back(5);
        nums.push_back(10);
        nums.push_back(40);
        nums.push_back(50);
        nums.push_back(35);
        cout << maximumSum(nums) << endl;
    }
    {
        vector<int> nums;
        nums.push_back(3);
        nums.push_back(2);
        nums.push_back(7);
        nums.push_back(10);
        cout << maximumSum(nums) << endl;
    }
    {
        vector<int> nums;
        nums.push_back(3);
        nums.push_back(2);
        nums.push_back(5);
        nums.push_back(10);
        nums.push_back(7);
        cout << maximumSum(nums) << endl;
    }

    return 0;
}
