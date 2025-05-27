#include <vector>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <type_traits>

template<typename T>
bool isPalindrome( T number ) requires std::is_integral<T>::value
{
    T reverse = 0;
    T temp = number;

    if constexpr ( !std::is_unsigned<T>::value )
    {
        temp = std::llabs(number);
    }
    while(temp != 0)
    {
        reverse = reverse * 10 + temp % 10;
        temp /= 10;
    }

    if constexpr ( !std::is_unsigned<T>::value)
    {
        return (reverse == std::llabs(number));
    }
    else
    {
        return (reverse == number);
    }
}

int main(int argc, char** argv)
{
    size_t MAX = 999;
    std::vector<decltype(MAX)> values;
    for(decltype(MAX) i = MAX; i > 0; i-- )
    {
        for( decltype(MAX) j = MAX; j > 0; j-- )
        {
            decltype(MAX) t = i * j;
            if( isPalindrome( t ) )
                values.push_back(t);
        }
    }

    std::sort( values.begin(), values.end() );

    std::cout << "Palindrome largest: " << values[values.size() - 1] << std::endl;

    return 0;
}
