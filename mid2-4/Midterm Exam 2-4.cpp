#include <iostream>
using std::cout;
using std::endl;

#include <list>
#include "list - 1133317 - mid 2-4.h" // include definition of class template list

template< typename T >
void testList();

template< typename T >
void testResize1();

template< typename T >
void testResize2();

// return true iff left == right
template< typename T >
bool equal( list< T > &left, std::list< T > &right );

int main()
{
   testList< char >();
   testList< short >();
   testList< long >();
   testList< long long >();

   system( "pause" );
}

template< typename T >
void testList()
{
   testResize1< T >();
   testResize2< T >();
   cout << endl;
}

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

template< typename T >
void testResize1()
{
   const int number = 50;
   int numErrors = 0;
   for( int n = 1; n < number; n++ )
      for( int length = 0; length < number; length++ )
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

         list1.resize( length );
         list2.resize( length );

         if( !equal( list1, list2 ) )
            numErrors++;
      }

   cout << "There are " << numErrors << " errors.\n";
}

template< typename T >
void testResize2()
{
   const int number = 50;
   int numErrors = 0;
   for( int n = 0; n < number; n++ )
      for( int length = 0; length < number; length++ )
      {
         list< T > list1( n );

         typename list< T >::iterator it1 = list1.begin();
         for( ; it1 != list1.end(); ++it1 )
            *it1 = 1 + rand() % 99;

         if( !efficientResize( list1, n, length ) )
            numErrors++;
      }

   cout << "There are " << numErrors << " errors.\n";
}

// return true iff the addresses of nodes in list1[ 0 .. minSize ]
// keep unchanged after list1.resize( length )
template< typename T >
bool efficientResize( list< T > &list1, size_t n, size_t length )
{
   size_t minSize = ( n < length ) ? n : length;
   // let k = minSize, and node 1, node 2, ..., node k be the first k nodes of list1.

   ListNode< T > *head1 = *( reinterpret_cast< ListNode< T > ** >( &list1 ) );
   ListNode< T > **addresses;
   addresses = new ListNode< T > *[ minSize + 1 ];
   // p = list1.myData.myHead->next i.e., the address of the first node of list1
   ListNode< T > *p = *( reinterpret_cast< ListNode< T > ** >( head1 ) );
   for( size_t i = 1; i <= minSize; ++i, p = p->next )
      addresses[ i ] = p; // save the address of node i

   // addresses[ i ] is the address of node i before the excution of list1.resize( length ).

   list1.resize( length );

   // p = list1.myData.myHead->next i.e., the address of the first node of list1
   p = *( reinterpret_cast< ListNode< T > ** >( head1 ) );
   for( size_t i = 1; i <= minSize; ++i, p = p->next )
      // p is the address of node i after the excution of list1.resize( length )
      if( addresses[ i ] != p )
         return false;

   // addresses[ i ] == p if and only if
   // node i of list1 before the excution of list1.resize( length ) is the same node as
   // node i of list1 after the excution of list1.resize( length )

   delete[] addresses;

   return true;
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
   
   it1++;
   typename std::list<T>::iterator  it3 = right.begin();
   if (*it1 != *it3)
        return false;

   return true;
}