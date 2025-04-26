// 10083 - Division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

const int maxSize = 200;

#include <cstddef>

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
   using iterator = value_type *;
   using const_iterator = const value_type *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   vector()
      : myData()
   {
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   vector( const size_type count )
      : myData()
   {
       if (count == 0)
           myData.myFirst = myData.myLast = myData.myEnd = nullptr;
       else
       {
           myData.myFirst = new value_type[count]();
           myData.myLast = myData.myEnd = myData.myFirst + count;
       }

   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   vector( const vector &right )
      : myData()
   {
       size_type size = right.myData.myLast - right.myData.myFirst;
       if (size != 0)
       {
           myData.myFirst = new value_type[size];
           for (size_t i = 0; i < size; i++)
               myData.myFirst[i] = right.myData.myFirst[i];

           myData.myLast = myData.myFirst + size;
           myData.myEnd = myData.myFirst + size;
       }
       else
       {
           myData.myFirst = myData.myLast = myData.myEnd = nullptr;
       }


   }

   // Vector destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the vector.
   ~vector()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   // The vector is extended by inserting a new element before the element
   // at the specified position, effectively increasing the container size by one.
   // This causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   // Relocates all the elements that were after "where" to their new positions.
   iterator insert( const_iterator where, const value_type &val )
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

   // overloaded assignment operator
   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
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

   // Removes from the vector a single element (where).
   // This effectively reduces the container size by one, which is destroyed.
   // Relocates all the elements after the element erased to their new positions.
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

   // Removes all elements from the vector (which are destroyed),
   // leaving the container with a size of 0.
   // A reallocation is not guaranteed to happen,
   // and the vector capacity is not guaranteed to change due to calling this function.
   void clear()
   {
      myData.myLast = myData.myFirst;
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return myData.myFirst;
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myFirst );
   }

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   iterator end()
   {
      return myData.myLast;
   }

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myLast );
   }

   // Returns a const_iterator pointing to the first element in the container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator cbegin() const
   {
      return begin();
   }

   // Returns a const_iterator pointing to the past-the-end element in the container.
   // If the container is empty, this function returns the same as vector::cbegin.
   // The value returned shall not be dereferenced.
   const_iterator cend() const
   {
      return end();
   }

   // Returns whether the vector is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.myFirst == myData.myLast;
   }

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   size_type size() const
   {
      return static_cast< size_type >( myData.myLast - myData.myFirst );
   }

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   // This capacity is not necessarily equal to the vector size.
   // It can be equal or greater, with the extra space allowing to accommodate
   // for growth without the need to reallocate on each insertion.
   size_type capacity() const
   {
      return static_cast< size_type >( myData.myEnd - myData.myFirst );
   }

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   value_type& front()
   {
      return *myData.myFirst;
   }

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   const value_type& front() const
   {
      return *myData.myFirst;
   }

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   value_type& back()
   {
      return myData.myLast[ -1 ];
   }

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   const value_type& back() const
   {
      return myData.myLast[ -1 ];
   }

private:

   ScaryVal myData;
};

// determine if two Arrays are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const vector< Ty > &left, const vector< Ty > &right )
{
    if (left.size() != right.size())
        return false;

    for (size_t i = 0; i < left.size(); ++i)
    {
        if (*(left.begin() + i) != *(right.begin() + i) )
            return false;
    }

    return true;




}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( const vector< Ty > &left, const vector< Ty > &right )
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
   HugeInteger( unsigned int n = 0 )
      : integer( ( n == 0 ) ? 1 : n )
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
   } // end function operator==

   // function that tests if one HugeInteger is less than another
   bool operator<( HugeInteger &right )
   {
       if (integer.size() != right.integer.size())
           return integer.size() < right.integer.size(); 

       typename T::const_iterator it1 = integer.end() - 1;
       typename T::const_iterator it2 = right.integer.end() - 1;
       for (; it1 >= integer.begin(); --it1, --it2)
       {
           if (*it1 != *it2)
               return *it1 < *it2;
       }
       return false; 

   } // end function operator<

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
      if( *this == op2 )
         return zero;

      HugeInteger difference( *this );
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
          difference.integer.erase(difference.integer.end() - 1);



      if( difference.leadingZero() )
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
           product.integer.erase(product.integer.end() - 1);

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
      if( *this < op2 )
         return zero;

      HugeInteger dividend(*this);
      HugeInteger divisor(op2);
      HugeInteger remainder = dividend;

      size_type dividendSize = dividend.integer.size();
      size_type divisorSize = divisor.integer.size();

      int shift = static_cast<int>(dividendSize) - static_cast<int>(divisorSize);

      HugeInteger buffer(divisor);
      for (int i = 0; i < shift; ++i)
          buffer.integer.insert(buffer.integer.begin(), 0);

      int quotientSize;
      if (dividend < buffer) {
          buffer.integer.erase(buffer.integer.begin());
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

          buffer.integer.erase(buffer.integer.begin());
      }
      return quotient;
   } 

   // modulus operator; HugeInteger % HugeInteger
   // provided that the op2 is not equal to 0
   HugeInteger operator%( HugeInteger &op2 )
   {
      return *this - ( ( *this / op2 ) * op2 );
   }

   // overloaded prefix increment operator 
   HugeInteger& operator++()
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
      integer.erase( integer.end() - 1 );
      for( value_type i = number; i > 0; i /= 10 )
         integer.insert( integer.end(), i % 10 );
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

   // function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
   void divideByTen()
   {
      typename T::iterator it = integer.begin() + 1;
      for( ; it != integer.end(); ++it )
         *( it - 1 ) = *it;
      integer.erase( integer.end() - 1 );
   }

   // function to help increment the integer
   void helpIncrement()
   {
      typename T::iterator it = integer.begin();
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
         integer.insert( integer.end(), 1 );
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
         integer.erase( integer.end() - 1 );
   }
}; // end class HugeInteger


// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::iterator it = hugeInteger.integer.end() - 1;
   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}


template< typename T >
void solution()
{
   T t, a, b;
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
         HugeInteger< vector< T > > base;
         base.convert( t ); // put all digits of t into base

         HugeInteger< vector< T > > dividend( 1 );
         dividend.power( base, a ); // dividend = pow( t, a )

         if( dividend.size() > maxSize - base.size() )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            HugeInteger< vector< T > > divisor( 1 );
            divisor.power( base, b ); // divisor = pow( t, b )

            if( divisor.size() > maxSize - base.size() )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               --dividend; // pow( t, a ) - 1
               --divisor;  // pow( t, b ) - 1

               HugeInteger< vector< T > > quotient = dividend / divisor;
               HugeInteger< vector< T > > remainder = dividend % divisor;

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

int main()
{
   // execute the following 6 instructions one by one, each of them should get an AC
   solution< int >();
//   solution< unsigned int >();
//   solution< long int >();
//   solution< unsigned long int >();
//   solution< long long int >();
//   solution< unsigned long long int >();
}