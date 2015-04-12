#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>

void print(const std::map<int, int>& stat)
{
    for (std::map<int, int>::const_iterator it  = stat.begin();
                                            it != stat.end();
                                          ++it)
    {
        std::cout << it->first << "\t" << it->second << std::endl;
    }
    std::cout << std::endl;
}

void print(const std::vector<int>& sample)
{
    for (int i = 0; i < sample.size(); ++i) {
        std::cout << sample[i] << ' ';
    }
    std::cout << std::endl;
}

void stats(std::map<int, int> *stat, const std::vector<int>& sample)
{
    for (int i = 0; i < sample.size(); ++i) {
        std::pair<std::map<int, int>::iterator, bool> ret =
                stat->insert(std::make_pair(sample[i], 0));
        ++ret.first->second;
    }
}

std::vector<int> sampling(std::istream& stream, int k)
{
    std::vector<int> reservoir;
    int sample = 0;
    int i      = 0;
    while (1) {
        stream >> sample;
        if (!stream) break;
        if (i < k) {
            reservoir.resize(i + 1);
            reservoir[i] = sample;
        } else {
            // std::random_device rdev;
            // std::mt19937 mt(rdev());
            // std::uniform_int_distribution<int> dist(0, i);
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

    std::ostringstream oss;
    for (int i = 0; i < 10; ++i) {
        oss << i << ' ';
    }

    std::map<int, int> stat;

    for (int i = 0; i < 1000000; ++i) {
        std::istringstream iss(oss.str());
        std::vector<int> sample = sampling(iss, 4);
        stats(&stat, sample);
    }

    print(stat);

    return 0;
}
