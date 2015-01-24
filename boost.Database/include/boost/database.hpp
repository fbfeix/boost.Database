
// database.hpp ----------------------------------------------------//
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

#include <boost/noncopyable.hpp>
#include <boost/database/connection_attributes.hpp>
#include <boost/array.hpp>
#include <string>


#ifdef BOOST_USE_POSTGRES_DATABASE
#include <boost/database/detail/postgres/postgres_database_impl.hpp>
#else
#include <boost/database/detail/postgres/postgres_database_impl.hpp>
#endif


namespace boost
{
	namespace database
	{
		class Database : private boost::noncopyable
		{
		public:
			Database(const ConnectionAttributes& attr)
				: impl_(new database_impl(attr))
			{
				
			}


			bool launch()
			{
				return impl_->launch();
			}


			template<typename T, size_t fields>
			boost::array<std::basic_string<T, std::char_traits<T> >, fields>
				select(const std::string& sql)
			{
				return impl_->select < T, fields >(sql);
			}


			bool insert(const std::string& sql)
			{
				return impl_->insert(sql);
			}

			bool deleteData(const std::string& sql)
			{
				return impl_->deleteData(sql);
			}


		private:
			DatabaseImpl impl_;

		};

	}
} // boost::database

#endif // BOOST_DATABASE_SELECTABLE_HPP

