
#include <stdlib.h>
#include "WSUCraftService.h"
#include "WSUMap.h"


///////////////////////////////////////////////////////////
WSUMap map;


///////////////////////////////////////////////////////////
int main(void)
{
   WSUCraftService netService;
   
   netService.provideMapDataToClients(map);
   
   exit(0);
   return (0);        
}
