#ifndef TIME_LAPSE_HPP_SLSK253_IMPL
#define TIME_LAPSE_HPP_SLSK253_IMPL


// ------------------------------- # INCLUDES
#include <chrono>
// ~ INCLUDES -------------------------------


namespace tim
{
	template<typename TimeT = std::chrono::milliseconds>
	struct measure
	{
		template<typename F>
		static typename TimeT::rep execution(F const &func)
		{
			auto start = std::chrono::system_clock::now();
			func();
			auto duration = std::chrono::duration_cast<TimeT>(
				std::chrono::system_clock::now() - start);
			return duration.count();
		}
	};
}


#endif

