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



namespace boost
{
namespace database
{
	template<typename T = wchar_t, size_t fields>
	class Selectable
	{
		typedef boost::array < std::basic_string<T, std::char_traits<T> >, fields > SelectArgumentType;

#ifdef BOOST_USE_POSTGRES_DATABASE
		friend class postgres_database_impl
#endif

	public:		
		template<typename... Ts>
		Selectable(const SelectArgumentType&) = 0;

	protected:
		Selectable() {}
	};



	/*
	*/
	class MultiSelectable
	{
	public:
		MultiSelectable(char*...)
		{}
	private:
		MultiSelectable() {}
	};

}} // boost::database

#endif // BOOST_DATABASE_SELECTABLE_HPP