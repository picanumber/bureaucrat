#ifndef INHERITABLE_BEHAVIORS_HPP_IMPL_OSIJFD987
#define INHERITABLE_BEHAVIORS_HPP_IMPL_OSIJFD987


namespace ihb
{
	/**
	* @ struct relational
	* @ brief  Comparison operator provider
	* Intended to be inherited from, by classes that implement
	* "operator<". Provides default (usual) implementations
	* of the relational operators : { >, ==, !=, <=, >= }
	*
	* The operators defined here have weaker precedence in overload resolution 
	* than the ones already defined in the inheriting structure.
	*/
	template<typename T>
	struct relational
	{
		friend bool operator> (relational const &lhs, relational const &rhs)
		{
			return (T const&)rhs < (T const&)lhs;
		}
		
		friend bool operator==(relational const &lhs, relational const &rhs) 
		{ 
			return !((T const&)lhs < (T const&)rhs || (T const&)lhs > (T const&)rhs);
		}

		friend bool operator!=(relational const &lhs, relational const &rhs) 
		{ 
			return !((T const&)rhs == (T const&)lhs);
		}

		friend bool operator<=(relational const &lhs, relational const &rhs) 
		{ 
			return !((T const&)rhs < (T const&)lhs);
		}
		
		friend bool operator>=(relational const &lhs, relational const &rhs) 
		{ 
			return !((T const&)lhs < (T const&)rhs);
		}
	protected:
		~relational()
		{
		}
	};
}


#endif