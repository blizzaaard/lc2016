// http://www.mitbbs.com/article_t1/JobHunting/32906379_0_1.html

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Iterator {

    int *m_data;
    int  m_position;
    int  m_size;

  public:
    explicit Iterator()
    : m_data(0)
    , m_position(-1)
    , m_size(0)
    {
    }

    explicit Iterator(int a[], int size)
    : m_data(a)
    , m_position(-1)
    , m_size(size)
    {
    }

    bool hasNext()
    {
        return m_position < m_size - 1;
    }

    int next()
    {
        return m_data[++m_position];
    }
};

class Solution {

  public:
    bool isDistanceZeroOrOne(Iterator& src, Iterator& dst)
    {
        bool same = true;

        bool rmv = true, add = true, chg = true;

        int currSrc = 0, currDst = 0;
        int prevSrc = 0, prevDst = 0;
        while (src.hasNext() && dst.hasNext()) {
            currSrc = src.next();
            currDst = dst.next();
            if (same) {
                if (currSrc == currDst) continue;
                same = false;
            } else {
                if (rmv && currSrc != prevDst) {
                    rmv = false;
                }
                if (add && prevSrc != currDst) {
                    add = false;
                }
                if (chg && currSrc != currDst) {
                    chg = false;
                }
                if (!rmv && !add && !chg) return false;
            }
            prevSrc = currSrc;
            prevDst = currDst;
        }

        if (!src.hasNext() && !dst.hasNext()) {
            return same || chg;
        } else if (src.hasNext()) {
            currSrc = src.next();
            return (same || (rmv && prevDst == currSrc)) && !src.hasNext();
        } else if (dst.hasNext()) {
            currDst = dst.next();
            return (same || (add && prevSrc == currDst)) && !dst.hasNext();
        }

        return false;
    }
};

class Solution_DP {

  public:
    bool isDistanceZeroOrOne(Iterator& src, Iterator& dst)
    {
        vector<vector<int> > opt(2, vector<int>(2, 0));

        // Assume that the "first" elements of 'src' and 'dst' are empty.

        opt[0][0] = 0;

        int prevSrc = -1, prevDst = -1;
        int currSrc = -1, currDst = -1;

        while (src.hasNext() && dst.hasNext()) {
            currSrc = src.next();
            currDst = dst.next();

            // old:  0 1
            // new:    0 1
            //       x x x
            //       x x x
            // new:    0 1
            // old:  0 1

            // Calculate opt[0][1]

            if (-1 == prevSrc) {
                opt[0][1] = 1; // assume the that first one in 'src' is empty
            } else if (prevSrc == currDst) {
                opt[0][1] = opt[0][1];
            } else {
                opt[0][1] = min(opt[1][1], opt[0][1]) + 1;
            }

            // Calculate opt[1][0]

            if (-1 == prevDst) {
                opt[1][0] = 1; // assume that the first one in 'dst' is empty
            } else if (currSrc == prevDst) {
                opt[1][0] = opt[1][0];
            } else {
                opt[1][0] = min(opt[1][1], opt[1][0]) + 1;
            }

            // Calculate opt[1][1]

            if (currSrc == currDst) {
                opt[1][1] = opt[0][0];
            } else {
                opt[1][1] = min(opt[0][0], min(opt[0][1], opt[1][0])) + 1;
            }

            opt[0][0] = opt[1][1];

            prevSrc = currSrc;
            prevDst = currDst;
        }

        if (!src.hasNext() && !dst.hasNext()) {
            return opt[1][1] < 2;
        } else if (src.hasNext()) {
            currSrc = src.next();
            if (src.hasNext()) return false;
            if (currSrc == prevDst) {
                return opt[1][0] < 2;
            } else {
                return min(opt[1][1], opt[1][0]) + 1 < 2;
            }
        } else if (dst.hasNext()) {
            currDst = dst.next();
            if (dst.hasNext()) return false;
            if (prevSrc == currDst) {
                return opt[0][1] < 2;
            } else {
                return min(opt[1][1], opt[0][1]) + 1 < 2;
            }
        }

        assert(0);
        return false;
    }
};

