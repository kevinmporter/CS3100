//
//  CharArrayArray.cpp
//  Project1
//

#include "CharArray.h"
#include "CharArrayArray.h"
#include <assert.h>  // For assert()
#include <algorithm> // For std::min()
#include <iostream> // For std::cout

///////////////////////////////////////////////////////////
//
void CharArrayArray::clear()
{
   while(0 < this->size())
   {
      this->popBack();
   }
}

   
///////////////////////////////////////////////////////////
//
void CharArrayArray::pushBack(CharArray * const &anElement)
{
   this->insertAt(anElement, this->size());
}

   
///////////////////////////////////////////////////////////
//
void CharArrayArray::popBack()
{
   assert(0 < this->size());
   
   this->removeAt(this->size() - 1);
}


///////////////////////////////////////////////////////////
//
void CharArrayArray::append(CharArrayArray &anArray)
{
   const size_t count = anArray.size();
   
   for(size_t i = 0; i < count; i++)
   {
      this->pushBack(anArray[i]);
   }
}


///////////////////////////////////////////////////////////
//
CharArray * &CharArrayArray::operator [](size_t index)
{
   return this->at(index);
}


