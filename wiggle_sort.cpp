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

void sort(vector<int>& nums)
{
    if (nums.empty()) return;

    bool peek = false;
    for (int i = 0; i < nums.size() - 1; ++i) {
        if ((!peek && nums[i] > nums[i + 1])
        ||  ( peek && nums[i] < nums[i + 1]))
        {
            swap(nums[i], nums[i + 1]);
        }
        peek = !peek;
    }
}

int main()
{
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(7);
        nums.push_back(9);
        nums.push_back(3);
        nums.push_back(5);
        sort(nums);
        print(nums);
    }
    return 0;
}
