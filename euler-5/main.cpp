#include <iostream>

int main(int argc, char** argv)
{
    constexpr size_t START = 20 * 20;
    const size_t PRIMES[] = {1, 2, 3, 5, 7, 9, 11, 13, 17, 19};
    const size_t OTHERS[] = {4, 6, 8, 10, 12, 14, 15, 16, 18, 20};

    for( size_t index = 0; index < static_cast<unsigned int>(0 - 1); index++ )
    {
        bool innerSuccess = true;

        for( size_t p : PRIMES )
        {
            if( index % p != 0 )
            {
                innerSuccess = false;
                break;
            }
        }

        if( !innerSuccess ) continue;

        for( size_t o : OTHERS )
        {
            if( index % o != 0 )
            {
                innerSuccess = false;
                break;
            }
        }

        if( innerSuccess )
            std::cout << "Evenly divisble: " << index << std::endl;
    }

    return 0;
}
