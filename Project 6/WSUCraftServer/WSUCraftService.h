//
//  WSUCraftService.h
//  WSUCraftServer
//
//  Created by Erik Buck on 3/31/13.
//  Copyright (c) 2013 WSU. All rights reserved.
//

#ifndef __WSUCraftServer__WSUCraftService__
#define __WSUCraftServer__WSUCraftService__

#include "WSUMap.h"
#include <stdio.h>  // For ssize_t

class WSUCraftService
{
public:
   void provideMapDataToClients(WSUMap &aMap);
   
private:
   void processReceivedRequest(const char *recvBuffer,
      ssize_t recvLength,
      WSUMap &aMap,
      unsigned int clientSid);
};

#endif /* defined(__WSUCraftServer__WSUCraftService__) */
