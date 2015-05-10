//
//  WSUCraftService.cpp
//  WSUCraftServer
//
//  Created by Erik Buck on 3/31/13.
//  Copyright (c) 2013 WSU. All rights reserved.
//

#include "WSUCraftService.h"
#include <zlib.h>

///////////////////////////////////////////////////////////
#include <unistd.h>         // read() close()
#include <stdlib.h>         // exit()
#include <stdio.h>          // printf()
#include <string.h>         // strcpy(),strerror(), strlen()
#include <fcntl.h>          // file i/o constants
#include <sys/stat.h>       // file i/o constants
#include <errno.h>

///////////////////////////////////////////////////////////
// FOR BSD UNIX/LINUX
#include <sys/types.h>      //
#include <netinet/in.h>     //
#include <sys/socket.h>     // socket system calls
#include <arpa/inet.h>      // socket system calls (bind)

///////////////////////////////////////////////////////////
#define PORT_NUM (8081)        // Port number
#define PEND_CONNECTIONS (5) // num connections to hold
#define BUFFER_SIZE (2047)     // buffer size in bytes


#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

void reportIPInfo()
{
   struct ifaddrs * ifAddrStruct = NULL;
   struct ifaddrs * ifa = NULL;
   void * tmpAddrPtr = NULL;

   getifaddrs(&ifAddrStruct);

   for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
   {
      if (ifa ->ifa_addr->sa_family == AF_INET)
      { // check it is IP4
         // is a valid IP4 Address
         tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
         char addressBuffer[INET_ADDRSTRLEN];
         inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
         printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
      }
      else if (ifa->ifa_addr->sa_family == AF_INET6)
      { // check it is IP6
         // is a valid IP6 Address
         tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
         char addressBuffer[INET6_ADDRSTRLEN];
         inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
         printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
      }
   }

   if (ifAddrStruct != NULL)
   {
      freeifaddrs(ifAddrStruct);
   }
}

///////////////////////////////////////////////////////////
void WSUCraftService::provideMapDataToClients(
                                              const WSUMap &aMap)
{
   ////////////////////////////////////////////////////////
   // local variables for socket connection
   unsigned int          serverSid;     // Server socket
   struct sockaddr_in    serverAddr;  // Server address
   unsigned int          clientSid;     // Client socket
   struct sockaddr_in    clientAddr;  // Client address
   socklen_t             addrLength;     // Address length

   ////////////////////////////////////////////////////////
   // create a new socket
   serverSid = socket(AF_INET, SOCK_STREAM, 0);

   ////////////////////////////////////////////////////////
   // fill-in address information, and then bind it
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_port = htons(PORT_NUM);
   serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   bind(serverSid, (struct sockaddr *)&serverAddr,
        sizeof(serverAddr));

   ////////////////////////////////////////////////////////
   // Listen for connections and then accept
   listen(serverSid, PEND_CONNECTIONS);

   reportIPInfo();
   printf("WSUCraftServer Started on Port:%d\n", PORT_NUM);

   ////////////////////////////////////////////////////////
   // Server main loop
   while(true)
   {
      // wait for the next client request to arrive
      addrLength = sizeof(clientAddr);
      clientSid = accept(serverSid,
                         (struct sockaddr *)&clientAddr,
                         &addrLength);

      if (clientSid == 0)
      {
         fprintf(stderr,
                 "ERROR: Failed to create client socket \n");
         close(serverSid);  // close the primary socket
         exit(-1);
      }
      else
      {
         //         fprintf(stderr,
         //                 "Accepted connection ...\n");

         char recvBuffer[BUFFER_SIZE+1];
         ssize_t recvLength;

         recvLength = recv(clientSid,
                           recvBuffer,
                           BUFFER_SIZE,
                           0);

         if (0 > recvLength)
         {
            fprintf(stderr,
                    "Error: failed recv ...\n");
         }
         else
         {
            //            fprintf(stderr,
            //                    "Received %zd bytes ...\n", recvLength);
            processReceivedRequest(
                                   recvBuffer, recvLength, aMap, clientSid);
         }
         close(clientSid);
         clientSid = 0;
      }
   }

   fprintf(stderr,
           "Closing ...\n");
   ////////////////////////////////////////////////////////
   // Close the server secket
   close(serverSid);  // close the primary socket
}


///////////////////////////////////////////////////////////
void WSUCraftService::processReceivedRequest(
                                             const char *recvBuffer,
                                             ssize_t recvLength,
                                             const WSUMap &aMap,
                                             unsigned int clientSid)
{
   const uint32_t chunkWidth = 32;
   const uint32_t chunkHeight = 256;
   const uint32_t chunkLength = 32;
   uint32_t x;
   uint32_t z;

   sscanf(recvBuffer, "%u %u", &x, &z);

   if((x + chunkWidth - 1) < aMap.width && (z + chunkLength - 1) < aMap.length)
   {
      uint8_t chunkStorage[chunkWidth][chunkHeight][chunkLength];
      //memset(chunkStorage, WSUMap::Air, sizeof(chunkStorage));

      // Collect all the data for a chunk
      for(uint32_t i = 0; i < chunkWidth; i++)
      {
         for(uint32_t j = 0; j < chunkHeight; j++)
         {
            for(uint32_t k = 0; k < chunkLength; k++)
            {
               chunkStorage[i][j][k] =
               aMap.blockTypeIDAt(i + x, j, k + z);
            }
         }
      }

      // Send the compressed chunk data
      Bytef compressedChunkStorage[chunkWidth][chunkHeight][chunkLength];
      z_stream strm;

      strm.zalloc = Z_NULL;
      strm.zfree = Z_NULL;
      strm.opaque = Z_NULL;
      strm.total_out = 0;
      strm.next_in = (Bytef *)chunkStorage;
      strm.avail_in = (uInt)sizeof(chunkStorage);

      // Compresssion Levels:
      //   Z_NO_COMPRESSION
      //   Z_BEST_SPEED
      //   Z_BEST_COMPRESSION
      //   Z_DEFAULT_COMPRESSION
      if (Z_OK != deflateInit2(&strm,
                               Z_DEFAULT_COMPRESSION,
                               Z_DEFLATED,
                               (15+16),
                               8,
                               Z_DEFAULT_STRATEGY))
      {
         fprintf(stderr, "Error: deflateInit2 ...\n");
         return;
      }

      do
      {
         strm.next_out =
         (Bytef *)(compressedChunkStorage + strm.total_out);
         strm.avail_out = (uInt)(sizeof(compressedChunkStorage) -
                                 (size_t)strm.total_out);

         deflate(&strm, Z_FINISH);

      }
      while (strm.avail_out == 0);

      deflateEnd(&strm);

      uint32_t numBytesToSend = (uint32_t)strm.total_out;
      send(clientSid, &numBytesToSend, sizeof(numBytesToSend), 0);
      ssize_t count = send(clientSid,
                           compressedChunkStorage,
                           numBytesToSend,
                           0);

      printf("Chunk at {%u %u} Num bytes sent = %lu\n", x, z, (unsigned long)count);
   }
   else
   {
      printf("Chunk at {%u %u} can't be sent\n", x, z);
   }
}
