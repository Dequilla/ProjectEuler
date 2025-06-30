#pragma once
#include <functional>
#include <iomanip>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#ifdef _WIN32
	#include <Windows.h>
	#include <Psapi.h>
#elif __unix__
	// https://stackoverflow.com/questions/5120861/how-to-measure-memory-usage-from-inside-a-c-program
	#include <sys/time.h>
	#include <sys/resource.h>
#endif

namespace bench
{
	template<typename Clock>
	concept IsClock = std::is_base_of_v<std::chrono::steady_clock, Clock>;

	template <IsClock Clock = std::chrono::high_resolution_clock>
	class Timer
	{
		Clock::time_point m_start;

	public:

		Timer();

		[[nodiscard]] Clock::duration read();
		[[maybe_unused]] Clock::duration restart();
	};

	class MemoryMonitor
	{
		std::thread m_thread;
		std::atomic<bool> m_running = false;
		size_t m_usedOnStart = 0;
		size_t m_maxUsed = 0;

		[[nodiscard]] static size_t getCurrentMemoryUsed();

		void monitor();

	public:
		MemoryMonitor();

		size_t stop();
	};

	template<typename FuncDef,
			 IsClock Clock = std::chrono::high_resolution_clock>
	requires std::is_invocable_v<FuncDef>
	class Benchmarker
	{
	public:
		struct Result
		{
			Clock::duration duration;
			size_t maxMemoryUsed;
		};

	private:
		FuncDef m_function;
		std::vector<Result> m_results;
		Timer<Clock> m_timer;
		size_t m_repeat = 100;

	public:
		Benchmarker( FuncDef function );

		void setRepeat( size_t count = 100 );
		void attach( FuncDef function );
		void benchmark();

		const std::string resultTable( size_t nth = 10 ) const;
		Result average() const;
	};

#define BENCHMARK(func, var) \
	bench::Benchmarker<decltype( &func )> var( &func )

	///////////////////////////////////////////////////////////////////////////
	//// Template Implementation

	template <IsClock Clock>
	Timer<Clock>::Timer()
		: m_start( Clock::now() )
	{
	}

	template <IsClock Clock>
	Clock::duration Timer<Clock>::read()
	{
		return ( Clock::now() - m_start );
	}

	template <IsClock Clock>
	Clock::duration Timer<Clock>::restart()
	{
		const auto duration = read();
		m_start = Clock::now();
		return duration;
	}

#ifdef _WIN32
	size_t MemoryMonitor::getCurrentMemoryUsed()
	{
		PROCESS_MEMORY_COUNTERS memCounter;
		BOOL result = K32GetProcessMemoryInfo( GetCurrentProcess(), &memCounter, sizeof( memCounter ) );
		if( result )
			return static_cast<size_t>( memCounter.WorkingSetSize );
		else
			return 0;
	}
#elif __unix__
	static size_t MemoryMonitor::getCurrentMemoryUsed() const
	{
		// https://stackoverflow.com/questions/5120861/how-to-measure-memory-usage-from-inside-a-c-program
		assert( false && "NOT IMPLEMENTED" );
	}
#endif

	void MemoryMonitor::monitor()
	{
		m_running = true;
		while( m_running )
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
			const size_t used = MemoryMonitor::getCurrentMemoryUsed();
			if( used > m_maxUsed )
				m_maxUsed = used;
		}
	}

	MemoryMonitor::MemoryMonitor()
	{
		m_usedOnStart = MemoryMonitor::getCurrentMemoryUsed();
		m_thread = std::thread( &MemoryMonitor::monitor, this );
	}

	size_t MemoryMonitor::stop()
	{
		m_running = false;
		m_thread.join();

		return m_maxUsed - m_usedOnStart;
	}

	template<typename FuncDef, IsClock Clock>
	requires std::is_invocable_v<FuncDef>
	Benchmarker<FuncDef, Clock>::Benchmarker( FuncDef function )
	{
		attach( function );
	}

	template<typename FuncDef, IsClock Clock>
	requires std::is_invocable_v<FuncDef>
	void Benchmarker<FuncDef, Clock>::setRepeat( size_t count )
	{
		m_repeat = count;
	}

	template<typename FuncDef, IsClock Clock>
	requires std::is_invocable_v<FuncDef>
	void Benchmarker<FuncDef, Clock>::attach( FuncDef function )
	{
		m_function = function;
	}

	template<typename FuncDef, IsClock Clock>
	requires std::is_invocable_v<FuncDef>
	void Benchmarker<FuncDef, Clock>::benchmark()
	{
		assert( m_function );

		for( size_t counter = 0; counter < m_repeat; counter++ )
		{
			m_timer.restart();
			m_function();
			const auto duration = m_timer.read();

			// Probably not very precise but should work...
			MemoryMonitor monitor;
			m_function();
			const size_t used = monitor.stop();
			m_results.emplace_back( Result { duration, used } );

			// Allow memory to
			// reset?
			std::this_thread::sleep_for( std::chrono::nanoseconds( 50 ) );

		}
	}

	template<typename FuncDef, IsClock Clock>
	requires std::is_invocable_v<FuncDef>
	Benchmarker<FuncDef, Clock>::Result Benchmarker<FuncDef, Clock>::average() const
	{
		Result average;
		for( const auto& result : m_results )
		{
			average.duration += result.duration;
			average.duration /= 2;

			average.maxMemoryUsed += result.maxMemoryUsed;
			average.maxMemoryUsed /= 2;
		}

		return average;
	}

	template<typename FuncDef, IsClock Clock>
	requires std::is_invocable_v<FuncDef>
	const std::string Benchmarker<FuncDef, Clock>::resultTable( size_t nth ) const
	{
		std::stringstream ss;
		ss << "." << std::setfill( '-' ) << std::setw( 10 ) << "Timings" << std::setfill( '-' ) << std::setw( 10 ) << "Memory" << "." << std::endl;
		for( size_t index = 0; index < m_results.size(); index += nth )
		{
			ss << "|" << std::setfill( ' ' ) << std::setw( 10 ) << m_results[index].duration
			   << "|" << std::setfill( ' ' ) << std::setw( 9 ) << m_results[index].maxMemoryUsed << "|" << std::endl;
		}

		return ss.str();
	}
}
