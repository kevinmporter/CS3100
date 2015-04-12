//
//  WSUMap.cpp
//  WSUMap
//
//  Created by Erik Buck on 3/8/13.
//  Copyright (c) 2013 WSU. All rights reserved.
//

#include "WSUMap.h"
#include <algorithm>


///////////////////////////////////////////////////////////
uint8_t WSUMap::blockTypeIDAt(
   uint32_t x, uint32_t y, uint32_t z) const
{
   uint8_t result = WSUMap::Air;

   uint32_t modifierX = 0;
   uint32_t modifierY = 0;
   uint32_t modifierZ = 0;

   if (((x % 200 >= 30 && x % 200 <= 35) || (z % 200 >= 30 && z % 200 <= 35))
           || ((x % 200 >= 46 && x % 200 <= 50) || (z % 200 >= 46 && z % 200 <= 50))) {
      modifierY = 1;
   } else if ((x % 200 >= 36 && x % 200 <= 40) && (z % 200 >= 36 && z % 200 <= 40)) {
      modifierY = 2;
   } else if ((x % 200 >= 41 && x % 200 <= 45) && (z % 200 >= 41 && z % 200 <= 45)) {
      modifierY = 3;
   }



   if (y == 0) {
      result = WSUMap::Bedrock;
   } else if (y < 35 + modifierY) {
      if ((x % 200 >= 1 && x % 200 <= 250) && (z % 150 >= 1 && z % 150 <= 200)) {
         result = WSUMap::Water;
      } else {
         result = WSUMap::Stone;
      }
   } else if (y < (36 + modifierY)) {
      if (x % 17 == 0 && z % 7 == 0) {
         result = WSUMap::TallGrass;
      } else if (((x % 13 == 0) && (z % 17 == 0)) || ((x % 13 == 1) && (z % 17 == 0))) {
         result = WSUMap::LiveShrub;
      } else if (x % 29 == 0 && z % 43 == 0) {
         result = WSUMap::Sapling;
      }
      else {
         result = WSUMap::Grass;
      }
      if ((x % 200 >= 1 && x % 200 <= 25) && (z % 150 >= 1 && z % 150 <= 25)) {
         result = WSUMap::Water;
      }
   } else if (y < (37 + modifierY)) {
      if (x % 17 == 0 && z % 7 == 0) {
         result = WSUMap::TallGrass;
      } else if ((x % 13 == 0 && z % 17 == 0) || ((x % 13 == 1) && (z % 17 == 0))) {
         result = WSUMap::LiveShrub;
      } else if (x % 29 == 0 && z % 43 == 0) {
         result = WSUMap::Sapling;
      }

   }
/*   if (x % 17 == 0 && z % 17 == 0 && (y > 35 && y < 37)) {
      result = WSUMap::TallGrass;
   }
   if (((x < 500 && x > 700 && z > 600 && z < 1000)) && y < 36) {
      if ((x < 550 && y < 10 && z < 650) || (x > 660 && y < 10 && z > 900)) {
         result = WSUMap::Dirt;
      } else {
         result = WSUMap::Water;
      }

   }
*/
   /*if (0 == y)
   {
      result = WSUMap::Bedrock;
   }
   else if (35 > y)
   {
      result = WSUMap::Stone;
   }
   else if (36 > y)
   {
      if (z % 17 == 0) {
         result = WSUMap::DeadShrup;
      } else if (z % 7 == 0) {
         result = WSUMap::LiveShrub;
      } else if (z % 5) {
         result = WSUMap::TallGrass;
      } else {
         result = WSUMap::Grass;
      }


      }
   } else if (y > 36) {
      if ((x % 17 == 0 || x % 17 == 1 || x % 17 == 2) && (z % 17 == 0 || z % 17 == 1 || z % 17 == 2)) {
         result = WSUMap::Cloud;
      }
   }*/

   return result;
}
