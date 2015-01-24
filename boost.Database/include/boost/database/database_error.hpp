// database_error.hpp ----------------------------------------------------//
// -----------------------------------------------------------------------------

// Copyright 2015 Felix Astner

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// -----------------------------------------------------------------------------

// Revision History
// 10-10-2013 dd-mm-yyyy - Initial Release

// -----------------------------------------------------------------------------

#ifndef BOOST_DATABASE_DATABASE_ERROR_HPP
#define BOOST_DATABASE_DATABASE_ERROR_HPP

#include <exception>
#include <string>

namespace boost
{
	namespace database
	{

		class exception
			: public std::exception
		{
		public:

			exception(const std::string& what)
				: std::exception(what.c_str())
			{}
		};

	}
} // boost::database

#endif // BOOST_DATABASE_DATABASE_ERROR_HPP