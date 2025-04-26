// 10083 - Division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

const int maxSize = 200;

template< typename BidIt >
class ReverseIterator // wrap iterator to run it backwards
{
public:
   using value_type = typename BidIt::value_type;
   using difference_type = typename BidIt::difference_type;
   using pointer = typename BidIt::pointer;
   using reference = typename BidIt::reference;

   // construct with value-initialized wrapped iterator
   ReverseIterator() = default;

   // construct wrapped iterator from right
   explicit ReverseIterator( BidIt right )
      : current( right )
   {
   }

   template< typename other >
   ReverseIterator( const ReverseIterator< other > &right )
      : current( right.current ) // initialize with compatible base
   {
   }

   // assign from compatible base
   template< typename other >
   ReverseIterator& operator=( const ReverseIterator< other > &right )
   {
      current = right.current;
      return *this;
   }

   BidIt base() const // return wrapped iterator
   {
      return current;
   }

   reference operator*() const // return designated value
   {
      BidIt tmp = current;
      return *--tmp;
   }

   pointer operator->() const // return pointer to class object
   {
      BidIt tmp = current;
      --tmp;
      return tmp.operator->();
   }

   ReverseIterator& operator++() // preincrement
   {
      --current;
      return *this;
   }

   ReverseIterator operator++( int ) // postincrement
   {
      ReverseIterator tmp = *this;
      --current;
      return tmp;
   }

   ReverseIterator& operator--()	// predecrement
   {
      ++current;
      return *this;
   }

   ReverseIterator operator--( int ) // postdecrement
   {
      ReverseIterator tmp = *this;
      ++current;
      return tmp;
   }

   // increment by integer
   ReverseIterator& operator+=( const difference_type off )
   {
      current -= off;
      return *this;
   }

   // return this + integer
   ReverseIterator operator+( const difference_type off ) const
   {
      return ReverseIterator( current - off );
   }

   // decrement by integer
   ReverseIterator& operator-=( const difference_type off )
   {
      current += off;
      return *this;
   }

   // return this - integer
   ReverseIterator operator-( const difference_type off ) const
   {
      return ReverseIterator( current + off );
   }

   // subscript
   reference operator[]( const difference_type off ) const
   {
      return current[ static_cast< difference_type >( -off - 1 ) ];
   }

protected:
   BidIt current{}; // the wrapped iterator
};

template< typename BidIt1, typename BidIt2 >
bool operator==( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return left.base() == right.base();
}

template< typename BidIt1, typename BidIt2 >
bool operator!=( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return !( left == right );
}

template< typename BidIt1, typename BidIt2 >
bool operator<( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return right.base() < left.base();
}

template< typename BidIt1, typename BidIt2 >
bool operator>( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return right < left;
}

template< typename BidIt1, typename BidIt2 >
bool operator<=( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return !( right < left );
}

template< typename BidIt1, typename BidIt2 >
bool operator>=( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return !( left < right );
}


// CLASS TEMPLATE VectorConstIterator
template< typename MyVec >
class VectorConstIterator
{
public:
   using value_type = typename MyVec::value_type;
   using difference_type = typename MyVec::difference_type;
   using pointer = typename MyVec::const_pointer;
   using reference = const value_type &;
   using TPtr = typename MyVec::pointer;

   VectorConstIterator()
      : ptr()
   {
   }

   VectorConstIterator( TPtr parg )
      : ptr( parg )
   {
   }

   reference operator*() const
   {
      return *ptr;
   }

   pointer operator->() const
   {
      return ptr;
   }

   VectorConstIterator& operator++()
   {
      ++ptr;
      return *this;
   }

   VectorConstIterator operator++( int )
   {
      VectorConstIterator temp = *this;
      ++ *this;
      return temp;
   }

   VectorConstIterator& operator--()
   {
      --ptr;
      return *this;
   }

   VectorConstIterator operator--( int )
   {
      VectorConstIterator temp = *this;
      -- *this;
      return temp;
   }

   VectorConstIterator& operator+=( const difference_type off )
   {
      ptr += off;
      return *this;
   }

   VectorConstIterator operator+( const difference_type off ) const
   {
      VectorConstIterator temp = *this;
      return temp += off;
   }

   VectorConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   VectorConstIterator operator-( const difference_type off ) const
   {
      VectorConstIterator temp = *this;
      return temp -= off;
   }

