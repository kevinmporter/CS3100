//
//  MazeLocationArray.cpp
//  Project1
//

#include "MazeLocationArray.h"
#include <assert.h>  // For assert()
#include <algorithm> // For std::min()
#include <iostream> // For std::cout

///////////////////////////////////////////////////////////
//
void MazeLocationArray::clear() {
    while (0 < this->size()) {
        this->popBack();
    }
}


///////////////////////////////////////////////////////////
//
void MazeLocationArray::pushBack(Maze::Location *const &anElement) {
    this->insertAt(anElement, this->size());
}


///////////////////////////////////////////////////////////
//
void MazeLocationArray::popBack() {
    assert(0 < this->size());

    this->removeAt(this->size() - 1);
}

///////////////////////////////////////////////////////////
//
Maze::Location *&MazeLocationArray::operator[](size_t index) {
    return this->at(index);
}


