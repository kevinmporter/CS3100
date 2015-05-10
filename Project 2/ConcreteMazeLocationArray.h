///////////////////////////////////////////////////////
/// ConcreteMaze::Location Header
/// Kevin Porter
/// CS3100
//////////////////////////////////////////////////////

#include "MazeLocationArray.h"
#include <stdlib.h>  // For size_t

class ConcreteMazeLocationArray : public MazeLocationArray {

private:
    virtual void scrunch();
    size_t beginning;
    size_t length;
    Maze::Location **memory; // store the Maze::Location pointers in an array

    ////////////////////////////////////////////////////////
/// Remove element at index from array moving all
/// elements after index down one position to fill gap
/// created by removing the element reducing the array
/// size by 1
/// removeAt() is now a private function because its implementation might mess up the data structure
/// if used improperly
    virtual void removeAt(size_t index);


public:
    // virtual constructor
    ConcreteMazeLocationArray();

/// Virtual Destructor
    ~ConcreteMazeLocationArray();

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
            size_t index);

////////////////////////////////////////////////////////
/// Returns the number of elements in array
    virtual size_t size() const;

////////////////////////////////////////////////////////
/// Sets the element value stored at the specified
/// index. works as long index is less than size().
    virtual void setAt(Maze::Location *const &anElement,
            size_t index);

////////////////////////////////////////////////////////
/// Returns a reference to the element at index
    virtual Maze::Location *const &at(size_t index) const;

    //virtual Maze::Location * const &pop() const;

    virtual bool isEmpty();

////////////////////////////////////////////////////////
/// Returns a reference to the element at index
    virtual Maze::Location *&at(size_t index);

    virtual Maze::Location *&pop();

    //virtual bool const &isEmpty() const;
};
