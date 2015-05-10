//
//  ConcreteArray.h
//  Project1
//  Kevin Porter
//

#ifndef __Array__ConcreteArray__
#define __Array__ConcreteArray__

#include "Array.h"
#include <string.h>  // For memmove()
#include <stdlib.h>  // For calloc(), realloc()
#include <algorithm>
#include <assert.h>

///////////////////////////////////////////////////////////
/// BEGIN code added for Project 3
///////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
/// NEW IN PROJECT 3
////////////////////////////////////////////////////////
// THIS FUNCTION MUST BE DECLARED BEFORE
// ConcreteArray OR ELSE COMPILER WILL NOT KNOW HOW
// TO COPY elements.
////////////////////////////////////////////////////////
template<typename T>
T *deepCopy(T *original)
{
   return original->makeDeepCopy();
}


////////////////////////////////////////////////////////
/// NEW IN PROJECT 3
////////////////////////////////////////////////////////
// THIS FUNCTION MUST BE DECLARED BEFORE
// ConcreteArray OR ELSE COMPILER WILL NOT KNOW HOW
// TO COPY long *.
////////////////////////////////////////////////////////
long *deepCopy(long *original)
{
   return new long(*original);
}

///////////////////////////////////////////////////////////
/// END code added for Project 3 (SEE THE
/// Project 3 "To Do" CODE BELOW
///////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
/// This class encapsulates an array storing any number of
/// elements limited only by the amount of memory available
/// in the host process and provides access to stored
/// elements via index position within the array.
template<class element>
class ConcreteArray : public Array<element>
{
private:
   /// Default capacity is an arbitrary small value > 0
   static const size_t defaultCapacity = 8;
   
   element *m_Data;   /// Pointer to storage for elements
   size_t m_Size;     /// Number of elements stored
   size_t m_Capacity; /// Number of elements that can be
   
public:
   
   ////////////////////////////////////////////////////////
   /// Default constructor
   ConcreteArray() :
      m_Size(0),
      m_Capacity(ConcreteArray::defaultCapacity)
   {
      m_Data = new element[m_Capacity];
   };
   
   ////////////////////////////////////////////////////////
   /// Copy Constructor (shallow copy)
   ConcreteArray(const ConcreteArray<element> &original) :
      m_Size(original.m_Size),
      m_Capacity(original.m_Capacity)
   {
      assert(m_Size <= m_Capacity);
      
      m_Data = new element[m_Capacity];
      for(size_t i = 0; i < m_Size; i++)
      {
         m_Data[i] = original.m_Data[i];
      }
   };
   
   ////////////////////////////////////////////////////////
   /// Destructor
   virtual ~ConcreteArray()
   {
      delete [] m_Data;
      m_Size = 0;
   };

   ////////////////////////////////////////////////////////
   /// The array is extended by inserting element before
   /// the element at the specified index increasing the
   /// array size by 1.
   /// Any existing elements at index and beyond are moved
   /// to make space for the inserted element.
   /// If index is equal to size(), element is appended to
   /// the end of the array.
   /// Array storage expands as necessary.
   virtual void insertAt(element const &anElement,
                         size_t index)
   {
      assert(index <= m_Size);
      
      if(m_Size == (m_Capacity - 1))
      {  // Double the amount of memory allocated for
         // storing elements
         m_Capacity *= 2;
         element *newData = new element[m_Capacity];
         for(size_t i = 0; i < m_Size; i++)
         {
            newData[i] = m_Data[i];
         }
         delete [] m_Data;
         m_Data = newData;
      }
      
      assert((m_Size + 1) < m_Capacity);
      
      if(index < m_Size)
      {  // Move elements after index to make room for
         // element to be inserted
         for(size_t i = m_Size - 1; i > index; i--)
         {
            m_Data[i] = m_Data[i-1];
         }
      }
      
      m_Size++;
      m_Data[index] = anElement;
   };
   
