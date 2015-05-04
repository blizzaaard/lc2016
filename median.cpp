#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

// What is the distributed algorithm to determine the median of arrays of
// integers located on different computers?
//
// Suppose you have a master node (or are able to use a consensus protocol to
// elect a master from among your servers).  The master first queries the
// servers for the size of their sets of data, call this n, so that it knows to
// look for the k = n/2 largest element.
//
// The master then selects a random server and queries it for a random element
// from the elements on that server.  The master broadcasts this element to
// each server, and each server partitions its elements into those larger than
// or equal to the broadcasted element and those smaller than the broadcasted
// element.
//
// Each server returns to the master the size of the larger-than partition,
// call this m.  If the sum of these sizes is greater than k, the master
// indicates to each server to disregard the less-than set for the remainder of
// the algorithm.  If it is less than k, then the master indicates to disregard
// the larger-than sets and updates k = k - m.  If it is exactly k, the
// algorithm terminates and the value returned is the pivot selected at the
// beginning of the iteration.
//
// If the algorithm does not terminate, recurse beginning with selecting a new
// random pivot from the remaining elements.
//
// http://www.quora.com/Distributed-Algorithms/What-is-the-distributed-algorithm-to-determine-the-median-of-arrays-of-integers-located-on-different-computers


class Solution_TwoHeaps {
    // - stream supported
    // - time complexity O(nlogn)
    //
    // For the first two elements add smaller one to the maxHeap on the left,
    // and bigger one to the minHeap on the right. Then process stream data one
    // by one,
    //
    // Step 1: Add next item to one of the heaps
    //
    //    if next item is smaller than maxHeap root add it to maxHeap, else add
    //    it to minHeap
    //
    // Step 2: Balance the heaps (after this step heaps will be either balanced
    //         or one of them will contain 1 more item)
    //
    //    if number of elements in one of the heaps is greater than the other
    //    by more than 1, remove the root element from the one containing more
    //    elements and add to the other one
    //
    // Then at any given time you can calculate median like this:
    //
    //    If the heaps contain equal elements;
    //      median = (root of maxHeap + root of minHeap)/2
    //    Else
    //      median = root of the heap with more elements

  public:
    double median(istream& stream)
    {
        priority_queue<int, vector<int>, greater<int> > minHeap;
        priority_queue<int> maxHeap;

        for (int i = 0; i < 2; ++i) {
            int num = 0;
            stream >> num;
            if (!stream) break;
            if (minHeap.empty() && maxHeap.empty()) {
                minHeap.push(num);
            } else if (minHeap.top() < num) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(num);
            } else {
                maxHeap.push(num);
            }
        }

        while (1) {
            int num = 0;
            stream >> num;
            if (!stream) break;

            // Add the number to the max heap if it's smaller than the root of
            // the max heap

            if (num < maxHeap.top()) maxHeap.push(num);
            else minHeap.push(num);

            // Rebalance the two heaps

            if ((int)(maxHeap.size() - minHeap.size()) > 1) {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
            if ((int)(minHeap.size() - maxHeap.size()) > 1) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
        }

        if (maxHeap.empty() && minHeap.empty())
            return 0;
        else if (maxHeap.size() == minHeap.size())
            return (maxHeap.top() + minHeap.top()) / (double) 2;
        else if (maxHeap.size() > minHeap.size())
            return maxHeap.top();
        else
            return minHeap.top();
    }
};

class Solution_CountingSort {
    // - stream supported
    // - time complexity O(n)
    // - range of the input should be small

  public:
    double median(istream& stream, const int min, const int max)
    {
        vector<int> result;
        vector<int> count(max - min + 1, 0);
        while (1) {
            int num = 0;
            stream >> num;
            if (!stream) break;
            ++count[num - min];
        }

        for (int i = min; i <= max; ++i) {
            while (count[i - min] > 0) {
                result.push_back(i);
                --count[i - min];
            }
        }

        int n = result.size();
        if (n % 2)
            return result[n / 2];
        else
            return (result[(n - 1) / 2 + 1] + result[(n - 1) / 2]) / (double) 2;
    }
};

class Solution_Selection {
    // - stream NOT supported
    // - time complexity O(n)

    int partition(vector<int>& nums, int start, int end)
    {
        int pivot = nums[end];
        int i = start - 1;
        for (int j = start; j < end; ++j) {
            if (nums[j] <= pivot) {
                ++i;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[end]);
        return i + 1;
    }

    int kth_element(vector<int>& nums, int start, int end, int k)
    {
        int pivot = partition(nums, start, end);
        if (pivot == k)     return nums[pivot];
        else if (k > pivot) return kth_element(nums, pivot + 1, end, k);
        else                return kth_element(nums, start, pivot - 1, k);
    }

  public:
    double median(vector<int>& nums)
    {
        int n = nums.size();
        if (n % 2) return kth_element(nums, 0, n - 1, n / 2);
        else {
            int a = kth_element(nums, 0, n - 1, (n - 1) / 2);
            int b = kth_element(nums, 0, n - 1, (n - 1) / 2 + 1);
            return (a + b) / (double) 2;
        }
    }
};

int main()
{
    string input = "5 3 8 9 7 6 2 11 12 13 14 15 16 17 18 19";
    {
        Solution_TwoHeaps s;
        istringstream iss(input);
        cout << s.median(iss) << endl;
    }
    {
        Solution_CountingSort s;
        istringstream iss(input);
        cout << s.median(iss, 0, 100) << endl;
    }
    {
        istringstream iss(input);
        vector<int> nums;
        while (1) {
            int num = 0;
            iss >> num;
            if (!iss) break;
            nums.push_back(num);
        }
        Solution_Selection s;
        cout << s.median(nums) << endl;
    }
    return 0;
}
