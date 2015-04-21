//
//  WSUMap.h
//  WSUMap
//
//

#ifndef __WSUMap__WSUMap__
#define __WSUMap__WSUMap__

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <map>
#include <string>


class triple {
public:
   uint32_t x;
   uint32_t y;
   uint32_t z;

   triple(uint32_t nx, uint32_t ny, uint32_t nz) {
      x = nx;
      y = ny;
      z = nz;
   }

   bool operator<(const triple &other) const {
      return (x < other.x && y < other.y && z < other.z);
   }
};

///////////////////////////////////////////////////////////
/// Instances of the WSUMap class encapsulate a "map"
/// composed of block type identifiers.
///
/// The conceptual map is a 3 dimensional volume containing
/// blocks representing bedrock, stone, dirt, grass, wood,
/// leaves, lava, water, air, clouds, etc. Think of each
/// block as a 1 meter cube within the 3 dimensional
/// volume.
///
/// The "map" data structure provides random access to
/// stored block type identifiers as if the block type
/// identifier data is stored as a 3 dimensional array in
/// memory. To find out what type of block is in the map at
/// position {1330, 52, 40400}, a program calls WSUMap's
/// blockTypeIDAt(uint32_t x, uint32_t y, uint32_t z)
/// member function:
///
///uint8_t blocktypeID = blockTypeIDAt(1330, 52, 40400);
///
/// The WSUMap class is intended to encapsulate very large
/// maps. Assume each map volume is at least 65536 blocks
/// wide and 65536 blocks long and 256 blocks high. As a
/// practical matter, if one byte is used to store each
/// block type identifier and every position in the map is
/// represented by a block type identifier, the entire map
/// would require 1,099,511,627,776 bytes (1 Terabyte) of
/// memory. Therefore, some data structure other than a
/// simple 3 dimensional array in memory should most likely
/// be used.
///
/// Assumed usage patterns for the WSUMap class enable
/// potential optimizations for both data storage and data
/// access:
///
/// 1) Assume approximately half of all block positions
/// are occupied by "air". Therefore, a data structure
/// can be implemented that doesn't store any value for
/// positions occupied by "air". If there is no value
/// stored for a particular position, blockTypeIDAt() can
/// return the block type identifier for "air" by default.
/// This optimization alone can reduce required memory to
/// approximately half a Terabyte!
///
/// 2) The map is intended to be rendered using 3D computer
/// graphics. There is a limit to the number of blocks
/// that can be meaningfully rendered and presented to
/// a user at one time. For example, blocks behind the
/// user's 3D view point can't be seen and perhaps don't
/// need to be stored in memory. However, the user's
/// 3D point of view is expected to change frequently.
/// The user's position in the map can change, and the
/// direction the user is looking can change. Therefore,
/// block positions that were once behind the 3D view
/// point may be in view at another time.
///
/// 3) Most users will not invest enough time to view
/// every part of the map. Assuming a user changes the
/// position of his/her point of view at a rate of
/// 3 meters per second, it will take the user 8.6 hours
/// to move the point of view approximately 92,682 meters
/// from one corner of the map to the opposite corner.
/// However, users may be able to "teleport" the view
/// point large distances in an instant, but when doing so
/// does not view all of the terrain between the old
/// and new view points.
/// 
/// Your assignment is to implement the blockTypeIDAt() and
/// setBlockTypeIDAt() member functions of the following
/// WSUMap class. Your instructor will test your
/// implementation within an application that enables multiple
/// users to simultaneously and interactively view portions
/// of a WSUMap instance.
///
/// Your implementation must compile and run on either of WSU's
/// Thor or Gandalf servers. To make the map interesting to
/// view, write code to fill an instance of your WSUMap class
/// with blocks representing terrain (bedrock, stone, dirt,
/// grass, air, etc.) Make sure approximately half the volume
/// of the map is filled with Air. The top plain of blocks i.e.
/// all block positions with height equal 255 must be air.
/// All bottom block positions, i.e. all block positions with
/// height 0 must be "bedrock".
///
/// Although you don't have to implement it yet, consider how
/// a map can be saved and later reloaded?
///
/// DO NOT CRASH THE WSU SERVERS OR ATTEMPT TO CREATE HALF
/// TERABYTE FILES OR ATTEMPT TO ALLOCATE MORE THAT A FEW
/// GIGABYTES OF RAM!
///
/// Your instructor's solution requires no more than 30
/// Megabytes of RAM at any one time to store a map.
///
class WSUMap
{
public:
   // arbitrary large dimensions
   static const uint32_t width = 1 << 12;
   static const uint32_t length = 1 << 12;
   static const uint32_t height = 1 << 8;
   static const uint32_t total = width * length * height;

   std::map<uint32_t, uint8_t> blockMap;

   


   WSUMap()
   {
   }

  uint32_t getKey(uint32_t x,
                  uint32_t y,
                  uint32_t z) const;
   
   
   //////////////////////////////////////////////
   /// This function returns the block type
   /// identifier for the specified x, y, z
   /// position within the map.
   uint8_t blockTypeIDAt(
      uint32_t x, uint32_t y, uint32_t z) const;

   uint8_t setBlockTypeIDAt(
           uint8_t someBlock, uint32_t x, uint32_t y, uint32_t z);
   
   ////////////////////////////////////////////////////////
   /// The following values enumerate a subset of possible
   /// block type identifiers. The identifier 0 is
   /// reserved to represent "Air".
   enum
   {
      Air = 255,
      Bedrock = 0,
      Stone,
      Dirt,
      Grass,
      Water,
      Lava,
      Sand,
      Gravel,
      GoldOre,
      IronOre,
      CoalOre,
      WoodenPlank,
      Sapling,
      Wood,
      Leaves,
      DeadShrup,
      LiveShrub,
      TallGrass,
      Cloud = 66,
   };
};



#endif /* defined(__WSUMap__WSUMap__) */