   ////////////////////////////////////////////////////////
   /// Remove element at index from array moving all
   /// elements after index one position to fill gap
   /// created by removing the element
   virtual void removeAt(size_t index)
   {
      assert(index < m_Size);
      
      if((index + 1) < m_Size)
      {  // Move elements to close gap left by removing
         // an element
         for(size_t i = index + 1; i < m_Size; i++)
         {
            m_Data[i-1] = m_Data[i];
         }
      }
      m_Size--;
   };
   
   ////////////////////////////////////////////////////////
   /// Returns the number of elements in array
   virtual size_t size() const
   {
      return m_Size;
   };
   
   ////////////////////////////////////////////////////////
   /// Sets the element value stored at the specified
   /// index. works as long index is less than size().
   virtual void setAt(element const &anElement,
                      size_t index)
   {
      assert(index < m_Size);
      
      m_Data[index] = anElement;
   };
   
   ////////////////////////////////////////////////////////
   /// Returns the element at index
   virtual element const &at(size_t index) const
   {
      assert(index < m_Size);
      
      return m_Data[index];
   };
   
   ////////////////////////////////////////////////////////
   /// Returns the element at index
   virtual element &at(size_t index)
   {
      assert(index < m_Size);
      
      return m_Data[index];
   };
   
   
   
///////////////////////////////////////////////////////////
/// BEGIN code added for Project 3
///////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////
   /// NEW IN PROJECT 3
   ////////////////////////////////////////////////////////
   /// Constructor via iterators (shallow copy)
   template <class _InputIterator>
   ConcreteArray(
      _InputIterator start,
      _InputIterator end) :
      m_Size(0),
      m_Capacity(ConcreteArray::defaultCapacity)
   {
      m_Data = new element[m_Capacity];
      
      for(_InputIterator it(start); it != end; ++it)
      {
         this->push_back(*it);
      }
   }

   ////////////////////////////////////////////////////////
   /// NEW IN PROJECT 3
   ////////////////////////////////////////////////////////
   /// Returns a newly allocated array produced by deep
   /// copying this.
   virtual ConcreteArray<element> *makeDeepCopy() const
   {
      // create a new array from the heap
      ConcreteArray<element> *array = new ConcreteArray();
      // perform deep copy for every element in the array
      for (size_t i = 0; i < this->size(); i++) {
         array->push_back(deepCopy(this->at(i)));
      }
      
      return array;  
   }
   
   ////////////////////////////////////////////////////////
   /// NEW IN PROJECT 3
   ////////////////////////////////////////////////////////
   /// These member functions each return an iterator to
   /// the first element in the array.
   virtual element * begin()
   {
      return &m_Data[0];  
   };
   
   ////////////////////////////////////////////////////////
   /// NEW IN PROJECT 3
   virtual const element * begin() const
   {
      return &m_Data[0];  
   };
   
   ////////////////////////////////////////////////////////
   /// NEW IN PROJECT 3
   ////////////////////////////////////////////////////////
   /// These member functions each return an iterator to
   /// one index past the end of the array.
   virtual element * end()
   {
      return &m_Data[size()];  
   };
   
   ////////////////////////////////////////////////////////
   /// NEW IN PROJECT 3
   virtual const element * end() const
   {
      return &m_Data[size()];  
   };
   
   ////////////////////////////////////////////////////////
   /// NEW IN PROJECT 3
   ////////////////////////////////////////////////////////
   /// Overloaded assignment operator
   ConcreteArray &operator=(
      const ConcreteArray &original)
   {
      // only perform copy if it's a different array
      if (this != &original) {
         // start from scratch
         this->clear();
         // perform deep copy for every element in the array
         for (size_t i = 0; i < original.size(); i++) {
            this->push_back(deepCopy(original.at(i)));
         }
      }
      return *this;
   }
};


////////////////////////////////////////////////////////
/// NEW IN PROJECT 3
////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
template<typename T>
ConcreteArray<T> *deepCopy(ConcreteArray<T> *original)
{
   return original->makeDeepCopy();
}


#endif /* defined(__Array__ConcreteArray__) */
