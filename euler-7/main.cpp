#include <iostream>
#include <cassert>
#include <vector>

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
void build_primes(std::vector<T>& rPrimes, const size_t& max) requires std::is_arithmetic<T>::value
{
    assert(max > 0);

    if( max >= 2 )
        rPrimes.push_back(2);

    for( T i = 3; (i * i) <= static_cast<size_t>( static_cast<int>(0 - 1) ); i += 2 )
    {
        if( isPrime(i) )
            rPrimes.push_back(i);

        if( rPrimes.size() >= max )
            break;
    }
}

int main(int argc, char** argv)
{
    std::vector<size_t> primes;
    build_primes(primes, 10'001);

    std::cout << "Count: " << primes.size() << std::endl;
    std::cout << "10.001th prime: " << *(primes.end() - 1) << std::endl;

    return 0;
}
