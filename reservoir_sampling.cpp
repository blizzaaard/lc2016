#include <iostream>
#include <map>
#include <sstream>
#include <time.h>
#include <random>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

void print(const map<int, int>& stat)
{
    for (map<int, int>::const_iterator it  = stat.begin();
                                       it != stat.end();
                                     ++it)
    {
        cout << it->first << "\t" << it->second << endl;
    }
    cout << endl;
}

void print(const vector<int>& sample)
{
    for (int i = 0; i < sample.size(); ++i) {
        cout << sample[i] << ' ';
    }
    cout << endl;
}

void stats(map<int, int> *stat, const vector<int>& sample)
{
    for (int i = 0; i < sample.size(); ++i) {
        pair<map<int, int>::iterator, bool> ret =
                stat->insert(make_pair(sample[i], 0));
        ++ret.first->second;
    }
}

vector<int> sampling(istream& stream, int k)
{
    vector<int> reservoir;
    int sample = 0;
    int i      = 0;
    while (1) {
        stream >> sample;
        if (!stream) break;
        if (i < k) {
            reservoir.resize(i + 1);
            reservoir[i] = sample;
        } else {
            // TODO: better distribution
            //
            // random_device rdev;
            // mt19937 mt(rdev());
            // uniform_int_distribution<int> dist(0, i);
            // int j = dist(mt);

            int j = (rand() * 1.0 / RAND_MAX) * (i + 1); // +1 for better scaling
            if (j < k) reservoir[j] = sample;
        }
        ++i;
    }
    return reservoir;
}

int main()
{
    srand(time(0));

    ostringstream oss;
    for (int i = 0; i < 10; ++i) {
        oss << i << ' ';
    }

    map<int, int> stat;

    for (int i = 0; i < 1000000; ++i) {
        istringstream iss(oss.str());
        vector<int> sample = sampling(iss, 4);
        stats(&stat, sample);
    }

    print(stat);

    return 0;
}
