//
//  WSUMap.cpp
//  WSUMap
//
//  Created by Erik Buck on 3/8/13.
//  Copyright (c) 2013 WSU. All rights reserved.
//

#include "WSUMap.h"
#include <algorithm>
#include <math.h>
#include <string>

uint8_t WSUMap::setBlockTypeIDAt(
        uint32_t x, uint32_t y, uint32_t z) const {
   uint8_t result = WSUMap::Air;

   uint32_t modifierX = 0;
   uint32_t modifierY = 0;
   uint32_t modifierZ = 0;

   if (y == 0) {
      result = WSUMap::Bedrock;
   } else if (y < 35 + modifierY) {
      if ((x % 200 >= 1 && x % 200 <= 250) && (z % 150 >= 1 && z % 150 <= 200)) {
         result = WSUMap::Water;
      } else {
         result = WSUMap::Stone;
      }
   } else if ((y < (50 - sinf(z / 7.0f)) + ((x / 20) % 3) * 7) ||
              (y < (50 - sinf(x / 7.0f + ((x / 20) % 3) * 6)))) {
      if (x % 17 == 0 && z % 7 == 0) {
         result = WSUMap::TallGrass;
      } else if (x % 7 < sinf(z / 6) * 5) {
         // I wanted to put some leaves here, but the image does not appear to come through correctly.
         result = WSUMap::Dirt;
      }

      else if (((x % 13 == 0) && (z % 17 == 0)) || ((x % 13 == 1) && (z % 17 == 0))) {
         result = WSUMap::LiveShrub;
      } else if (x % 29 == 0 && z % 43 == 0) {
         result = WSUMap::Sapling;
      } else if (x % 43 == 0 && z % 53 == 0) {
         result = WSUMap::GoldOre;
      }
      else {
         result = WSUMap::Grass;
      }
      if ((x % 200 >= 1 && x % 200 <= 25) && (z % 150 >= 1 && z % 150 <= 25)) {
         // Water also does not appear to render properly.
         result = WSUMap::Water;
      }
   } else if ((y < (51 - sinf(z / 7.0f)) + ((x / 20) % 3) * 7) ||
              (y < (51 - sinf(x / 7.0f) + ((x / 20) % 3) * 6))) {
      if (x % 17 == 0 && z % 7 == 0) {
         result = WSUMap::TallGrass;
      } else if (((x % 13 == 0) && (z % 17 == 0)) || ((x % 13 == 1) && (z % 17 == 0))) {
         result = WSUMap::LiveShrub;
      } else if (x % 7 < (sinf(z / 6) * 5) && ((rand() % 10) > 8)) {
         result = WSUMap::Sapling;
      } else if (x % 43 == 0 && z % 53 == 0) {
         result = WSUMap::GoldOre;
      }
   }

   else if (y > (256 - (sinf(z / 120.0f) * 150))) {
      result = WSUMap::Cloud;
   }

   return result;
}


///////////////////////////////////////////////////////////
uint8_t WSUMap::blockTypeIDAt(
   uint32_t x, uint32_t y, uint32_t z) const
{
   uint8_t result = WSUMap::Air;
   std::weak_ptr<triple> *t = new std::weak_ptr<triple(x, y, z)>;

   try  {
      result = blockMap.find(*t);
   } catch (std::exception ex) {
      result = setBlockTypeIDAt(x, y, z);
      //std::pair<triple*, uint8_t> *pair = new std::pair<triple*, uint8_t>(t, result);
   }

   return result;
}