   difference_type operator-( const VectorConstIterator &right ) const
   {
      return ptr - right.ptr;
   }

   reference operator[]( const difference_type off ) const
   {
      return *( *this + off );
   }

   bool operator==( const VectorConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VectorConstIterator &right ) const
   {
      return !( *this == right );
   }

   bool operator<( const VectorConstIterator &right ) const
   {
      return ptr < right.ptr;
   }

   bool operator>( const VectorConstIterator &right ) const
   {
      return right < *this;
   }

   bool operator<=( const VectorConstIterator &right ) const
   {
      return !( right < *this );
   }

   bool operator>=( const VectorConstIterator &right ) const
   {
      return !( *this < right );
   }

   TPtr ptr; // pointer to element in vector
};


// CLASS TEMPLATE VectorIterator
template< typename MyVec >
class VectorIterator
{
public:
   using value_type = typename MyVec::value_type;
   using difference_type = typename MyVec::difference_type;
   using pointer = typename MyVec::const_pointer;
   using reference = value_type &;
   using TPtr = typename MyVec::pointer;

   VectorIterator()
      : ptr()
   {
   }

   VectorIterator( TPtr parg )
      : ptr( parg )
   {
   }

   reference operator*() const
   {
      return *ptr;
   }

   pointer operator->() const
   {
      return ptr;
   }

   VectorIterator& operator++()
   {
      ++ptr;
      return *this;
   }

   VectorIterator operator++( int )
   {
      VectorIterator temp = *this;
      ++ *this;
      return temp;
   }

   VectorIterator& operator--()
   {
      --ptr;
      return *this;
   }

   VectorIterator operator--( int )
   {
      VectorIterator temp = *this;
      -- *this;
      return temp;
   }

   VectorIterator& operator+=( const difference_type off )
   {
      ptr += off;
      return *this;
   }

   VectorIterator operator+( const difference_type off ) const
   {
      VectorIterator temp = *this;
      return temp += off;
   }

   VectorIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   VectorIterator operator-( const difference_type off ) const
   {
      VectorIterator temp = *this;
      return temp -= off;
   }

   difference_type operator-( const VectorIterator &right ) const
   {
      return ptr - right.ptr;
   }

   reference operator[]( const difference_type off ) const
   {
      return *( *this + off );
   }

   bool operator==( const VectorIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VectorIterator &right ) const
   {
      return !( *this == right );
   }

   bool operator<( const VectorIterator &right ) const
   {
      return ptr < right.ptr;
   }

   bool operator>( const VectorIterator &right ) const
   {
      return right < *this;
   }

   bool operator<=( const VectorIterator &right ) const
   {
      return !( right < *this );
   }

   bool operator>=( const VectorIterator &right ) const
   {
      return !( *this < right );
   }

   TPtr ptr; // pointer to element in vector
};


// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
   using value_type = ValueType;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   VectorVal()
      : myFirst(),
        myLast(),
        myEnd()
   {
   }

   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
   using value_type = Ty;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = Ty &;
   using const_reference = const Ty &;
   using size_type = size_t;
   using difference_type = ptrdiff_t;

private:
   using ScaryVal = VectorVal< Ty >;

