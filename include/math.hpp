#pragma once
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>

#include "types.hpp"

namespace math
{
	template<typename T>
	T generate_sum( T start, T count, T step = 1 ) requires std::is_integral<T>::value
	{
		return ( count / 2 ) * ( 2 * start + ( count - 1 ) * step );
	}

	template<typename In, typename Out>
	Out sum( In* values, size_t count ) requires( std::is_arithmetic<In>::value && std::is_arithmetic<Out>::value )
	{
		assert( count > 0 );

		Out sum = 0;

		#pragma omp simd
		for( size_t i = 0; i < count; i++ )
			sum += static_cast<Out>( values[i] );

		return sum;
	}

	template<typename T>
	bool is_prime( T val ) requires( std::is_arithmetic<T>::value )
	{
		if( val < 2 )
			return false;

		if( val == 2 )
			return true;

		if( val % 2 == 0 )
			return false;

		for( T i = 3; ( i * i ) <= val; i += 2 )
		{
			if( val % i == 0 )
				return false;
		}

		return true;
	}

	template<typename T>
	void build_primes( std::vector<T> &rPrimes, const T& max ) requires std::is_arithmetic<T>::value
	{
		for( T i = 3; ( i * i ) <= max; i += 2 )

			if( is_prime( i ) )
				rPrimes.push_back( i );
	}

	template<typename T>
	void build_primes_count( std::vector<T> &rPrimes, const size_t &count ) requires std::is_arithmetic<T>::value
	{
		assert( count > 0 );

		if( count >= 2 )
			rPrimes.push_back( 2 );

		// Maximum to i*i == MAX_32BIT_INT
		for( T i = 3; ( i * i ) <= static_cast<size_t>( static_cast<int>( 0 - 1 ) ); i += 2 )
		{
			if( is_prime( i ) )
				rPrimes.push_back( i );

			if( rPrimes.size() >= count )
				break;
		}
	}

	template<typename T>
	bool is_palindrome( T number ) requires std::is_integral<T>::value
	{
		T reverse = 0;
		T temp = number;

		if constexpr( !std::is_unsigned<T>::value )
		{
			temp = std::llabs( number );
		}
		while( temp != 0 )
		{
			reverse = reverse * 10 + temp % 10;
			temp /= 10;
		}

		if constexpr( !std::is_unsigned<T>::value )
		{
			return ( reverse == std::llabs( number ) );
		}
		else
		{
			return ( reverse == number );
		}
	}

	template<typename T>
	inline bool is_pythagorean_triplet( T a, T b, T c )
	requires std::is_arithmetic_v<T>
	{
		if( !( c > b && b > a ) )
			return false;

		return true;
	}

	template<typename T>
	inline T pythagoras( T a, T b )
	requires std::is_arithmetic_v<T>
	{
		return (
			std::sqrt(
				std::pow( a, 2 ) + std::pow( b, 2 )
			)
		);
	}
}
