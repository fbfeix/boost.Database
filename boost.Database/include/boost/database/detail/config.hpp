
#ifndef BOOST_DATABASE_CONFIG_HPP
#define BOOST_DATABASE_CONFIG_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_DECLSPEC // defined in config system
// we need to import/export our code only if the user has specifically
// asked for it by defining either BOOST_ALL_DYN_LINK if they want all boost
// libraries to be dynamically linked, or BOOST_DATABASE_DYN_LINK
// if they want just this one to be dynamically liked:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_DATABASE_DYN_LINK)
// export if this is our own source, otherwise import:
#ifdef BOOST_DATABASE_SOURCE
# define BOOST_DATABASE_DECL __declspec(dllexport)
#else
# define BOOST_DATABASE_DECL __declspec(dllimport)
#endif  // BOOST_DATABASE_SOURCE
#endif  // DYN_LINK
#endif  // BOOST_HAS_DECLSPEC

// if BOOST_DATABASE_DECL isn't defined yet define it now:
#ifndef BOOST_DATABASE_DECL
#define BOOST_DATABASE_DECL
#endif


#endif // BOOST_FILESYSTEM_CONFIG_HPP