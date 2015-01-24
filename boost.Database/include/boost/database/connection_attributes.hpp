

// selectable.hpp ----------------------------------------------------//
// -----------------------------------------------------------------------------

// Copyright 2015 Felix Astner

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// -----------------------------------------------------------------------------

// Revision History
// 10-10-2013 dd-mm-yyyy - Initial Release

// -----------------------------------------------------------------------------

#ifndef BOOST_DATABASE_CONNECTION_ATTRIBUTES_HPP
#define BOOST_DATABASE_CONNECTION_ATTRIBUTES_HPP

#include <exception>


namespace boost
{
	namespace database
	{

		struct ConnectionAttributes
		{
			ConnectionAttributes()
			{ }

			ConnectionAttributes(std::string Host,
				unsigned long Port,
				std::string DB_Name,
				std::string User,
				std::string Password)
				: host(Host)
				, port(Port)
				, db_name(DB_Name)
				, user(User)
				, password(Password)
			{ }

			std::string host = "localhost";
			unsigned long port = 5432;
			std::string db_name = "postgres";
			std::string user = "postgres";
			std::string password;
		};

	}
} // boost::database

#endif // BOOST_DATABASE_CONNECTION_ATTRIBUTES_HPP