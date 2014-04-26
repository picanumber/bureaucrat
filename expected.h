#ifndef EXPECTED_HPP_IMPL
#define EXPECTED_HPP_IMPL


#include <exception>
#include <algorithm>
#include <stdexcept>


template<class T>
class Expected
{
	union {
		T ham;
		std::exception_ptr spam;
	};
	bool gotHam;
	Expected() {} // used internally
public:
	// ------------------------- Construction
	Expected(T const &rhs)
		: ham(rhs)
		, gotHam(true)
	{
	}
	Expected(T &&rhs)
		: ham(std::move(rhs))
		, gotHam(true)
	{
	}
	Expected(Expected const &rhs)
		: gotHam(rhs.gotHam)
	{
		if (gotHam) new(&ham) T(rhs.ham);
		else new(&spam) std::exception_ptr(rhs.spam);
	}
	Expected(Expected &&rhs)
		: gotHam(rhs.gotHam)
	{
		if (gotHam) new(&ham) T(std::move(rhs.ham));
		else new(&spam) std::exception_ptr(std::move(rhs.spam));
	}
	// ----------------------------- Swapping
	void swap(Expected &rhs)
	{
		if (gotHam)
		{
			if (rhs.gotHam)
			{
				using std::swap;
				swap(ham, rhs.ham);
			}
			else
			{
				auto t = std::move(rhs.spam);
				new(&rhs.ham) T(std::move(ham));
				new(&spam) std::exception_ptr(t);
				std::swap(gotHam, rhs.gotHam);
			}
		}
		else
		{
			if (rhs.gotHam)
			{
				rhs.swap(*this);
			}
			else
			{
				spam.swap(rhs.spam);
				std::swap(gotHam, rhs.gotHam);
			}
		}
	}
	// -------------- Building from exception
	template<class E>
	static Expected<T> fromException(E const &exception)
	{
		if (typeid(exception) != typeid(E))
		{
			throw std::invalid_argument("slicing detected");
		}
		return fromException(std::make_exception_ptr(exception));
	}

	static Expected<T> fromException(std::exception_ptr p)
	{
		Expected<T> result;
		result.gotHam = false;
		new(&result.spam) std::exception_ptr(std::move(p));
		return result;
	}

	static Expected<T> fromException()
	{
		return fromException(std::current_exception());
	}
	// ------------------------------- Access
	bool valid() const
	{
		return gotHam;
	}

	T& get()
	{
		if (!gotHam) std::rethrow_exception(spam);
		return ham;
	}

	T const& get() const
	{
		if (!gotHam) std::rethrow_exception(spam);
		return ham;
	}
	// --------------------- probing for type
	template<class E>
	bool hasException() const
	{
		try
		{
			if (!gotHam) std::rethrow_exception(spam);
		}
		catch (E const &object)
		{
			return true;
		}
		catch (...)
		{
		}
		return false;
	}
	// -------------------------------- Icing
	template<class F>
	static Expected fromCode(F fun)
	{
		try
		{
			return Expected(fun());
		}
		catch (...)
		{
			return fromException();
		}
	}
};


#endif
