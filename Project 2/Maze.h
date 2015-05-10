//
//  Maze.h
//  MazeSolver
//
//

#ifndef __MazeSolver__Maze__
#define __MazeSolver__Maze__

#include <stdint.h>
#include <time.h>

////////////////////////////////////////////////////////////////////////////////
/// This class encapsulates a maze with positions identified by integer x and y
/// coordinates. Each position within the maze is "open" if a person could walk
/// through that position. A position that is not open cannot be occupied by a
/// person. Each maze has a start position that a person can occupy. The maze
/// is solved if a continuous sequence of open positions starting with the start
/// position and ending with any open position other than the start position
/// along an outside edge of the maze.
///
/// Example maze:
/// start
///  |
///  |
/// # ######################################
/// # ## # ##          #                   #
/// # #     # ########   ################# #
/// # ##### #   #      # #                 #
/// #       # # # ###### # ############### #
/// # ####### # #      # #                 #
/// #         # ######   ################# #
/// # ######### #      # #                 #
/// # #         ###### # ######### #########
/// # # #########   #  # #       #         #
/// # # #         #   ## # ##### ######### #
/// # # ################ # #             # #
/// # #            #   #   # # # # # # # # #
/// # ############ # # # ################# #
/// #            # # # #                   #
/// # ############   # # ###################
/// ### ##   ###########                    --exit
/// #    ###           ################### #
/// # ##     # # # # #                     #
/// ########################################
///
/// In the example maze, '#' indicates a blocked position and ' ' indicates an
/// open position.
class Maze {
public:
    ///
    /// Type used to identify positions within a maze
    struct Location {
        uint16_t x;
        uint16_t y;

        Location(uint16_t anX, uint16_t aY) :
                x(anX),
                y(aY) {
            //prevLoc = this;
        };

        ////
        // return previous location
        ////
        /*Location *&getPrevLoc() {
            return prevLoc;
        };*/

        ////
        // Link to previous locations.
        ////
        /*void setPrevLoc(Location *&newPrevLoc) {
            prevLoc = newPrevLoc;
        };*/

        ////
        // Compares location to another location, returns a true or false value.
        ////
        /*
        bool const &isEqual(Location *anotherLoc) {
            bool equal_value = false;
            if (this->x == anotherLoc->x && this->y == anotherLoc->y) {
                equal_value = true;
            }
            bool const &return_value = equal_value;
            return return_value;
        };*/
    private:
        //Location *prevLoc;
    };

    ///
    /// Virtual destructor
    virtual ~Maze() {
    };

///////////////////////////////////////////////////////////
/// BEGIN Pure virtual member functions to be implemented
/// by concrete subclasses
///////////////////////////////////////////////////////////

    ///
    /// Returns the width of the maze. All open positions within the maze have
    /// X coordinate in the range 0 to width-1.
    virtual uint16_t getWidth() const = 0;

    ///
    /// Returns the length of the maze. All open positions within the maze have
    /// Y coordinate in the range 0 to length-1.
    virtual uint16_t getLength() const = 0;

    ///
    /// Returns the location of the start position in the maze.  The start
    /// position is always open.
    virtual Maze::Location startLocation() const = 0;

    ///
    /// Returns true if and only if the specified location identifies an open
    /// position in the maze. It is an error to specify a location outside the
    /// maze.
    virtual bool isOpenAt(const Maze::Location &aLocation) const = 0;

    //////////////////////////////////////////////////////////////
    /// Set or get the value of any breadcrumb at aLocation.
    /// A value of 0 indicates no breadcrumb is present.
    virtual uint32_t &breadcrumbAt(const Maze::Location &aLocation) = 0;

////////////////////////////////////////////////////////////////////////////////
/// END Pure virtual member functions to be implemented by concrete
////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    /// Returns true if an only if aLocation is within the maze
    bool isInside(const Maze::Location &aLocation) const {
        return (aLocation.x < this->getWidth() &&
                aLocation.y < this->getLength());
    }

    //////////////////////////////////////////////////////////////
    /// Returns true if an only if aLocation is an exit from the
    /// maze
    bool isExit(const Maze::Location &aLocation) const {
        return (aLocation.x == 0 ||
                aLocation.x == this->getWidth() - 1 ||
                aLocation.y == 0 ||
                aLocation.y == this->getLength() - 1)
                &&
                (aLocation.x != this->startLocation().x ||
                        aLocation.y != this->startLocation().y);
    }

    //////////////////////////////////////////////////////////////
    /// This is syntactical sugar for breadcrumbAt(aLocation)
    uint32_t &operator[](const Maze::Location &aLocation) {
        return this->breadcrumbAt(aLocation);
    }
};


////////////////////////////////////////////////////////////////////////////////
/// This function returns a pointer to a newly allocated Maze instance. The
/// caller is responsible for deleting the returned Maze instance.
extern Maze *MakeMaze();

#endif /* defined(__MazeSolver__Maze__) */
