// Date.cpp
// Member-function definitions for class Date.

#include <iomanip>
using namespace std;

#include "Date.h"

extern bool leapYear( int year );

Date::Date()
{
   year = 2000;
   month = 0;
   day = 0;
}

void Date::setDate( Date date )
{
   setYear( date.year );
   setMonth( date.month );
   setDay( date.day );
}

void Date::setYear( int y )
{
   year = ( y >= 2000 ) ? y : 2000;
}

void Date::setMonth( int m )
{
   month = ( m <= 12 && m >= 1 ) ? m : 1;
}

void Date::setDay( int d )
{
   int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if( month == 2 && leapYear( year ) )
      day = ( d <= 29 && d >= 1 ) ? d : 1;
   else
      day = ( d <= days[ month ] && d >= 1 ) ? d : 1;
}

int Date::getYear() const
{
   return year;
}

int Date::getMonth() const
{
   return month;
}

int Date::getDay() const
{
   return day;
}

bool Date::operator==( const Date &date2 )
{
   return ( year == date2.year && month == date2.month && day == date2.day );
}

bool Date::operator<( const Date &date2 )
{
   if( year < date2.year )
      return true;
   if( year > date2.year )
      return false;

   if( month < date2.month )
      return true;
   if( month > date2.month )
      return false;

   if( day < date2.day )
      return true;

   return false;
}

bool Date::operator<=( const Date &date2 )
{
   return ( *this < date2 ) || ( *this == date2 );
}

Date Date::operator+( int numDays )
{
   int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   if( leapYear( year ) )
      days[ 2 ] = 29;

   Date date( *this );
   date.day += numDays;






   return date; // reference return to create an lvalue
}

// overloaded output operator
ostream& operator<<( ostream &output, const Date &d )
{
   output << setfill( '0' ) << d.year << "/" << setw( 2 ) << d.month
      << '/' << setw( 2 ) << d.day;
   output << setfill( ' ' );
   return output; // enables cascading
} // end function operator<<