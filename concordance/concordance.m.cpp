#include "concordance.h"
#include <iostream>

int main()
{
    yguo::Concordance concordance;
    concordance.build(std::cin);
    std::cout << concordance << std::endl;

    return 0;
}
