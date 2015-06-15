// Contigious Subarray Sum
//
// Given a Array A containing positive integers and a integer K , find if there
// exist a subarray of A whose sum = K


#include <iostream>
#include <vector>

using namespace std;

void print(const pair<int, int>& result)
{
    cout << result.first << ' ' << result.second << endl;
}

pair<int, int> hasSum(const vector<int>& nums, int target)
    // Despite having two nested loops, this code runs in linear time because i
    // and j never decrease, and can only be incremented O(N) times.
{
    int maxLen = 0, start = -1, end = -1;

    int n = nums.size();
    if (0 >= n) return make_pair(start, end);

    int i = 0, j = 0, sum = 0;
    while (i < n) {
        while (j < n && sum < target) sum += nums[j++];
        if (sum == target) {
            if (maxLen < j - i + 1) {
                maxLen = j - i + 1;
                start  = i;
                end    = j;
            }
        }
        sum -= nums[i++];
    }

    return make_pair(start, end);
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
        nums.push_back(19);
        nums.push_back(24);
        nums.push_back(4);
        nums.push_back(7);
        nums.push_back(9);
        nums.push_back(45);
        print(hasSum(nums, 16));
    }
    {
        vector<int> nums;
        nums.push_back(1);
        print(hasSum(nums, 2));
    }
    return 0;
}
