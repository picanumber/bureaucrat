#ifndef FUNCTIONAL_CAST_HPP_LK35GHD_IMPL
#define FUNCTIONAL_CAST_HPP_LK35GHD_IMPL


// ------------------------------- # INCLUDES
#include<functional>
// ~ INCLUDES -------------------------------


namespace fcast
{
	/**
	* @ struct memfun_type
	* @ brief  Captures the type of a member function
	*/
	template<typename T>
	struct memfun_type
	{
		using type = void;
	};

	template<typename Ret, typename Class, typename... Args>
	struct memfun_type<Ret(Class::*)(Args...) const>
	{
		using type = std::function<Ret(Args...)>;
	};

	/**
	* @ fn    FFL
	* @ brief Casts a callable to the respective std::function type
	*
	* Example usage (disambiguate the type of a lambda)
	*     FFL([](int i, string s) { cout << i << ' ' << s << endl; });
	*/
	template<typename F>
	typename memfun_type<decltype(&F::operator())>::type FFL(F const &func)
	{
		return func;
	}
}


#endif

