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


///////////////////////////////////////////////////////////
uint8_t WSUMap::blockTypeIDAt(
   uint32_t x, uint32_t y, uint32_t z) const
{
   uint8_t result = WSUMap::Air;
   
   if(0 == y)
   {
      result = WSUMap::Bedrock;
   }
   else if(35 > y)
   {
      result = WSUMap::Stone;
   }
   else if(y < (45 + sinf(z / 16.0f) * 10 + ((x / 16) % 2) * 15))
   {
      result = WSUMap::Dirt;
   }   
   else if(40 > y)
   {
      result = WSUMap::Grass;
   }   
   else if(85 > y && y > 75 && 0 == (random() % 16))
   {
      result = WSUMap::Cloud;
   }   
   
   return result;
}