public:
   using iterator = VectorIterator< ScaryVal >;
   using const_iterator = VectorConstIterator< ScaryVal >;
   using reverse_iterator = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

   vector()
      : myData()
   {
   }

   vector( const size_type count )
      : myData()
   {
      if( count != 0 )
      {
         myData.myFirst = new value_type[ count ]();
         myData.myLast = myData.myFirst + count;
         myData.myEnd = myData.myFirst + count;
      }
      myData.myFirst = myData.myLast = myData.myEnd = nullptr;
   }

   vector( const vector &right )
      : myData()
   {
       size_type size = right.myData.myLast - right.myData.myFirst; //size = right.myData.myLast - right.myData.myFirst
       if (size != 0) //size
       {
           myData.myFirst = new value_type[size];
           for (int i = 0; i < size; i++) {
               myData.myFirst[i] = right.myData.myFirst[i];
           }
           myData.myLast = myData.myFirst + size;
           myData.myEnd = myData.myFirst + size;
       }
       myData.myFirst = myData.myLast = myData.myEnd = nullptr;

   }

   ~vector()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   iterator insert( const_iterator where, const Ty &val )
   {
       if (where < myData.myFirst || where > myData.myLast)
           return nullptr;

       size_type pos = where - myData.myFirst;
       size_type originalSize = size();
       size_type originalCapacity = capacity();
       if (originalSize == originalCapacity)
       {
           size_type newCapacity;
           if (originalCapacity <= 1)
               newCapacity = originalCapacity + 1;
           else
               newCapacity = originalCapacity * 3 / 2;

           pointer newArray = new value_type[newCapacity]();

           for (size_type i = 0; i < pos; i++)
           {
               newArray[i] = myData.myFirst[i];
           }

           newArray[pos] = val;

           for (size_type j = pos; j < originalSize; j++)
           {
               newArray[j + 1] = myData.myFirst[j];
           }

           delete[] myData.myFirst;

           myData.myFirst = newArray;
           myData.myLast = newArray + originalSize + 1;
           myData.myEnd = newArray + newCapacity;

           return myData.myFirst + pos;
       }
       else
       {
           for (size_type i = originalSize; i > pos; i--)
           {
               myData.myFirst[i] = myData.myFirst[i - 1];
           }

           myData.myFirst[pos] = val;
           myData.myLast++;

           return myData.myFirst + pos;


       }
   }

   vector& operator=( const vector &right )
   {
       if (this != &right) // avoid self-assignment
       {
           size_type rightSize = right.size();
           if (rightSize > capacity())
           {
               if (capacity() > 0)
                   delete[] myData.myFirst; // release space

               size_type newCapacity = capacity() * 3 / 2;
               if (newCapacity < rightSize)
                   newCapacity = rightSize;

               myData.myFirst = new value_type[newCapacity]();
               myData.myEnd = myData.myFirst + newCapacity;

           }

           for (size_type i = 0; i < rightSize; i++)
           {
               myData.myFirst[i] = right.myData.myFirst[i];
           }
           myData.myLast = myData.myFirst + rightSize;

       }

       return *this; // enables x = y = z, for example
   }

   iterator erase( const_iterator where )
   {
       if (where < myData.myFirst || where >= myData.myLast)
           return nullptr;

       size_type pos = where - myData.myFirst;
       size_type originalSize = size();
       for (size_type i = pos; i < originalSize; i++)
       {
           myData.myFirst[i] = myData.myFirst[i + 1];
       }
       myData.myLast--;

       // return const_cast< iterator >( where );
       return myData.myFirst + pos;
   }

   void clear()
   {
      myData.myLast = myData.myFirst;
   }

   iterator begin()
   {
      return iterator( myData.myFirst );
   }

   const_iterator begin() const
   {
      return const_iterator( myData.myFirst );
   }

   iterator end()
   {
      return iterator( myData.myLast );
   }

   const_iterator end() const
   {
      return const_iterator( myData.myLast );
   }

   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   const_reverse_iterator rbegin() const
   {
      return const_reverse_iterator( end() );
   }

   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   const_reverse_iterator rend() const
   {
      return const_reverse_iterator( begin() );
   }

   const_iterator cbegin() const
   {
      return begin();
   }

   const_iterator cend() const
   {
      return end();
   }

   const_reverse_iterator crbegin() const
   {
      return rbegin();
   }

   const_reverse_iterator crend() const
   {
      return rend();
   }

   bool empty() const
   {
      return myData.myFirst == myData.myLast;
   }

   size_type size() const
   {
      return static_cast< size_type >( myData.myLast - myData.myFirst );
   }

   size_type capacity() const
   {
      return static_cast< size_type >( myData.myEnd - myData.myFirst );
   }

   value_type& front()
   {
      return *myData.myFirst;
   }

   const value_type& front() const
   {
      return *myData.myFirst;
   }

   value_type& back()
   {
      return myData.myLast[ -1 ];
   }

   const value_type& back() const
   {
      return myData.myLast[ -1 ];
   }

private:

   ScaryVal myData;
};

template< typename Ty >
bool operator==( const vector< Ty > &left, const vector< Ty > &right )
{
    if (left.size() != right.size())
        return false;
        
    for (int i = 0; i < left.size(); i++)
    {
        if ( *(left.begin() + i) != *(right.begin() + i) )
            return false;
    }
    return true;
}

template< typename Ty >
bool operator!=( const vector< Ty > &left, const vector< Ty > &right )
{
   return !( left == right );
}

