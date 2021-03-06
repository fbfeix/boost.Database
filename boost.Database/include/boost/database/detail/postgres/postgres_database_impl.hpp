// postgres_database_impl.hpp ----------------------------------------------------//
// -----------------------------------------------------------------------------

// Copyright 2015 Felix Astner

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// -----------------------------------------------------------------------------

// Revision History
// 10-10-2013 dd-mm-yyyy - Initial Release

// -----------------------------------------------------------------------------

#ifndef BOOST_DATABASE_POSTGRES_DATABASE_IMPL_HPP
#define BOOST_DATABASE_POSTGRES_DATABASE_IMPL_HPP

#include <boost/tuple/tuple.hpp>
#include <type_traits>
#include <libpq-fe.h>
#include <boost/math/tools/tuple.hpp>


namespace boost
{
	namespace database
	{
		template<int INDEX, typename TargetType, typename...Ts>
		void insertIntoTuple(boost::tuple<Ts...> &tuple, const std::string& s)
		{
			boost::get<INDEX>(tuple) = boost::lexical_cast<typename TargetType>(s);
		}


		template<int Index>
		struct FieldLoop
		{
			template<typename...Ts>
			static inline void loop(PGresult* res, boost::tuple<Ts...> &tpl)
			{
				
				::boost::tuples::element<Index, boost::tuple<Ts...> >::type;


				//insertIntoTuple<Index, tuple_element<Index, decltype(tpl) >::type, Ts...>(tpl, PQgetvalue(res, 0, Index));
				insertIntoTuple<Index, ::boost::tuples::element<Index, boost::tuple<Ts...> >::type, Ts...>(tpl, std::string(PQgetvalue(res, 0, Index)));

				FieldLoop<Index - 1>::loop<Ts...>(res, tpl);
			}
		};

		template<>
		struct FieldLoop < 0 >
		{
			template<typename...Ts>
			static inline void loop(PGresult* res, boost::tuple<Ts...> &tpl)
			{
				using namespace std::tr1;
				

				insertIntoTuple<0, ::boost::tuples::element<0, boost::tuple<Ts...> >::type, Ts...>(tpl, std::string(PQgetvalue(res, 0, 0)));
				
			}
		};

	}
}

#include <string>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/database/database_error.hpp>
#include <boost/database/connection_attributes.hpp>
#include <utility>
#include <boost/database/detail/apply.h>
#include <boost/move/move.hpp>
#include <boost/database/detail/apply.h>

namespace boost
{
	namespace database
	{

		class postgres_database_impl : private boost::noncopyable
			, public boost::enable_shared_from_this<postgres_database_impl>
		{
		public:
			postgres_database_impl(const ConnectionAttributes& attr)
				: credentials_(attr)
			{

			}	
			
			~postgres_database_impl()
			{
				PQfinish(con_);
			}


			bool launch()
			{
				std::string conStr("host=");
				conStr.append(credentials_.host);
				conStr.append(" port=");
				conStr.append(boost::lexical_cast<std::string>(credentials_.port));
				conStr.append(" dbname=");
				conStr.append(credentials_.db_name);
				conStr.append(" user=");
				conStr.append(credentials_.user);
				conStr.append(" password=");
				conStr.append(credentials_.password);

				con_ = PQconnectdb(conStr.c_str());

				if (PQstatus(con_) != CONNECTION_OK)
				{
					throw boost::database::exception(PQerrorMessage(con_));
				}
			}

			template<typename T, std::size_t fields>
			inline boost::array<std::basic_string<T, std::char_traits<T> >, fields>
				select(const std::string& sql)
			{


				PGresult * res = PQexec(con_, sql.c_str());

				if (PQresultStatus(res) != PGRES_TUPLES_OK)
				{
					PQclear(res);
					throw boost::database::exception(PQerrorMessage(con_));
				}

				if (PQntuples(res) == 1)
				{
					int data_fields = PQnfields(res);

					boost::array<std::basic_string<T, std::char_traits<T> >, fields> out;

					


					for (int i = 0; i < data_fields; i++)
					{
						out[i] = std::basic_string<T, std::char_traits<T>, std::allocator<T> >(
							PQgetvalue(res, 0, i));

						


					}
					
					
					
					PQclear(res);

					return out;
					
				}

				PQclear(res);

				throw boost::database::exception("too mutch data found");
			}

			template<typename T, typename...Ts>
			T select_(const std::string& sql)
			{
				PGresult * res = PQexec(con_, sql.c_str());

				if (PQresultStatus(res) != PGRES_TUPLES_OK)
				{
					PQclear(res);
					throw boost::database::exception(PQerrorMessage(con_));
				}

				if (PQntuples(res) == 1)
				{
					int data_fields = PQnfields(res);

					

					

					typename boost::tuple<Ts...> tpl;
					
					FieldLoop<sizeof...(Ts)-1>::loop<Ts...>(res, tpl);
					


					PQclear(res);

					
					

					return ::database::detail::apply(selector_helper<T, Ts...>::doSelect, tpl);

					
				}

				PQclear(res);

				throw boost::database::exception("too mutch data found");
			}
			
			inline bool insert(const std::string& sql)
			{
				PGresult *res = PQexec(con_, sql.c_str());

				if (PQresultStatus(res) != PGRES_COMMAND_OK)
				{
					PQclear(res);
					return false;
					throw boost::database::exception(PQerrorMessage(con_));					
				}

				PQclear(res);
				return true;

			}

			inline bool deleteData(const std::string& sql)
			{
				PGresult *res = PQexec(con_, sql.c_str());

				if (PQresultStatus(res) != PGRES_COMMAND_OK)
				{
					PQclear(res);
					return false;
					throw boost::database::exception(PQerrorMessage(con_));
				}

				PQclear(res);
				return true;
			}

		
		private:
			PGconn * con_;

			ConnectionAttributes credentials_;
		};

		typedef postgres_database_impl database_impl;
		typedef boost::shared_ptr<postgres_database_impl> DatabaseImpl;

	}
} // boost::database

#endif // BOOST_DATABASE_POSTGRES_DATABASE_IMPL_HPP