int main()
{
    // test for the iterator
    {
        int a[] = { 1, 2, 3, 4, 5, 6 };
        Iterator it(a, sizeof a / sizeof *a);
        while (it.hasNext()) {
            cout << it.next() << " ";
        }
        cout << endl;
    }
    {
        int a[] = { 1 };
        Iterator it(a, sizeof a / sizeof *a);
        while (it.hasNext()) {
            cout << it.next() << " ";
        }
        cout << endl;
    }
    {
        int a[] = { 1 };
        Iterator it(a, 0);
        while (it.hasNext()) {
            cout << it.next() << " ";
        }
        cout << endl;
    }


    Solution_DP s;

    // both empty
    {
        Iterator src;
        Iterator dst;
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // empty and 1 element
    {
        int b[] = { 1 };
        Iterator src;
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // empty and 2 elements all 0s
    {
        int b[] = { 0, 0 };
        Iterator src;
        Iterator dst(b, sizeof b / sizeof *b);
        assert(false == s.isDistanceZeroOrOne(src, dst));
    }
    // empty and 2 elements
    {
        int b[] = { 1, 2 };
        Iterator src;
        Iterator dst(b, sizeof b / sizeof *b);
        assert(false == s.isDistanceZeroOrOne(src, dst));
    }
    // one element and 2 elements, missing last element
    {
        int a[] = { 1 };
        int b[] = { 1, 2 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // one element and 2 elements, missing first element
    {
        int a[] = { 2 };
        int b[] = { 1, 2 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // one element and 2 elements, no equal element
    {
        int a[] = { 3 };
        int b[] = { 1, 2 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(false == s.isDistanceZeroOrOne(src, dst));
    }
    // different element in the middle
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6 };
        int b[] = { 1, 2, 3, 4, 5, 4, 8, 7, 6 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // different element in the middle, but equals next element
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6 };
        int b[] = { 1, 2, 3, 4, 5, 8, 8, 7, 6 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // different element at the end
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6 };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 32 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // different element at the end, but equals previous element
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6 };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 7 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // different element at the beginning, but equals next element
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6 };
        int b[] = { 2, 2, 3, 4, 5, 9, 8, 7, 6 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // different element at the beginning, but not equals next element
    {
        int a[] = { 1,  2, 3, 4, 5, 9, 8, 7, 6 };
        int b[] = { 22, 2, 3, 4, 5, 9, 8, 7, 6 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // missing first element
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6 };
        int b[] = {    2, 3, 4, 5, 9, 8, 7, 6 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // missing last element
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7    };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // one difference and missing one
    {
        int a[] = { 1, 2, 3, 4, 5, 4, 7, 6    };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(false == s.isDistanceZeroOrOne(src, dst));
    }
    // two differences and missing one
    {
        int a[] = { 1, 2, 3, 4, 5, 4, 8, 7, 1, 6 };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6    };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(false == s.isDistanceZeroOrOne(src, dst));
    }
    // one difference and missing two
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6       };
        int b[] = { 1, 2, 3, 4, 5, 4, 9, 7, 6, 3, 2 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(false == s.isDistanceZeroOrOne(src, dst));
    }
    //miss one
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6 };
        int b[] = { 1, 2, 3, 4, 5, 9, 7, 6    };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // miss one
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6    };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 1, 6 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // miss one, and equals next
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6    };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 7, 6 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // miss one, and equals next
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 7    };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 1, 7 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(true == s.isDistanceZeroOrOne(src, dst));
    }
    // miss two
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6       };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6, 3, 2 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(false == s.isDistanceZeroOrOne(src, dst));
    }
    // miss two
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 7, 6       };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 1, 6 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(false == s.isDistanceZeroOrOne(src, dst));
    }
    // miss three
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 7, 6          };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6, 3, 2 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(false == s.isDistanceZeroOrOne(src, dst));
    }
    // one extra, miss two
    {
        int a[] = { 1, 2, 3, 4, 5, 9, 8, 7, 1, 6    };
        int b[] = { 1, 2, 3, 4, 5, 9, 8, 7, 6, 3, 2 };
        Iterator src(a, sizeof a / sizeof *a);
        Iterator dst(b, sizeof b / sizeof *b);
        assert(false == s.isDistanceZeroOrOne(src, dst));
    }

    return 0;
}