// CLASS TEMPLATE ListConstIterator
template< typename MyList >
class ListConstIterator
{
public:
   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::const_pointer;
   using reference = const value_type &;

   ListConstIterator()
      : ptr()
   {
   }

   ListConstIterator( nodePtr pNode )
      : ptr( pNode )
   {
   }

   reference operator*() const
   {
      return ptr->myVal;
   }

   ListConstIterator& operator++()
   {
      ptr = ptr->next;
      return *this;
   }

   ListConstIterator operator++( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->next;
      return temp;
   }

   ListConstIterator& operator--()
   {
      ptr = ptr->prev;
      return *this;
   }

   ListConstIterator operator--( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->prev;
      return temp;
   }

   bool operator==( const ListConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ListConstIterator &right ) const
   {
      return !( *this == right );
   }

   nodePtr ptr; // pointer to node
};


// CLASS TEMPLATE ListIterator
template< typename MyList >
class ListIterator
{
public:
   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::const_pointer;
   using reference = value_type &;

   ListIterator()
      : ptr()
   {
   }

   ListIterator( nodePtr pNode )
      : ptr( pNode )
   {
   }

   reference operator*() const
   {
      return ptr->myVal;
   }

   ListIterator& operator++()
   {
      ptr = ptr->next;
      return *this;
   }

   ListIterator operator++( int )
   {
      ListIterator temp = *this;
      ptr = ptr->next;
      return temp;
   }

   ListIterator& operator--()
   {
      ptr = ptr->prev;
      return *this;
   }

   ListIterator operator--( int )
   {
      ListIterator temp = *this;
      ptr = ptr->prev;
      return temp;
   }

   bool operator==( const ListIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ListIterator &right ) const
   {
      return !( *this == right );
   }

   nodePtr ptr; // pointer to node
};

template< typename ValueType >
struct ListNode // list node
{
   using nodePtr = ListNode *;

   nodePtr next; // successor node, or first element if head
   nodePtr prev; // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
        mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = ListIterator< ScaryVal >;
   using const_iterator = ListConstIterator< ScaryVal >;
   using reverse_iterator = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.mySize = count;
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      for (int i = 0; i < count; i++) {
          nodePtr newNode = new node;
          newNode->myVal = Ty();

          newNode->prev = myData.myHead->prev;
          newNode->next = myData.myHead;
          myData.myHead->prev->next = newNode;
          myData.myHead->prev = newNode->prev;
      }

   }

   list( const list &right )
      : myData()
   {
       myData.myHead = new node;
       myData.myHead->myVal = Ty();
       myData.myHead->prev = myData.myHead->next = myData.myHead;

       typename Ty::iterator it = right.begin();
       for (; it != right.end(); it = it->next) {
           nodePtr newNode = new node;
           newNode->myVal = it->myVal;

           newNode->prev = myData.myHead->prev;
           newNode->next = myData.myHead;
           myData.myHead->prev->next = newNode;
           myData.myHead->prev = newNode->prev;
       }


   }

   ~list()
   {
      clear();
      delete myData.myHead;
   }

   list& operator=( const list &right )
   {
      if( this != &right )
      {
          if (right.myData.mySize == 0)
          {
              if (myData.mySize != 0)
                  clear();
          }
          iterator leftIt = this->begin();
          const_iterator rightIt = right.begin();

          while (leftIt != this->end() && rightIt != right.end()) {
              leftIt->myVal = rightIt->myVal;
              leftIt = leftIt->next;
              rightIt = right->next;
          }
          
          if (rightIt != right.end())
          {
              while (rightIt != right.end())
              {
                  nodePtr newNode = new node;
                  newNode->myVal = rightIt->myVal;
                  newNode->prev = myData.myHead->prev;
                  newNode->next = myData.myHead;
                  myData.myHead->prev->next = newNode;
                  myData.myHead->prev = newNode;

                  rightIt = rightIt->next;
              }
          }
          else if (leftIt != this->end())
          {
              nodePtr LastToKeep = leftIt->prev;

              while (leftIt != this->end())
              {
                  nodePtr nodeToDelete = leftIt;
                  leftIt = leftIt->next;
                  delete[]nodeToDelete;
              }
              LastToKeep->next = myData.myHead;
              myData.myHead->prev = LastToKeep;
          }
          myData.mySize = right.myData.mySize;

      }

      return *this;
   }

   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   iterator end()
   {
      return iterator( myData.myHead );
   }

   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   const_reverse_iterator rbegin() const
   {
      return const_reverse_iterator( end() );
   }

   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   const_reverse_iterator rend() const
   {
      return const_reverse_iterator( begin() );
   }

   const_iterator cbegin() const
   {
      return begin();
   }

   const_iterator cend() const
   {
      return end();
   }

   const_reverse_iterator crbegin() const
   {
      return rbegin();
   }

   const_reverse_iterator crend() const
   {
      return rend();
   }

   size_type size() const
   {
      return myData.mySize;
   }

   bool empty() const
   {
      return myData.mySize == 0;
   }

   reference front()
   {
      return myData.myHead->next->myVal;
   }

   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   iterator insert( const_iterator where, const Ty &val ) // insert val at where
   {
       nodePtr newNode = new node;
       newNode->myVal = val;

       nodePtr whereNode = const_cast<nodePtr>(where); //nodePtr
       nodePtr prevNode = whereNode->prev;

       newNode->next = whereNode;
       newNode->prev = prevNode;
       prevNode->next = newNode;
       whereNode->prev = newNode;

       myData.mySize++;

       return iterator(newNode);
   }

   iterator erase( const_iterator where )
   {
       nodePtr whereNode = const_cast<nodePtr>(where); //nodePtr
       nodePtr prevNode = whereNode->prev;
       nodePtr nextNode = whereNode->next;

       prevNode->next = nextNode;
       nextNode->prev = prevNode;

       delete[] whereNode;
       myData.mySize--;

       return iterator(nextNode);
   }

   void clear()
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
          while (myData.myHead->next != myData.myHead)
          {
              myData.myHead->next = myData.myHead->next->next;
              delete[] myData.myHead->next->prev;
        }
          myData.myHead->prev = myData.myHead;
          myData.mySize = 0;

      }
   }

