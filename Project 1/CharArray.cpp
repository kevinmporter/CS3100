//
//  CharArray.cpp
//  Project1
//

#include "CharArray.h"
#include <assert.h>  // For assert()
#include <algorithm> // For std::min()

///////////////////////////////////////////////////////////
//
void CharArray::clear()
{
   while(0 < this->size())
   {
      this->popBack();
   }
}

   
///////////////////////////////////////////////////////////
//
void CharArray::pushBack(char &anElement)
{
   this->insertAt(anElement, this->size());
}

   
///////////////////////////////////////////////////////////
//
void CharArray::popBack()
{
   assert(0 < this->size());
   
   this->removeAt(this->size() - 1);
}


///////////////////////////////////////////////////////////
//
void CharArray::append(CharArray &anArray)
{
   const size_t count = anArray.size();
   
   for(size_t i = 0; i < count; i++)
   {
      this->pushBack(anArray[i]);
   }
}


///////////////////////////////////////////////////////////
//
char &CharArray::operator [](size_t index)
{
   return this->at(index);
}


///////////////////////////////////////////////////////////
//
void CharArray::print(
   std::ostream &stream) const
{
   const size_t count = this->size();
   
   for(size_t i = 0; i < count; i++)
   {
      stream << this->at(i);
   }
}


///////////////////////////////////////////////////////////
//
void CharArray::append(const char *aString,
   const size_t count)
{
   for(size_t i = 0; i < count; i++)
   {
      char temp(aString[i]);
      this->pushBack(temp);
   }
}
