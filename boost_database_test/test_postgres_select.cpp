#define BOOST_USE_POSTGRES_DATABASE      


#include "stdafx.h"

#include <boost/database.hpp>
#include <boost/foreach.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE( test_postgres_select )  
{
    
	boost::database::ConnectionAttributes attr;

	attr.port = 5433;
	attr.db_name = "credentials_tbl";
	attr.password = "password";

	boost::database::Database db(attr);

	db.launch();

	auto result = db.select<char, 3>("select id, email, name from credentials_tbl limit 1");

	BOOST_FOREACH(auto it, result)
	{
		std::cout << it << std::endl;
	}

}

