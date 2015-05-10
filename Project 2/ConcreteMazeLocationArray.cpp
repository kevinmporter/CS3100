////////////////////////////////////////////
/// Kevin Porter
/// CS3100
/// ConcreteMazeLocationArray implementation
///////////////////////////////////////////

#include <assert.h>
#include "ConcreteMazeLocationArray.h"

////////////////////
/// Constructor
///////////////////
ConcreteMazeLocationArray::ConcreteMazeLocationArray() {
    length = 0;
    beginning = 0;
    memory = NULL;
}

////////////////////
/// Destructor
///////////////////
ConcreteMazeLocationArray::~ConcreteMazeLocationArray() {
    // be a good citizen, release memory on destruct
    if (memory != NULL) {
        free(memory);
    }
}

void ConcreteMazeLocationArray::setAt(Maze::Location *const &anElement, size_t index) {
    // only allow new elements or changing elements
    assert(index < size() + 1);
    // if it's a new element, increase the array to allow for it
    if (index == size()) {
        Maze::Location **insert = NULL;
        length = size() + 1;
        insert = (Maze::Location **) realloc(memory, (size() * sizeof(Maze::Location *)));

        if (insert != NULL) { // migrate array if realloc was successful
            memory = insert;

        }
    }
    // always set the new element
    memory[index] = anElement;
}

void ConcreteMazeLocationArray::insertAt(Maze::Location *const &anElement, size_t index) {
    // only allow insertions within the array or at the end
    assert(index < size() + 1);
    Maze::Location **insert = NULL;
    if (index < size() + 1) {
        length = size() + 1;
        insert = (Maze::Location **) realloc(memory, (sizeof(Maze::Location *) * length));

        if (insert != NULL) { // migrate the array if realloc was successful
            memory = insert;
            // size - 1 because size references the new array size, not the current array size
            for (size_t i = size() - 1; i > index; i--) { // make room for the new element
                memory[i] = memory[i - 1];
            }
            memory[index] = anElement;
        }
    }
}

void ConcreteMazeLocationArray::removeAt(size_t index) {
    // only allow removes from inside the array
    if (index == beginning) {
        beginning = beginning + 1;
    } else {
        assert(index < size());
        Maze::Location **remove = NULL;
        for (size_t i = index; i < size(); i++) { // make remove element at index and close gap
            memory[i] = memory[i + 1];
        }
        length = size() - 1;
        remove = (Maze::Location **) realloc(memory, size() * sizeof(Maze::Location *));

        if (remove != NULL) { // migrate memory iff realloc was successful
            memory = remove;
        }
    }
}

Maze::Location *const &ConcreteMazeLocationArray::at(size_t index) const {
    return memory[index];
}

Maze::Location *&ConcreteMazeLocationArray::at(size_t index) {
    return memory[index];
}

size_t ConcreteMazeLocationArray::size() const {
    const size_t return_value = length;
    return return_value;
}

void ConcreteMazeLocationArray::scrunch() {
    assert(beginning < size());
    Maze::Location **remove = NULL;
    for (size_t i = 0; i < size() - beginning; i++) { // make remove element at index and close gap
        memory[i] = memory[beginning + i];
    }
    length = size() - beginning;
    remove = (Maze::Location **) realloc(memory, size() * sizeof(Maze::Location *));

    if (remove != NULL) { // migrate memory iff realloc was successful
        memory = remove;
    }
    beginning = 0;
}

/*Maze::Location * const &ConcreteMazeLocationArray::pop() {
    assert(beginning <= size());
    Maze::Location * const &location_value = at(beginning);
    if (beginning > 50) {
        scrunch();
    }
    removeAt(beginning);
    //Maze::Location *&return_value = *&location_value;
    return *&location_value;
}*/

Maze::Location *&ConcreteMazeLocationArray::pop() {
    assert(beginning <= size());
    Maze::Location *&location_value = at(beginning);
    if (beginning > 50) {
        scrunch();
    }
    removeAt(beginning);
    //Maze::Location *&return_value = *&location_value;
    return *&location_value;
}

bool ConcreteMazeLocationArray::isEmpty() {
    bool const &empty = true;
    bool const &notEmpty = false;
    if (beginning >= size()) {
        return true;
    } else {
        return false;
    }
}

/*bool &ConcreteMazeLocationArray::isEmpty() {
    bool m_isEmpty = false;
    if (beginning >= size()) {
        m_isEmpty = true;
    }
    bool &return_value = m_isEmpty;
    return return_value;
}*/
