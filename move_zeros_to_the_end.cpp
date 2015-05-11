#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& nums)
{
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i] << ' ';
    }
    cout << endl;
}

void move(vector<int>& nums)
{
    if (nums.empty()) return;

    int index = nums.size() - 1;
    int i = 0;
    while (i <= index) {
        if (0 == nums[i]) swap(nums[i], nums[index--]);
        else ++i;
    }
}

int main()
{
    {
        vector<int> nums;
        nums.push_back(0);
        move(nums);
        print(nums);
    }
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(0);
        nums.push_back(2);
        nums.push_back(0);
        nums.push_back(3);
        nums.push_back(0);
        move(nums);
        print(nums);
    }
    {
        vector<int> nums;
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.push_back(0);
        nums.push_back(0);
        move(nums);
        print(nums);
    }
    return 0;
}
