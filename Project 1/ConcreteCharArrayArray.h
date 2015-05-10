///////////////////////////////////////////////////////
/// ConcreteCharArray Header
/// Kevin Porter
/// CS3100
//////////////////////////////////////////////////////

#include "CharArrayArray.h"
#include "CharArray.h"
#include <stdlib.h>  // For size_t

class ConcreteCharArrayArray : public CharArrayArray {

private:
    size_t length;
    CharArray **memory; // store the CharArray pointers in an array


public:
    // virtual constructor
    ConcreteCharArrayArray();
/// Virtual Destructor
    ~ConcreteCharArrayArray();

///////////////////////////////////////////////////////////
/// BEGIN Pure virtual member functions to be implemented
/// by concrete subclasses
///////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
/// The array is extended by inserting anElement before
/// the element at the specified index increasing the
/// array size by 1. Any existing elements at index
/// and beyond are moved to make space for the inserted
/// element.
/// If index is equal to size(), anElement is appended to
/// the end of the array. Array storage expands as
/// necessary.
    virtual void insertAt(CharArray * const &anElement,
            size_t index);

////////////////////////////////////////////////////////
/// Remove element at index from array moving all
/// elements after index down one position to fill gap
/// created by removing the element reducing the array
/// size by 1
    virtual void removeAt(size_t index);

////////////////////////////////////////////////////////
/// Returns the number of elements in array
    virtual size_t size() const;

////////////////////////////////////////////////////////
/// Sets the element value stored at the specified
/// index. works as long index is less than size().
    virtual void setAt(CharArray * const &anElement,
            size_t index);

////////////////////////////////////////////////////////
/// Returns a reference to the element at index
    virtual CharArray * const &at(size_t index) const;

////////////////////////////////////////////////////////
/// Returns a reference to the element at index
    virtual CharArray * &at(size_t index);
};
