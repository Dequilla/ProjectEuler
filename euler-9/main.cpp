#include <iostream>
#include "../include/math.hpp"
#include "../include/benchmark.hpp"

void solution_1()
{
	for( double a = 1; a < 998; a++ )
	{
		for( double b = a + 1; b < 998; b++ )
		{
			if( a + b >= 1000 ) break;

			const double c = math::pythagoras( a, b );

			if( a + b + c == 1000 )
			{
				std::cout << std::format( "Found triplet: a = {}, b = {}, c = {}!", a, b, c ) << std::endl;
				std::cout << std::format( "Product abc is: {}*{}*{}={}", a, b, c, ( a * b * c ) ) << std::endl;
				return;
			}
		}
	}
}

int main( int argc, char** argv )
{
	int status = 0;

	BENCHMARK( solution_1, benchmarker );
	benchmarker.benchmark();
	std::cout << benchmarker.resultTable() << std::endl;

	const auto average = benchmarker.average();
	std::cout << "Average time: " << average.duration << std::endl;
	std::cout << "Average memory: " << average.maxMemoryUsed << std::endl;


	return status;
}
