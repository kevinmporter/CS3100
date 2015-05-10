//
//  Array.h
//  Project1
//

#ifndef __Array__Array
#define __Array__Array

#include <stdlib.h>  // For size_t
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <sstream>
#include <string>
#include <assert.h>


///////////////////////////////////////////////////////////
/// This class encapsulates an array storing any number of
/// elements limited only by the amount of memory available
/// in the host process and provides access to stored
/// elements via within the array.
template<typename element>
class Array
{
public:
   ///
   /// Virtual Destructor
   virtual ~Array() {};
   
///////////////////////////////////////////////////////////
/// BEGIN Pure virtual member functions to be implemented
/// by concrete subclasses
///////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////
   /// These member functions each return an iterator to
   /// the first element in the array.
   virtual element * begin() = 0;
   virtual const element * begin() const = 0;

   ////////////////////////////////////////////////////////
   /// These member functions each return an iterator to
   /// one index past the end of the array.
   virtual element * end() = 0;
   virtual const element * end() const = 0;
      
   ////////////////////////////////////////////////////////
   /// The array is extended by inserting anElement before
   /// the element at the specified index increasing the
   /// array size by 1. Any existing elements at index
   /// and beyond are moved to make space for the inserted
   /// element.
   /// If index is equal to size(), anElement is appended to
   /// the end of the array. Array storage expands as
   /// necessary.
   virtual void insertAt(element const &anElement,
      size_t index) = 0;
   
   ////////////////////////////////////////////////////////
   /// Remove element at index from array moving all
   /// elements after index down one position to fill gap
   /// created by removing the element reducing the array
   /// size by 1
   virtual void removeAt(size_t index) = 0;
   
   ////////////////////////////////////////////////////////
   /// Returns the number of elements in array
   virtual size_t size() const = 0;
   
   ////////////////////////////////////////////////////////
   /// Sets the element value stored at the specified
   /// index. works as long index is less than size().
   virtual void setAt(element const &anElement,
      size_t index) = 0;
   
   ////////////////////////////////////////////////////////
   /// Returns a reference to the element at index
   virtual element const &at(size_t index) const = 0;
   
   ////////////////////////////////////////////////////////
   /// Returns a reference to the element at index
   virtual element &at(size_t index) = 0;
   
///////////////////////////////////////////////////////////
/// END Pure virtual member functions to be implemented
/// by concrete
///////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////
   /// Remove all elements from array and set array's size
   /// to 0
   void clear()
   {
      while(0 < this->size())
      {
         this->pop_back();
      }
   };
   
   element &back()
   {
      return at(size() - 1);
   }
   
   element const &back() const
   {
      return at(size() - 1);
   }
   
   ////////////////////////////////////////////////////////
   /// Append element at end of array expanding storage for
   /// array as necessary
   void push_back(element const &anElement)
   {
      this->insertAt(anElement, this->size());
   };
   
   ////////////////////////////////////////////////////////
   /// Removes and returns the last element in array 
   void pop_back()
   {
      assert(0 < this->size());
      
      this->removeAt(this->size() - 1);
   };
   
   ////////////////////////////////////////////////////////
   /// Appends all elements in a Array to array expanding
   /// storage for array as necessary
   void append(Array &source)
   {
      const size_t count = source.size();
      
      for(size_t i = 0; i < count; i++)
      {
         this->push_back(source.at(i));
      }
   };
   
   ////////////////////////////////////////////////////////
   /// Returns a reference to the element at index. This
   /// operator enables semantics similar to built-in
   /// arrays. e.g.
   /// someArray[5] = someArray[6];
   element &operator [](size_t index)
   {
      return this->at(index);
   }
   
   ////////////////////////////////////////////////////////
   /// Returns a reference to the element at index. This
   /// operator enables semantics similar to built-in
   /// arrays. e.g.
   /// someArray[6];
   element const &operator [](size_t index) const
   {
      return this->at(index);
   }
   
   ////////////////////////////////////////////////////////
   /// Returns a string representation of the array's
   /// elements
   operator std::string() const
   {
      std::ostringstream tempOStream;
      
      tempOStream  << "(";
      std::copy(begin(), end(),
            std::ostream_iterator<void *>(tempOStream, ", "));
      tempOStream  << ")\n";
      
      return tempOStream.str();
   }
};

#endif /* defined(__Arrayy__Array__) */

