// selectable.hpp ----------------------------------------------------//
// -----------------------------------------------------------------------------

// Copyright 2015 Felix Astner

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// -----------------------------------------------------------------------------

// Revision History
// 10-10-2013 dd-mm-yyyy - Initial Release

// -----------------------------------------------------------------------------

#ifndef BOOST_DATABASE_SELECTABLE_HPP
#define BOOST_DATABASE_SELECTABLE_HPP

#include <boost/tuple/tuple.hpp>
#include <boost/database/detail/apply.h>


namespace boost
{
namespace database
{

	/**
	* for selectable classes, it is required to have a static
	* method which creates the object, because static methods can't
	* be overwritten
	* The variadic Template (class...Ts) is dependent to the class
	* instead of the function to allow multiple inheritance of it!
	*/
	/* class iSelectable */
	template <typename...> struct iSelectable;

	template <class... Ts> struct iSelectable {
		template <typename T> static inline T select(Ts &&... params) { return T(std::forward<Ts>(params)...); }
	};

	/* selector_helper */
	template <typename TT, class... Ts> struct selector_helper {
		static inline TT doSelect(Ts &&... params) { return iSelectable<Ts...>::template select<TT>(std::forward<Ts>(params)...); }
	};


}} // boost::database



#endif // BOOST_DATABASE_SELECTABLE_HPP