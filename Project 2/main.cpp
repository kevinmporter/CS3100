//
//  main.cpp
//  MazeSolver
//
// Kevin Porter
// CS-3100-01
//

#include <stdint.h>
#include <stdio.h>

#include <iostream>
#include <unistd.h>
#include "Maze.h"
#include "ConcreteMazeLocationArray.h"

//////////////////////////////////////////////////////////////
/// This function prints the maze represented by the receiver.
/// If the maze has been solved, the printed maze includes '.'
/// characters in each position along a path from the start
/// position to an exit from the maze.
static void print(Maze &aMaze) {
    for (uint16_t j = 0; j < aMaze.getLength(); j++) {
        for (uint16_t i = 0; i < aMaze.getWidth(); i++) {
            Maze::Location location(i, j);
            uint8_t block = '#';

            if (aMaze.isOpenAt(location)) {
                block = aMaze.breadcrumbAt(location);

                //////////////////////////////////////////////////
                /// PLEASE NOTE I HAVE CHANGED THIS CONDITIONAL //
                //////////////////////////////////////////////////
                if (0 == block) {
                    block = ' ';
                }
            }

            putc(block, stdout);
        }
        putc('\n', stdout);
    }
};


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/// This function is an iterative version of the recursive maze solution.
/// It takes a maze and a start location and solves the maze.
static bool solve(Maze &maze, Maze::Location currentLocation) {
    // I'm in the habit of initializing variables, just in case
    bool isSolved = false;
    bool nowhere = true;
    // array-based queue from previous project
    ConcreteMazeLocationArray queue;
    Maze::Location *location = &currentLocation;

    // begin the loop with the start location already on the queue
    //location->setPrevLoc(location);
    queue.pushBack(location);
    while (queue.size() > 0) {
        //sleep(1);
        //print(maze);
        location = queue.pop();
        // a '.' breadcrumb means that location has been checked
        maze.breadcrumbAt(*location) = '.';
        // always check to see if the new location is the exit
        if (maze.isExit(*location)) {
            std::cout << "Solution found at: (" << location->x << "," << location->y << ")" << std::endl;
            // place a path breadcrumb at the start location
            Maze::Location start = maze.startLocation();
            maze.breadcrumbAt(start) = '.';
            /*while (!location->isEqual(&start)) {
                // follow the locations that led to the shortest solution and place a path breadcrumb
                maze.breadcrumbAt(*location) = '.';
                location = location->getPrevLoc();
            }*/
            isSolved = true;
            break;
        }
        // not the solution, so check every direction
        nowhere = true;
        Maze::Location *testRight = new Maze::Location((uint16_t) (location->x + 1), location->y);
        if (maze.isOpenAt(*testRight) && maze.breadcrumbAt(*testRight) != '.') {
            //testRight->setPrevLoc(location);
            queue.pushBack(testRight);
            nowhere = false;
        }
        Maze::Location *testDown = new Maze::Location(location->x, (uint16_t) (location->y + 1));
        if (maze.isOpenAt(*testDown) && maze.breadcrumbAt(*testDown) != '.') {
            //testDown->setPrevLoc(location);
            queue.pushBack(testDown);
            nowhere = false;
        }
        Maze::Location *testLeft = new Maze::Location((uint16_t) (location->x - 1), location->y);
        if (maze.isOpenAt(*testLeft) && maze.breadcrumbAt(*testLeft) != '.') {
            //testLeft->setPrevLoc(location);
            queue.pushBack(testLeft);
            nowhere = false;
        }
        Maze::Location *testUp = new Maze::Location(location->x, (uint16_t) (location->y - 1));
        if (maze.isOpenAt(*testUp) && maze.breadcrumbAt(*testUp) != '.') {
            //testUp->setPrevLoc(location);
            queue.pushBack(testUp);
            nowhere = false;
        }
        // if the location can't go anywhere else and there are no new locations to check,
        // then the maze isn't solvable
        if (nowhere && queue.isEmpty()) {
            std::cout << "No solution!" << std::endl;
            isSolved = false;
            break;
        }
    }
    return isSolved;
}


/////////////////////////////////////////////////////////////////
/// This function makes a maze, solves it, and prints the
/// solution.
int main(int argc, const char *argv[]) {
    Maze *mazePtr = MakeMaze();

    solve(*mazePtr, mazePtr->startLocation());

    print(*mazePtr);

    delete mazePtr;
    mazePtr = NULL;

    return 0;
}
