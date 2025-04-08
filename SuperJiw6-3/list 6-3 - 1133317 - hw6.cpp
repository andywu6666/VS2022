// HugeInteger test program.
#include <iostream>
using std::cout;
using std::endl;

#include <list>
#include "list 6-3 - 1133317 - hw6.h" // include definition of class template list

template< typename T >
void testList();

template< typename T >
void testInsert1();

template< typename T >
void testInsert2();

template< typename T >
void testErase1();

template< typename T >
void testErase2();

// return true iff left == right
template< typename T >
bool equal( list< T > &left, std::list< T > &right );

int main()
{
   srand( static_cast< unsigned int >( time( 0 ) ) );

   testList< char >();
   testList< short >();
   testList< long >();
   testList< long long >();

   system( "pause" );
}

template< typename T >
void testList()
{
   testInsert1< T >();
   testInsert2< T >();

   testErase1< T >();
   testErase2< T >();
   cout << endl;
}

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

template< typename T >
void testInsert1()
{
   list< T > list1( 0 );
   std::list< T > list2( 0 );

   typename list< T >::iterator it1 = list1.begin();
   typename std::list< T >::iterator it2 = list2.begin();

   T value = 1 + rand() % 99;
   typename list< T >::iterator rit1 = list1.insert( it1, value );
   typename std::list< T >::iterator rit2 = list2.insert( it2, value );

   int numErrors = 0;
   if( !equal( list1, list2 ) || rit1->myVal != *rit2 )
      numErrors++;

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testInsert2()
{
   const int number = 100;
   int numErrors = 0;
   for( int n = 1; n < number; n++ )
      for( int position = 0; position <= n; position++ )
      {
         list< T > list1( n );
         std::list< T > list2( n );

         typename list< T >::iterator it1 = list1.begin();
         typename std::list< T >::iterator it2 = list2.begin();
         for( ; it2 != list2.end(); it1 = it1->next, ++it2 )
         {
            T value = 1 + rand() % 99;
            it1->myVal = value;
            *it2 = value;
         }

         it1 = list1.begin();
         it2 = list2.begin();
         for( int i = 0; i < position; i++ )
         {
            it1 = it1->next;
            ++it2;
         }

         T value = 1 + rand() % 99;
         typename list< T >::iterator rit1 = list1.insert( it1, value );
         typename std::list< T >::iterator rit2 = list2.insert( it2, value );

         if( !equal( list1, list2 ) || rit1->myVal != *rit2 )
            numErrors++;
      }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testErase1()
{
   int numErrors = 0;
   for( int n = 0; n <= 1; n++ )
   {
      list< T > list1( n );

      typename list< T >::iterator rit1 = list1.erase( list1.begin() );

      if( list1.size() > 0 )
         numErrors++;

      if( rit1 != list1.end() )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testErase2()
{
   const int number = 100;
   int numErrors = 0;
   for( int n = 2; n < number; n++ )
      for( int position = 0; position < n; position++ )
      {
         list< T > list1( n );
         std::list< T > list2( n );

         typename list< T >::iterator it1 = list1.begin();
         typename std::list< T >::iterator it2 = list2.begin();
         for( ; it2 != list2.end(); it1 = it1->next, ++it2 )
         {
            T value = 1 + rand() % 99;
            it1->myVal = value;
            *it2 = value;
         }

         it1 = list1.begin();
         it2 = list2.begin();
         for( int i = 0; i < position; i++ )
         {
            it1 = it1->next;
            ++it2;
         }

         typename list< T >::iterator rit1 = list1.erase( it1 );
         typename std::list< T >::iterator rit2 = list2.erase( it2 );

         if( !equal( list1, list2 ) )
            numErrors++;

         if( rit2 != list2.end() && rit1->myVal != *rit2 )
            numErrors++;

         if( rit2 == list2.end() && rit1 != list1.end() )
            numErrors++;
      }

   cout << "There are " << numErrors << " errors\n";
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
   for( ; it2 != right.end(); it1 = it1->next, ++it2 )
      if( it1->myVal != *it2 )
         return false;

   return true;
}