#ifndef PRINTERS_HPP_KLDJF8_IMPL
#define PRINTERS_HPP_KLDJF8_IMPL


// ------------------------------- # INCLUDES
#include <iostream>
// ~ INCLUDES -------------------------------


namespace itt
{
	template<typename Iter>
	struct is_reverse_iterator
		: std::false_type
	{
	};

	template<typename Iter>
	struct is_reverse_iterator<std::reverse_iterator<Iter>>
		: std::integral_constant<bool, !is_reverse_iterator<Iter>::value>
	{
	};

	namespace prive
	{
		template<bool isRev>
		struct is_last_it
		{ // for normal iterators
			template<typename It, typename Cont>
			static bool apply(It it, Cont const &cont)
			{
				return it != cont.end() && ++it == cont.end();
			}
		};

		template<>
		struct is_last_it<true>
		{ // for reverse iterators
			template<typename It, typename Cont>
			static bool apply(It it, Cont const &cont)
			{
				return it != cont.rend() && ++it == cont.rend();
			}
		};
	}

	template<typename It, typename Cont>
	bool IsLastIter(It it, Cont const &cont)
	{
		return prive::is_last_it<is_reverse_iterator<It>::value>::apply(it, cont);
	};
}


#endif
