#include <iostream>
#include <cassert>
#include <vector>

#include "../include/math.hpp"

int main(int argc, char** argv)
{
    std::vector<size_t> primes;
    math::build_primes_count(primes, 10'001);

    std::cout << "Count: " << primes.size() << std::endl;
    std::cout << "10.001th prime: " << *(primes.end() - 1) << std::endl;

    return 0;
}
