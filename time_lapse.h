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
	* Example usage
	*     cout << measure<>::execution( [&]() {
	*         // some task
	*     });
	*/
	template<typename TimeT = std::chrono::milliseconds>
	struct measure
	{
		template<typename F, typename ...Args>
		static typename TimeT::rep execution(F func, Args&&... args)
		{
			auto start = std::chrono::system_clock::now();
			
			func(std::forward<Args>(args)...);

			auto duration = std::chrono::duration_cast<TimeT>(
				std::chrono::system_clock::now() - start);

			return duration.count();
		}
	};
}


#endif

