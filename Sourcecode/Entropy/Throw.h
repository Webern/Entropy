// Copyright (c) Matthew James Briggs

#pragma once

#include <string>
#include <exception>

// --------------------------------------------------------------
// These macros provide an easy way to throw a std::runtime_error
// which includes file name, function name, and line number.  For
// example, the following call
// ENTROPY_THROW( "this is my message" );
// will throw a std::runtime_error with the message:
//     "error Throw.h (7) someFunctionName: 'this is my message'"
//
// If you want to check and throw if a pointer (or smart pointer)
// is null then use ENTROPY_THROW_IF_NULL( myPtr );
// --------------------------------------------------------------

#ifndef __FILENAME__

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

        #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

    #else

        #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

    #endif

#endif

#ifndef ENTROPY_THROW
#define ENTROPY_THROW(throw_error_message)               \
throw std::runtime_error (                               \
std::string( "error " )                                  \
+ std::string( __FILENAME__ )                            \
+ std::string(" (")                                      \
+ std::string( std::to_string(__LINE__ ) )               \
+ std::string(") ")                                      \
+ std::string( __FUNCTION__ )                            \
+ std::string(": '")                                     \
+ std::string( throw_error_message )                     \
+ std::string( "'" ) );
#endif

#define ENTROPY_ASSERT(expectedTrueStatement)                           \
    if ( ! (expectedTrueStatement) )                                    \
    {                                                                   \
        ENTROPY_THROW("assertion failed '" #expectedTrueStatement "'"); \
    }
