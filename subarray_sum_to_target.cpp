// Contigious Subarray Sum
//
// Given a Array A and a integer K , find if there exist a subarray of A whose
// sum = K


#include <iostream>
#include <vector>

using namespace std;

void print(const pair<int, int>& result)
{
    cout << result.first << ' ' << result.second << endl;
}

pair<int, int> hasSum(const vector<int>& nums, int target)
{
    int n = nums.size();
    if (0 == n) return make_pair(-1, -1);
    int i = 0, j = 0, sum = nums[0];
    while (i < n) {
        while (j < n) {
            if (sum == target) return make_pair(i, j);
            else if (sum > target) sum -= nums[i++];
            else sum += nums[++j];
        }
    }
    return make_pair(-1, -1);
}

int main()
{
    {
        vector<int> nums;
        nums.push_back(23);
        print(hasSum(nums, 23));
    }
    {
        vector<int> nums;
        nums.push_back(24);
        nums.push_back(23);
        print(hasSum(nums, 23));
    }
    {
        vector<int> nums;
        nums.push_back(24);
        nums.push_back(2);
        nums.push_back(4);
        nums.push_back(8);
        nums.push_back(9);
        print(hasSum(nums, 23));
    }
    {
        vector<int> nums;
        nums.push_back(15);
        nums.push_back(2);
        nums.push_back(4);
        nums.push_back(8);
        nums.push_back(9);
        nums.push_back(5);
        nums.push_back(10);
        nums.push_back(23);
        print(hasSum(nums, 23));
    }
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(24);
        nums.push_back(4);
        nums.push_back(7);
        nums.push_back(9);
        nums.push_back(45);
        print(hasSum(nums, 16));
    }
    return 0;
}
