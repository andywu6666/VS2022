// Date.cpp
// Member-function definitions for class Date.
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
#include "Date.h"

extern bool leapYear( int year );

Date::Date()
{
   year = 2000;
   month = 0;
   day = 0;
}

void Date::setYear( int y )
{
   year = ( y >= 2000 ) ? y : 2000; // sets year
}

void Date::setMonth( int m )
{
   month = ( m <= 12 && m >= 1 ) ? m : 1; // sets month
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

bool Date::operator>=( const Date &date2 )
{
   return !( *this < date2 );
}

// return *this - date2 provided that *this > date2
int Date::operator-( const Date &date2 )
{
    tm tm1 = { 0 };
    tm1.tm_year = this->year - 1900;
    tm1.tm_mon = this->month - 1;
    tm1.tm_mday = this->day;
    tm1.tm_hour = 12;
    tm1.tm_isdst = -1;

    tm tm2 = { 0 };
    tm2.tm_year = date2.year -1900;
    tm2.tm_mon = date2.month - 1;
    tm2.tm_mday = date2.day;
    tm2.tm_hour = 12;
    tm2.tm_isdst = -1;

    time_t time_t1 = mktime(&tm1);
    time_t time_t2 = mktime(&tm2);

    double differ_second = difftime(time_t1, time_t2);
    return static_cast<int>( differ_second / 24 * 60 * 60 );

    

   


}