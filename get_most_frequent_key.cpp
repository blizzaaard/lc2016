#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <cassert>
#include <iostream>
#include <iterator>

using namespace std;

void print(const unordered_set<string>& result)
{
    for (unordered_set<string>::const_iterator it  = result.begin();
                                               it != result.end();
                                             ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

struct Bucket {

    unordered_set<string> m_set;   // all the 'key' occurred 'm_count' times
    int                   m_count; // the number of occurrences of the keys in
                                   // this bucket

    explicit Bucket(const int count)
    : m_count(count)
    {
    }
};

class HashTable {
    // insert(), remove() and getMostFrequentKey() are all O(1) operation.
    //
    //   bucket     bucket     bucket
    //   +---+      +---+      +---+
    //   | 1 |----->| 6 |----->| 9 |
    //   +---+      +---+      +---+
    //     |          |          |
    //   (set)      (set)      (set)
    // keys that  keys that  keys that
    // occurred   occurred   occurred
    // once       6 times    9 times

    typedef list<Bucket>                                BucketList;
    typedef unordered_map<string, BucketList::iterator> Hash;

    BucketList m_list;
    Hash       m_hash;

  public:
    void insert(const string& key)
    {
        Hash::iterator it = m_hash.find(key);
        if (it == m_hash.end()) {
            if (m_list.empty() || m_list.front().m_count != 1) {
                // Insert a new bucket with 'count' being 1 at the beginning of
                // the list if either the list is empty or the first bucket's
                // count is not 1.

                m_list.push_front(Bucket(1));
            }

            // Insert the key into the new bucket

            m_list.front().m_set.insert(key);

            // Insert the key and the bucket iterator into the hash.

            m_hash.insert(make_pair(key, m_list.begin()));
        } else {
            BucketList::iterator curr = it->second;
            BucketList::iterator next = curr;
            advance(next, 1);

            // TODO: optimization - if there's only one element in the bucket
            // and the next bucket's count is more than one greater than the
            // current one's, we can just increament the current bucket's count
            // by 1.

            if (next == m_list.end() || next->m_count != curr->m_count + 1) {
                // Insert a new bucket with 'count' being the next larger
                // number if the next bucket's count is more than one greater
                // than the current one's.

                next = m_list.insert(next, Bucket(curr->m_count + 1));
            }

            // Insert the key into the new bucket and remove it from the
            // original bucket.

            next->m_set.insert(key);
            curr->m_set.erase(key);

            // Remove the bucket from the bucket list if the bucket contains no
            // more elements.

            if (curr->m_set.empty()) m_list.erase(curr);

            // Update the bucket iterator for the key in the hash.

            m_hash.erase(it);
            m_hash.insert(make_pair(key, next));
        }
    }

    void remove(const string& key)
    {
        Hash::iterator it = m_hash.find(key);
        if (it == m_hash.end()) return;

        BucketList::iterator curr = it->second;
        BucketList::iterator prev = curr;
        advance(prev, -1);

        if (curr->m_count == 1) {
            // If this is the last occurrence of this key, just remove it.

            curr->m_set.erase(key);

            // Remove the bucket from the bucket list if the bucket contains no
            // elements anymore.

            if (curr->m_set.empty()) m_list.erase(curr);

            m_hash.erase(it);

            return;
        }

        if (prev == m_list.end() || prev->m_count != curr->m_count - 1) {
            // Insert a new bucket with 'count' being the next smaller number
            // if the previous bucket's count is more than one smaller than the
            // current one's.

            prev = m_list.insert(curr, Bucket(curr->m_count - 1));
        }

        // Insert the key into the new bucket and remove it from the original
        // bucket.

        prev->m_set.insert(key);
        curr->m_set.erase(key);

        // Remove the bucket from the bucket list if the bucket contains no
        // elements anymore.

        if (curr->m_set.empty()) m_list.erase(curr);

        // Update the bucket iterator for the key in the hash.

        m_hash.erase(it);
        m_hash.insert(make_pair(key, prev));
    }

    const unordered_set<string>& getMostFrequentKey()
    {
        static unordered_set<string> emptySet;
        if (m_list.empty()) return emptySet;
        return m_list.back().m_set;
    }

    void debug() const
    {
        for (BucketList::const_iterator it  = m_list.begin();
                                        it != m_list.end();
                                      ++it)
        {
            cout << it->m_count << '\t';
            for (unordered_set<string>::const_iterator jt  = it->m_set.begin();
                                                       jt != it->m_set.end();
                                                     ++jt)
            {
                cout << *jt << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main()
{
    HashTable ht;

    ht.insert("abc");
    ht.insert("def");
    ht.insert("abc");
    ht.insert("def");
    ht.insert("abc");
    ht.insert("ghi");
    ht.debug();

    print(ht.getMostFrequentKey());

    ht.remove("def");
    ht.debug();

    print(ht.getMostFrequentKey());

    ht.remove("abc");
    ht.debug();

    print(ht.getMostFrequentKey());

    ht.remove("def");
    ht.remove("ghi");
    ht.debug();

    print(ht.getMostFrequentKey());

    ht.remove("abc");
    ht.remove("abc");
    ht.remove("abc");
    ht.debug();

    print(ht.getMostFrequentKey());

    return 0;
}