private:
   ScaryVal myData;
};

template< typename Ty >
bool operator==( const list< Ty > &left, const list< Ty > &right )
{
    if (left.size() != right.size())
        return false;

    typename list<Ty>::const_iterator it1 = left.begin();
    typename list<Ty>::const_iterator it2 = right.begin();

    for (; it1 != left.end() ; it1 = it1->next, it2 = it2->next)
    {
        if (it1->myVal != it2->myVal)
            return false;
    }
    return true;


}

template< typename Ty >
bool operator!=( const list< Ty > &left, const list< Ty > &right )
{
   return !( left == right );
}


template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type;
 
   // constructor; construct a zero HugeInteger with size n
   HugeInteger( size_t n = 0 )
      : integer( ( n > 0 ) ? n : 1 )
   {
   }

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy )
      : integer( integerToCopy.integer )
   {
   }

   // destructor; destroys the HugeInteger
   ~HugeInteger()
   {
   }

   // overloaded assignment operator;
   // return avoids: ( a1 = a2 ) = a3
   const HugeInteger& operator=( const HugeInteger &right )
   {
      if( &right != this ) // avoid self-assignment
         integer = right.integer;

      return *this; // enables x = y = z, for example
   }

   // function that tests if two HugeIntegers are equal
   bool operator==( const HugeInteger &right )
   {
      return ( integer == right.integer );
   }

   // function that tests if one HugeInteger is less than another
   bool operator<( HugeInteger &right )
   {
       if (integer.size() != right.integer.size())
           return integer.size() < right.integer.size();

       typename T::const_iterator it1 = integer.cend() - 1;
       typename T::const_iterator it2 = right.integer.cend() - 1;
       for (; it1 >= integer.cbegin(); --it1, --it2)
       {
           if (*it1 != *it2)
               return *it1 < *it2;
       }
       return false;


   }

   // function that tests if one HugeInteger is less than or equal to another
   bool operator<=( HugeInteger &right )
   {
      return ( *this == right || *this < right );
   }

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( const HugeInteger &op2 )
   {
       HugeInteger zero;
       if (*this == op2)
           return zero;

       HugeInteger difference(*this);
       typename T::iterator it1 = difference.integer.begin();
       typename T::const_iterator it2 = op2.integer.begin();
       int borrow = 0;
       for (; it1 != difference.integer.end(); ++it1)
       {
           int digit1 = *it1;
           int digit2 = (it2 != op2.integer.end()) ? *it2 : 0;
           int diff = digit1 - digit2 - borrow;
           if (diff < 0)
           {
               diff += 10;
               borrow = 1;
           }
           else
               borrow = 0;
           *it1 = diff;
           if (it2 != op2.integer.end())
               ++it2;
       }

       while (difference.integer.size() > 1 && *(difference.integer.end() - 1) == 0)
           difference.integer.erase(difference.integer.cend() - 1);



       if (difference.leadingZero())
           cout << "difference has a leading zero!\n";

       return difference;
   }

   // subtraction assignment operator; HugeInteger -= HugeInteger
   void operator-=( HugeInteger &op2 )
   {
      *this = *this - op2;
   }

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( HugeInteger &op2 )
   {
       HugeInteger zero;
       if (isZero() || op2.isZero())
           return zero;

       // 複製兩個操作數
       HugeInteger A(*this), B(op2);

       // 位數
       size_type n1 = A.integer.size();
       size_type n2 = B.integer.size();

       // 結果長度 = n1 + n2
       HugeInteger product(static_cast<unsigned int>(n1 + n2));

       // 2) 雙重迴圈：A 的第 i 位 * B 的第 j 位，累加到 product[i+j]
       for (size_type i = 0; i < n1; ++i) {
           for (size_type j = 0; j < n2; ++j) {
               // 用 iterator 訪問
               typename T::iterator itA = A.integer.begin() + i;
               typename T::iterator itB = B.integer.begin() + j;
               typename T::iterator itP = product.integer.begin() + (i + j);
               *itP += (*itA) * (*itB);
           }
       }

       // 3) 統一處理進位
       for (size_type k = 0; k < n1 + n2 - 1; ++k) {
           typename T::iterator itP = product.integer.begin() + k;
           if (*itP >= 10) {
               *(itP + 1) += *itP / 10;
               *itP %= 10;
           }
       }

       // 4) 刪除末端多餘的零
       while (product.integer.size() > 1 && *(product.integer.end() - 1) == 0)
           product.integer.erase(product.integer.cend() - 1);

       if (product.leadingZero())
           cout << "product has a leading zero!\n";

       return product;
   }

   // multiplication assignment operator; HugeInteger *= HugeInteger
   void operator*=( HugeInteger &op2 )
   {
      *this = *this * op2;
   }

   // division operator; HugeInteger / HugeInteger
   // provided that the op2 is not equal to 0
   HugeInteger operator/( HugeInteger &op2 )
   {
       HugeInteger zero;
       if (*this < op2)
           return zero;

       HugeInteger dividend(*this);
       HugeInteger divisor(op2);
       HugeInteger remainder = dividend;

       size_type dividendSize = dividend.integer.size();
       size_type divisorSize = divisor.integer.size();

       int shift = static_cast<int>(dividendSize) - static_cast<int>(divisorSize);

       HugeInteger buffer(divisor);
       for (int i = 0; i < shift; ++i)
           buffer.integer.insert(buffer.integer.cbegin(), 0);

       int quotientSize;
       if (dividend < buffer) {
           buffer.integer.erase(buffer.integer.cbegin());
           quotientSize = shift;
       }
       else {
           quotientSize = shift + 1;
       }

       HugeInteger quotient(static_cast<unsigned int>(quotientSize));
       typename T::iterator quotPtr = quotient.integer.begin();

       for (int k = quotientSize - 1; k >= 0; --k) {
           while (!(remainder < buffer)) {
               remainder = remainder - buffer;
               quotPtr[k]++;
               if (remainder.isZero())
                   return quotient;
           }

           buffer.integer.erase(buffer.integer.cbegin());
       }
       return quotient;
   }

   // modulus operator; HugeInteger % HugeInteger
   // provided that the op2 is not equal to 0
   HugeInteger operator%( HugeInteger &op2 )
   {
      return *this - ( ( *this / op2 ) * op2 );
   }

   HugeInteger& operator++() // prefix increment operator
   {
      helpIncrement(); // increment integer
      return *this; // reference return to create an lvalue
   }

   // overloaded postfix increment operator;
   // note that the dummy integer parameter does not have a parameter name
   HugeInteger operator++( int )
   {
      HugeInteger temp = *this; // hold current state of object
      helpIncrement();

      // return unincremented, saved, temporary object
      return temp; // value return; not a reference return
   }

   // overloaded prefix decrement operator 
   HugeInteger& operator--()
   {
      helpDecrement(); // increment integer
      return *this; // reference return to create an lvalue
   }

   // overloaded postfix decrement operator;
   // note that the dummy integer parameter does not have a parameter name
   HugeInteger operator--( int )
   {
      HugeInteger temp = *this; // hold current state of object
      helpDecrement();

      // return unincremented, saved, temporary object
      return temp; // value return; not a reference return
   }

   // convert an integer into a HugeInteger
   void convert( const value_type &number )
   {
      integer.erase( --integer.cend() );
      for( value_type i = number; i > 0; i /= 10 )
         integer.insert( integer.cend(), i % 10 );
   }

   // compute base raised to the power of expon
   void power( HugeInteger &base, const value_type &expon )
   {
      *integer.begin() = 1;
      for( value_type i = 0; i < expon; ++i )
      {
         *this *= base;
         if( integer.size() > maxSize - base.integer.size() )
            break;
      }
   }

   size_type size()
   {
      return integer.size();
   }

   // return true if and only if all digits are zero
   bool isZero()
   {
      typename T::iterator it = integer.begin();
      for( ; it != integer.end(); ++it )
         if( *it != 0 )
            return false;

      return true;
   }

   // return true if and only if the leftmost digit is zero
   bool leadingZero()
   {
      return ( integer.size() > 1 && integer.back() == 0 );
   }

