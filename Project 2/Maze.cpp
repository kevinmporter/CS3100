//
//  ConcreteMaze.cpp
//  MazeSolver
//
//

#include "Maze.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/////////////////////////////////////////////////////////////////
//
class ConcreteMaze : public Maze {
protected:
    const uint8_t *data;
    uint32_t *breadcrumbData;
    uint16_t width;
    uint16_t length;

public:

    ConcreteMaze();

    ~ConcreteMaze();

    uint16_t getWidth() const {
        return this->width;
    };

    uint16_t getLength() const {
        return this->length;
    };

    Location startLocation() const;

    bool isOpenAt(const Maze::Location &aLocation) const;

    uint32_t &breadcrumbAt(const Maze::Location &aLocation);

};


/////////////////////////////////////////////////////////////////
//
static const uint8_t defaultMazeArray[801] = "\
X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\
X XX X XX          X                   X\
X X     X XXXXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXX X   X      X X                 X\
X       X X X XXXXXX X XXXXXXXXXXXXXXX X\
X XXXXXXX X X      X X                 X\
X         X XXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXXXXXX X      X X                 X\
X X         XXXXXX X XXXXXXXXX XXXXXXXXX\
X X XXXXXXXXX   X  X X       X         X\
X X X         X   XX X XXXXX XXXXXXXXX X\
X X XXXXXXXXXXXXXXXX X X             X X\
X X            X   X   X X X X X X X X X\
X XXXXXXXXXXXX X X X XXXXXXXXXXXXXXXXX X\
X            X X X X                   X\
X XXXXXXXXXXXX   X X XXXXXXXXXXXXXXXXXXX\
X X XX   XXXXXXXXXXX                   X\
X    XXX           XXXXXXXXXXXXXXXXXXX X\
X XX     X X X X X                     X\
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";


/////////////////////////////////////////////////////////////////
//
ConcreteMaze::ConcreteMaze() {
    this->data = defaultMazeArray;
    this->width = 40;
    this->length = 20;
    breadcrumbData = new uint32_t[this->length * this->width]();
}


/////////////////////////////////////////////////////////////////
//
ConcreteMaze::~ConcreteMaze() {
    delete[] breadcrumbData;
}


/////////////////////////////////////////////////////////////////
//
Maze::Location ConcreteMaze::startLocation() const {
    Maze::Location result(1, 0);

    return result;
}


/////////////////////////////////////////////////////////////////
//
bool ConcreteMaze::isOpenAt(
        const Maze::Location &aLocation) const {
    bool result = false;

    if (this->isInside(aLocation)) {
        size_t index = (aLocation.y * this->getWidth()) +
                aLocation.x;

        result = (this->data[index] == ' ');
    }

    return result;
}


/////////////////////////////////////////////////////////////////
//
uint32_t &ConcreteMaze::breadcrumbAt(
        const Maze::Location &aLocation) {
    assert(this->isInside(aLocation));
    size_t index = (aLocation.y * this->getWidth()) +
            aLocation.x;

    return breadcrumbData[index];
}


/////////////////////////////////////////////////////////////////
//
Maze *MakeMaze() {
    return new ConcreteMaze();
}

