#include <iostream>

#include <cstddef>
#include <iostream>
#include <vector>
#include <type_traits>
#include <csignal>

#define decl(x) std::remove_cv<decltype(x)>::type

template<typename T>
bool isPrime(T val) requires ( std::is_arithmetic<T>::value )
{
    if( val < 2 )
        return false;

    if( val == 2 )
        return true;

    if( val % 2 == 0 )
        return false;

    for( T i = 3; (i * i) <= val; i += 2 )
    {
        if( val % i == 0 )
            return false;
    }

    return true;
}

template<typename T>
void build_primes(std::vector<T>& rPrimes, const T& max) requires std::is_arithmetic<T>::value
{
    for( T i = 3; (i * i) <= max; i += 2 )
    {
        if( isPrime(i) )
            rPrimes.push_back(i);
    }
}

int main(int argc, char** argv)
{
    const size_t TARGET = 600'851'475'143; 

    std::vector<decl(TARGET)> primes;
    build_primes(primes, TARGET);

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
