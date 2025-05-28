#include <vector>
#include <iostream>

#include "../include/types.hpp"
#include "../include/math.hpp"

int main(int argc, char** argv)
{
    size_t MAX = 999;
    std::vector<decltype(MAX)> values;
    for(decltype(MAX) i = MAX; i > 0; i-- )
    {
        for( decltype(MAX) j = MAX; j > 0; j-- )
        {
            decltype(MAX) t = i * j;
            if( math::isPalindrome( t ) )
                values.push_back(t);
        }
    }

    std::sort( values.begin(), values.end() );

    std::cout << "Palindrome largest: " << values[values.size() - 1] << std::endl;

    return 0;
}