private:
   T integer;

   // function that divides a HugeInteger by 10;
   // shift a HugeInteger one position to the right
   void divideByTen()
   {
      typename T::iterator it1 = integer.begin();
      typename T::iterator it2 = it1;
      for( ++it2; it2 != integer.end(); ++it1, ++it2 )
         *it1 = *it2;

      integer.erase( --integer.cend() );
   }

   // function to help increment the integer
   void helpIncrement()
   {
      typename T::iterator it = integer.begin();
      if( isZero() )
         ( *it )++;
      else
      {
         ( *it )++;
         typename T::iterator it2 = it;
         for( ++it2; it2 != integer.end(); ++it, ++it2 )
            if( *it == 10 )
            {
               *it = 0;
               ( *it2 )++;
            }

         if( ( *it ) == 10 )
         {
            *it = 0;
            integer.insert( integer.cend(), 1 );
         }
      }
   }

   // function to help decrement the integer
   void helpDecrement()
   {
      typename T::iterator it = integer.begin();
      for( ; *it == 0; ++it )
         *it = 9;

      ( *it )--;

      if( !isZero() && integer.back() == 0 )
         integer.erase( --( integer.cend() ) );
   }

}; // end class template HugeInteger


// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::reverse_iterator it = hugeInteger.integer.rbegin();
   for( ; it != hugeInteger.integer.rend(); ++it )
      output << *it;

   return output; // enables cout << x << y;
}

