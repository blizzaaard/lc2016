#include <iostream>
#include <unordered_map>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Solution_TwoPass {

  public:
    int randomMaximum(int A[], int size)
    {
        int maximum = A[0];
        int count   = 1;
        for (int i = 1; i < size; ++i) {
            if (maximum < A[i]) {
                maximum = A[i];
                count = 1;
            } else if (maximum == A[i]) {
                ++count;
            }
        }

        // Return each maximum with probability 1 / count

        for (int i = 0; i < size; ++i) {
            if (maximum == A[i]) {
                int k = rand() * 1.0 / RAND_MAX * count;
                if (0 == k) {
                    return i;
                }
                --count;
            }
        }
        return -1;
    }
};

class Solution_OnePass {
    // Use reservior sampling

  public:
    int randomMaximum(int A[], int size)
    {
        int maximum = A[0];
        int count   = 1;
        int index   = 0;
        for (int i = 1; i < size; ++i) {
            if (maximum < A[i]) {
                maximum = A[i];
                count = 1;
                index = i;
            } else if (maximum == A[i]) {
                ++count;
                int k = rand() * 1.0 / RAND_MAX * count;
                if (0 == k) index = i;
            }
        }
        return index;
    }
};

int main()
{
    srand(time(0));

    Solution_OnePass s;

    int A[] = { 2, 3, 1, 3, 0, 1, 3, 3 };

    unordered_map<int, int> count;

    for (int i = 0; i < 10000000; ++i) {
        int index = s.randomMaximum(A, sizeof A / sizeof *A);
        ++count[index];
    }

    for (unordered_map<int, int>::const_iterator it  = count.begin();
                                                 it != count.end();
                                               ++it)
    {
        cout << it->first << " - " << it->second << endl;
    }

    return 0;
}
