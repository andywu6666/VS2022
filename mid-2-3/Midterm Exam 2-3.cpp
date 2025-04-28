#include <iostream>
using std::cout;
using std::endl;

#include <list>
#include "list - 1133317 - mid 2-3.h" // include definition of class template list

template< typename T >
void testPushBack();

// return true iff left == right
template< typename T >
bool equal( list< T > &left, std::list< T > &right );

int main()
{
   testPushBack< char >();
   testPushBack< short >();
   testPushBack< long >();
   testPushBack< long long >();

   system( "pause" );
}

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

template< typename T >
void testPushBack()
{
   const int number = 500;
   int numErrors = 0;
   for( int n = 0; n < number; n++ )
   {
      list< T > list1( n );
      std::list< T > list2( n );

      typename list< T >::iterator it1 = list1.begin();
      typename std::list< T >::iterator it2 = list2.begin();
      for( ; it2 != list2.end(); ++it1, ++it2 )
      {
         T value = 1 + rand() % 99;
         *it1 = value;
         *it2 = value;
      }

      T value = 1 + rand() % 99;
      list1.push_back( value );
      list2.push_back( value );

      if( !equal( list1, list2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n\n";
}

// return true iff left == right
template< typename T >
bool equal( list< T > &left, std::list< T > &right )
{
   if( left.size() != right.size() ) // different number of elements
      return false;

   if( right.size() == 0 )
      return true;

   typename list< T >::iterator it1 = left.begin();
   typename std::list< T >::iterator it2 = right.begin();
   for( ; it2 != right.end(); ++it1, ++it2 )
      if( *it1 != *it2 )
         return false;

   return true;
}