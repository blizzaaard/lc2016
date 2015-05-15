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

int LAP(const vector<int>& nums)
{
    int n = nums.size();
    if (n < 2) return 0;

    vector<vector<int> > opt(n, vector<int>(n, 2));
        // opt[i][j] = LAP with starting pair (nums[i], nums[j])

    int maxLength = 0;

    for (int j = n - 2; j > 0; --j) {
        int i = j - 1;
        int k = j + 1;
        while (i >= 0 && k <= n - 1) {
            int k_j = nums[k] - nums[j];
            int j_i = nums[j] - nums[i];
            if (k_j > j_i) {
                --i;
            } else if (k_j < j_i) {
                ++k;
            } else {
                opt[i][j] = opt[j][k] + 1;
                maxLength = max(maxLength, opt[i][j]);
                --i; ++k;
            }
        }
    }

    return maxLength;
}

vector<int> getLAP(const vector<int>& nums)
{
    vector<int> result;

    int n = nums.size();
    if (n < 2) return result;

    vector<vector<int> > opt(n, vector<int>(n, 2));
    vector<vector<int> > trace(n, vector<int>(n, -1));

    int traceI = 0, traceJ = 1;
    int maxLength = 2; // there is at least 2 elements which form a LAP

    for (int j = n - 2; j > 0; --j) {
        int i = j - 1;
        int k = j + 1;
        while (i >= 0 && k <= n - 1) {
            int k_j = nums[k] - nums[j];
            int j_i = nums[j] - nums[i];
            if (k_j > j_i) {
                --i;
            } else if (k_j < j_i) {
                ++k;
            } else {
                opt[i][j] = opt[j][k] + 1;
                trace[i][j] = k;
                if (maxLength < opt[i][j]) {
                    traceI = i;
                    traceJ = j;
                    maxLength = opt[i][j];
                }
                --i; ++k;
            }
        }
    }

    result.push_back(nums[traceI]);
    while (traceJ >= 0) {
        result.push_back(nums[traceJ]);
        int temp = traceJ;
        traceJ = trace[traceI][traceJ];
        traceI = temp;
    }

    return result;
}

int main()
{
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        cout << LAP(nums) << endl;
        print(getLAP(nums));
    }
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(7);
        nums.push_back(10);
        nums.push_back(15);
        nums.push_back(27);
        nums.push_back(29);
        cout << LAP(nums) << endl;
        print(getLAP(nums));
    }
    {
        vector<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.push_back(4);
        nums.push_back(6);
        nums.push_back(8);
        nums.push_back(10);
        nums.push_back(11);
        nums.push_back(12);
        nums.push_back(13);
        nums.push_back(14);
        nums.push_back(16);
        nums.push_back(18);
        cout << LAP(nums) << endl;
        print(getLAP(nums));
    }
    return 0;
}
