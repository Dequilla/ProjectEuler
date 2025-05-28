#include <iostream>
#include <vector>

#include "../include/types.hpp"
#include "../include/math.hpp"

int main(int argc, char** argv)
{
    const size_t TARGET = 600'851'475'143; 

    std::vector<decl(TARGET)> primes;
    math::build_primes(primes, TARGET);

    std::vector<decl(TARGET)> primeFactors;
    for( decl(TARGET) index = (primes.size() - 1); index > 0; index -= 1 )
    {
        decl(TARGET) prime = primes[index];

        if( TARGET % prime == 0 )
            primeFactors.push_back(prime);
    }

    for( auto p : primeFactors )
        std::cout << "Prime factor: " << p << std::endl;

    return 0;
}
