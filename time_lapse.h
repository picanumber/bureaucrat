#ifndef TIME_LAPSE_HPP_SLSK253_IMPL
#define TIME_LAPSE_HPP_SLSK253_IMPL


// ------------------------------- # INCLUDES
#include <chrono>
// ~ INCLUDES -------------------------------


namespace tim
{
	/**
	* @ class measure
	* @ brief Class to measure the execution time of a callable
	*/
	template<typename TimeT = std::chrono::milliseconds>
	struct measure
	{
		/**
		* @ fn    execution
		* @ brief Returns the quantity (count) of the elapsed time as TimeT units
		*/
		template<typename F, typename ...Args>
		static typename TimeT::rep execution(F func, Args&&... args)
		{
			auto start = std::chrono::system_clock::now();
			
			func(std::forward<Args>(args)...);

			auto duration = std::chrono::duration_cast<TimeT>(
				std::chrono::system_clock::now() - start);

			return duration.count();
		}

		/**
		* @ fn    duration
		* @ brief Returns the duration (in chrono's type system) of the elapsed time
		*/
		template<typename F, typename... Args>
		static TimeT duration(F func, Args&&... args)
		{
			auto start = std::chrono::system_clock::now();
			
			func(std::forward<Args>(args)...);
			
			return std::chrono::duration_cast<TimeT>(std::chrono::system_clock::now() - start);
		}
	};
}


#endif

