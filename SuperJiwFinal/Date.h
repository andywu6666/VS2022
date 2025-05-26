// Date.h
// Date class definition.
#ifndef DATA_H
#define DATA_H

#include <ostream>
using std::ostream;

class Date
{
   friend ostream& operator<<( ostream &, const Date & );
public:
   Date();
   void setDate( Date );
   void setYear( int );
   void setMonth( int );
   void setDay( int );
   int getYear() const;
   int getMonth() const;
   int getDay() const;
   bool operator==( const Date &date2 );
   bool operator<( const Date &date2 );
   bool operator<=( const Date &date2 );
   Date operator+( int numDays ); // returns current date + numDays
private:
	int year;
	int month;
   int day;
};

#endif // DATA_H