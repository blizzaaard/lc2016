#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

void print(const vector<int>& counter)
{
    for (int i = 0; i < counter.size(); ++i) {
        cout << counter[i] << " ";
    }
    cout << endl;
}

class Solution {

  public:
    int hindex(int A[], int size)
    {
        vector<int> count(size + 1, 0);

        for (int i = 0; i < size; ++i) {
            ++count[min(A[i], size)];
        }

        int sum = 0;
        for (int i = size; i >= 0; --i) {
            sum += count[i];
            if (sum >= i) return i;
        }

        return 0;
    }
};

class Solution_Partition {

    int partition(int A[], int start, int end)
    {
        int pivot = A[end];
        int i = start - 1;
        for (int j = start; j < end; ++j) {
            if (A[j] <= pivot) {
                ++i;
                swap(A[j], A[i]);
            }
        }
        swap(A[i + 1], A[end]);
        return i + 1;
    }

  public:
    int hindex(int A[], int size)
    {
        int start = 0, end = size - 1;
        int index = 0;

        while (start < end) {
            int pivot = partition(A, start, end);
            if (A[pivot] <= size - pivot) {
                // A[pivot] satisfies the requirement, now examine the right
                // part and see if there's a larger value that can satisfy too.

                index = pivot;
                start = pivot + 1;
            } else {
                // A[pivot] does not satisfy the requirement, now examine the
                // left part and see if there's a smaller value that can
                // satisfy.

                end = pivot - 1;
            }
        }

        return max(A[index], size - index - 1);
    }
};

int main()
{
    Solution_Partition s;

    {
        int A[] = { 6, 5, 5, 5, 5 };
        assert(5 == s.hindex(A, sizeof A / sizeof *A));
    }
    {
        int A[] = { 1, 3, 4, 7, 8, 9 };
        assert(4 == s.hindex(A, sizeof A / sizeof *A));
    }
    {
        int A[] = { 1, 2, 5, 7, 8 };
        assert(3 == s.hindex(A, sizeof A / sizeof *A));
    }
    {
        int A[] = { 5, 8, 1, 2, 7 };
        assert(3 == s.hindex(A, sizeof A / sizeof *A));
    }

    return 0;
}
