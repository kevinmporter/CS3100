///////////////////////////////////////////////////////
/// ConcreteCharArray Header
/// Kevin Porter
/// CS3100
//////////////////////////////////////////////////////

#include "CharArray.h"
#include <stdlib.h>  // For size_t
#include <iostream> // For std::cout
#include <assert.h>

class ConcreteCharArray : public CharArray {
private:

    size_t length;
    char *memory; // store chars in array

public:

    // methods implemented in ConcreteCharArray.cpp

    ConcreteCharArray();

    ~ConcreteCharArray();
    ////////////////////////////////////////////////////////
    /// The array is extended by inserting anElement before
    /// the element at the specified index increasing the
    /// array size by 1. Any existing elements at index
    /// and beyond are moved to make space for the inserted
    /// element.
    /// If index is equal to size(), anElement is appended to
    /// the end of the array. Array storage expands as
    /// necessary.
    virtual void insertAt(char const &anElement,
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
    virtual void setAt(char const &anElement,
            size_t index);

    ////////////////////////////////////////////////////////
    /// Returns a reference to the element at index
    virtual char const &at(size_t index) const;

    ////////////////////////////////////////////////////////
    /// Returns a reference to the element at index
    virtual char &at(size_t index);
};
