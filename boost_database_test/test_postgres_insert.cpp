
#include "stdafx.h"

#define BOOST_USE_POSTGRES_DATABASE


#include <boost/database.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

BOOST_AUTO_TEST_CASE( test_postgres_insert )  
{
	boost::database::ConnectionAttributes attr;

	attr.port = 5433;
	attr.db_name = "credentials_tbl";
	attr.password = "password";

	boost::database::Database db(attr);

	db.launch();

	

	for (int i = 0; i < 10; i++)
	{
		std::string sql;

		boost::uuids::uuid id = boost::uuids::random_generator()();

		sql = "INSERT INTO credentials_tbl(id, email, name, password) ";
		sql += "VALUES('";
		sql += boost::lexical_cast<std::string>(id);
		sql += "', 'example";
		sql += boost::lexical_cast<std::string>(i);
		sql += "@email.org', 'max";
		sql += boost::lexical_cast<std::string>(i);
		sql += "', 'pw'); ";


		BOOST_CHECK(db.insert(sql));
	}


}

