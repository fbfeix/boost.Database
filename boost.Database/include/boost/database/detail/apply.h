#ifndef BOOST_DATABASE_APPLY_H_
#define BOOST_DATABASE_APPLY_H_


#include <boost/tuple/tuple.hpp>
#include <iostream> 
#include <string>
#include <type_traits>
#include <utility>

namespace database
{
	namespace detail
	{
		using namespace boost;

		// ------------- UTILITY---------------
		template <int...> struct index_tuple {};

		template <int I, typename IndexTuple, typename... Types> struct make_indexes_impl;

		template <int I, int... Indexes, typename T, typename... Types>
		struct make_indexes_impl<I, index_tuple<Indexes...>, T, Types...> {
			typedef typename make_indexes_impl<I + 1, index_tuple<Indexes..., I>, Types...>::type type;
		};

		template <int I, int... Indexes> struct make_indexes_impl<I, index_tuple<Indexes...> > {
			typedef index_tuple<Indexes...> type;
		};

		template <typename... Types> struct make_indexes : make_indexes_impl<0, index_tuple<>, Types...> {};

		// ----------UNPACK TUPLE AND APPLY TO FUNCTION ---------
		template <class Ret, class Tuple, class... Args, int... Indexes>
		Ret apply_helper(Ret(*pf)(Args...), index_tuple<Indexes...>, Tuple&& tup) {
			return pf(std::forward<Args>(get<Indexes>(std::forward<Tuple>(tup)))...);
		}

		template <class Ret, class Tuple, class... Args>
		Ret apply(Ret(*pf)(Args...), Tuple&& tup) {
			return apply_helper(pf, typename make_indexes<Args...>::type(), std::forward<Tuple>(tup));
		}

		/* end of apply methods */

		


		


	} // namespace detail
} // database


#endif /* BOOST_DATABASE_APPLY_H_ */