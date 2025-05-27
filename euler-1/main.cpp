#include <iostream>

int main(int argc, char** argv)
{
    const int UPPER = 1000;
    const int LOWER = 0;

    size_t sum = 0;
    for( size_t i = LOWER; i < UPPER; i++ )
    {
        if( i % 3 == 0 || i % 5 == 0 )
        {
            sum += i;
        }
    }

    std::cout << sum << std::endl;

    return sum;
}
