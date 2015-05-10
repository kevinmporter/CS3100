//
//  Maze::LocationArray.h
//  Project1
//

#ifndef __MazeLocationArray__MazeLocationArray
#define __MazeLocationArray__MazeLocationArray

#include <stdlib.h>  // For size_t
#include "Maze.h"

class MazeLocationArray;

///////////////////////////////////////////////////////////
/// This class encapsulates an array storing any number of
/// Maze::Location * elements limited only by the amount
/// of memory available in the host process and provides
/// access to stored Maze::Location elements via index
/// position within the array.
class MazeLocationArray {
public:

    ///
    /// Virtual Destructor
    virtual ~MazeLocationArray() {
    };

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
    virtual void insertAt(Maze::Location *const &anElement,
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
    virtual void setAt(Maze::Location *const &anElement,
            size_t index) = 0;

    ////////////////////////////////////////////////////////
    /// Returns a reference to the element at index
    virtual Maze::Location *const &at(size_t index) const = 0;

    ////////////////////////////////////////////////////////
    /// Returns a reference to the element at index
    virtual Maze::Location *&at(size_t index) = 0;

////////////////////////////////////////////////////////////////////////////////
/// END Pure virtual member functions to be implemented by concrete
////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////
    /// Remove all elements from array and set array's size
    /// to 0
    void clear();

    ////////////////////////////////////////////////////////
    /// Append element at end of array expanding storage for
    /// array as necessary
    void pushBack(Maze::Location *const &anElement);

    ////////////////////////////////////////////////////////
    /// Removes and returns the last element in array
    void popBack();


    ////////////////////////////////////////////////////////
    /// Returns a reference to the element at index. This
    /// operator enables semantics similar to built-in
    /// arrays. e.g.
    /// someArray[5] = someArray[6];
    Maze::Location *&operator[](size_t index);

    ////////////////////////////////////////////////////////
    /// Returns a reference to the element at index. This
    /// operator enables semantics similar to built-in
    /// arrays. e.g.
    /// someArray[6];
    const Maze::Location *&operator[](size_t index) const;
};

#endif /* defined(__Maze::LocationArrayy__Maze::LocationArray__) */