template< typename T1, typename T2 >
void solution2()
{
   T2 t, a, b;
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         HugeInteger< T1 > base;
         base.convert( t ); // put all digits of t into base

         HugeInteger< T1 > dividend( 1 );
         dividend.power( base, a ); // dividend = pow( t, a )

         if( dividend.size() > maxSize - base.size() )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            HugeInteger< T1 > divisor( 1 );
            divisor.power( base, b ); // divisor = pow( t, b )

            if( divisor.size() > maxSize - base.size() )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               --dividend; // pow( t, a ) - 1
               --divisor;  // pow( t, b ) - 1

               HugeInteger< T1 > quotient = dividend / divisor;
               HugeInteger< T1 > remainder = dividend % divisor;

               if( quotient.leadingZero() )
                  cout << "quotient has a leading zero!\n";

               if( remainder.leadingZero() )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotient.size() < 100 && remainder.isZero() )
                  cout << quotient << endl;
               else
                  cout << "is not an integer with less than 100 digits.\n";
            }
         }
      }
   }
}

template< typename T >
void solution1()
{
   // execute the following 2 instructions one by one, each of them should get an AC
   solution2< vector< T >, T >();
//   solution2< list< T >, T >();
}

int main()
{
   // execute the following 6 instructions one by one, each of them should get an AC
   solution1< int >();
//   solution1< unsigned int >();
//   solution1< long int >();
//   solution1< unsigned long int >();
//   solution1< long long int >();
//   solution1< unsigned long long int >();
}