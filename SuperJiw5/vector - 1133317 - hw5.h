// vector standard header

#ifndef VECTOR_H
#define VECTOR_H

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
      if( count != 0 )
      {
         myData.myFirst = new value_type[ count ]();

         for (int i = 0; i < count; i++)
             myData.myFirst[i] = 0;
         myData.myLast = myData.myFirst + count;
         myData.myEnd = myData.myFirst + count;
      }
      myData.myFirst = myData.myLast = myData.myEnd = nullptr;
   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   vector( const vector &right )
      : myData()
   {
       size_t size = right.myData.myLast - right.myData.myFirst;
       if (size != 0) 
       {
           myData.myFirst = new value_type[ size ];
           for (int i = 0; i < size ; i++ )
               myData.myFirst[i] = right.myData.myFirst[i];
           myData.myLast = myData.myFirst + size;
           myData.myEnd = myData.myFirst + size;
       }

       myData.myFirst = myData.myLast = myData.myEnd = nullptr;
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
      if( where < myData.myFirst || where > myData.myLast )
         return nullptr;

      size_type pos = where - myFirst;
      size_type originalSize = size();
      size_type originalCapacity = capacity();
      if( originalSize == originalCapacity )
      {
         size_type newCapacity;
         if( originalCapacity <= 1 )
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
             newArray[j + 1] = myData.myFirst[i];
         }

         delete[] myFirst;

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
      if( this != &right ) // avoid self-assignment
      {
         size_type rightSize = right.size();
         if( rightSize > capacity() )
         {
            if( capacity() > 0 )
               delete[] myData.myFirst; // release space

            size_type newCapacity = capacity() * 3 / 2;
            if( newCapacity < rightSize )
               newCapacity = rightSize;

            myData.myFirst = new value_type[newCapacity]();
            myData.myEnd = myData.myFirst + newCapacity;

         }

         for (size_type i = 0; i < rightSize; i++
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
      if( where < myData.myFirst || where >= myData.myLast )
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

   // Returns a reference to the element at position "pos" in the vector container.
   value_type& operator[]( const size_type pos )
   {
      if( pos >= static_cast< size_type >( myData.myLast - myData.myFirst ) )
      {
         cout << "vector subscript out of range\n";
         exit( 1 );
      }

      return myData.myFirst[ pos ];
   }

   // Returns a reference to the element at position "pos" in the vector container.
   const value_type& operator[]( const size_type pos ) const
   {
      if( pos >= static_cast< size_type >( myData.myLast - myData.myFirst ) )
      {
         cout << "vector subscript out of range\n";
         exit( 1 );
      }
      
      return myData.myFirst[ pos ];
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

private:

   ScaryVal myData;
};

// determine if two Arrays are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const vector< Ty > &left, const vector< Ty > &right )
{



}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( const vector< Ty > &left, const vector< Ty > &right )
{
   return !( left == right );
}

#endif // VECTOR_H