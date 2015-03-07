     


#include "stdafx.h"

#define BOOST_USE_POSTGRES_DATABASE 

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

#include <boost/database.hpp>
#include <boost/uuid/uuid_io.hpp>

class User : public boost::database::iSelectable < boost::uuids::uuid, std::string, std::string >
{
public:

	User(boost::uuids::uuid id, const std::string& name, const std::string& surname)
	{
		std::cout << id << ", ";
		std::cout << name << ", ";
		std::cout << surname << std::endl;
	}
};




BOOST_AUTO_TEST_CASE(test_postgfgres_select)
{

	boost::database::ConnectionAttributes attr;

	attr.port = 5433;
	attr.db_name = "credentials_tbl";
	attr.password = "password";

	boost::database::Database db(attr);

	db.launch();

	//auto result = db.select<char, 3>("select id, email, name from credentials_tbl limit 1");

	for (int i = 0; i < 100; i++)
	{

		User result = db.select_ < User, boost::uuids::uuid, std::string, std::string >
			("select id, email, name from credentials_tbl limit 1");
	}
	
	

}