#include <iostream>
#include <cmath>

template<typename T>
T sum(T start, T count, T step = 1) requires std::is_integral<T>::value
{
    return (count / 2) * (2 * start + (count - 1) * step );
}

int main(int argc, char** argv)
{
    size_t square_of_sum = std::pow( sum( 1, 100), 2);

    size_t sum_of_squares = 0;
    for( size_t index = 1; index <= 100; index++ )
    {
        sum_of_squares += std::pow( index, 2 );
    }

    std::cout << "Square of sum: " << square_of_sum << " | Sum of squares: " << sum_of_squares << std::endl;
    std::cout << "Diff: " << square_of_sum - sum_of_squares << std::endl;

    return 0;
}
