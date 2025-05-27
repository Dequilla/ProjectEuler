#include <iostream>

int main(int argc, char** argv)
{
    const int UPPER = 4'000'000; 

    size_t sum = 0;
    for( size_t prev1 = 1, prev2 = 2; prev2 < UPPER;)
    {
        if( prev2 % 2 == 0 )
        {
            sum += prev2;
            std::cout << prev2 << " : "  << sum << std::endl;
        }

        size_t temp = prev2 + prev1;
        prev1 = prev2;
        prev2 = temp;

    }

    std::cout << "Sum: " << sum << std::endl;

    return sum;
}
