#include "ConcreteCharArray.h"      // Student supplies this file
#include "ConcreteCharArrayArray.h" // Student supplies this file
#include <string>
#include <fstream>
#include <iostream>


///////////////////////////////////////////////////////////
// Read all words in a dictionary, create ConcreteCharArray
// instances storing the characters in each word, create
// a ConcreteCharArrayArray instance storing all the
// ConcreteCharArray instances, print the number of words
// read to stdout, and print a random sample of the words
// to stdout.
int main(int argc, const char * argv[])
{
   const char *alternativePath = "/usr/share/dict/words";
   const char *defaultPath = "/usr/dict/words";
   const int numberOfWordsToFind = 20;
   
   ConcreteCharArrayArray charArrayArray;
   std::ifstream *infilePtr = new std::ifstream(defaultPath);
   
   if(!infilePtr->good())
   {
      delete infilePtr;
      
      infilePtr = new std::ifstream(alternativePath);
   }
   
   if(!infilePtr->good())
   {
      std::cout << "Error: " <<
         "Failed to open file <" <<
         defaultPath <<
         ">" << std::endl;
      std::cout << "Error: " <<
         "Failed to open file <" <<
         alternativePath <<
         ">" << std::endl;
   }
   else
   {
      std::string line;
      
      while (std::getline(*infilePtr, line))
      {
         ConcreteCharArray * const newString =
            new ConcreteCharArray;
         newString->append(line.c_str(), line.size());
         
         charArrayArray.pushBack(newString);
      }
      
      const size_t numberOfWords =
         charArrayArray.size();
      
      std::cout << "Number of words: " <<
         numberOfWords << std::endl;
      
      for(int i = 0; i < numberOfWordsToFind; i++)
      {
         charArrayArray.at(
            rand() % numberOfWords)->print();
         std::cout << std::endl;
      }
   }

   delete infilePtr;
   exit(0);
   return 0;
}

