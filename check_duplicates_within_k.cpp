#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

bool checkDupWithinK(const vector<int>& nums, int k)
{
    unordered_set<int> set;
    for (int i = 0; i < nums.size(); ++i) {
        if (set.count(nums[i])) return true;
        set.insert(nums[i]);
        if (i >= k) set.erase(nums[i - k]);
    }
    return false;
}

int main()
{
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.push_back(4);
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.push_back(4);
        cout << checkDupWithinK(nums, 3) << endl;
    }
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.push_back(1);
        nums.push_back(4);
        nums.push_back(5);
        cout << checkDupWithinK(nums, 3) << endl;
    }
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.push_back(4);
        nums.push_back(5);
        cout << checkDupWithinK(nums, 3) << endl;
    }
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.push_back(4);
        nums.push_back(4);
        cout << checkDupWithinK(nums, 3) << endl;
    }
    {
        vector<int> nums;
        nums.push_back(10);
        nums.push_back(5);
        nums.push_back(3);
        nums.push_back(4);
        nums.push_back(3);
        nums.push_back(5);
        nums.push_back(6);
        cout << checkDupWithinK(nums, 3) << endl;
    }
    return 0;
}
