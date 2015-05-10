//
//  main.cpp
//  Project3
//
//  Created by Erik Buck on 2/12/15.
//  Copyright (c) 2015 WSU. All rights reserved.
//

#include "Tester.h"


////////////////////////////////////////////////////////
// Tests ConcreteArray of ConcreteArray of pointers for
// iterator, deep copy, and assignment.
int main(int argc, const char * argv[])
{
   ///////////////////////////////////////////////////////////////////////////////
   // Test 1
   {
      std::cout << "Test 1 Started: Transform Original\n";
      Tester::performTestWorksLikeVector();
      std::cout << "Test 1 Passed:\n";
   }
   
   ///////////////////////////////////////////////////////////////////////////////
   // Test 2
   {
      std::cout << "Test 2 Started: Transform Shallow Copy\n";
      Tester::performTestTransformShallowCopy<std::vector<longPtrArray *>,
         longPtrArray>();
      Tester::performTestTransformShallowCopy<ConcreteArray<longPtrArray *>,
         longPtrArray>();
      std::cout << "Test 2 Passed:\n";
   }
   
   ///////////////////////////////////////////////////////////////////////////////
   // Test 3
   {
      std::cout << "Test 3 Started: Transform Shallow Copy\n";
      Tester::performTestTransformShallowCopy2<std::vector<longPtrArray *>,
         longPtrArray>();
      Tester::performTestTransformShallowCopy2<ConcreteArray<longPtrArray *>,
         longPtrArray>();
      std::cout << "Test 3 Passed:\n";
   }
   
   ///////////////////////////////////////////////////////////////////////////////
   // Test 4
   {
      std::cout << "Test 4 Started: Transform Deep Copy\n";
      Tester::performTestTransformDeepCopy<ConcreteArray<longPtrArray *>,
         longPtrArray>();
      std::cout << "Test 4 Passed:\n";
   }
   
   ///////////////////////////////////////////////////////////////////////////////
   // Test 5
   {
      std::cout << "Test 5 Started: Transform Deep Assignment operator\n";
      Tester::performTestTransformDeepAssignment<ConcreteArray<longPtrArray *>,
         longPtrArray>();
      std::cout << "Test 5 Passed:\n";
   }
   
   exit(0);
   return 0;
}


///////////////////////////////////////////////////////////////////////////////
std::ostream *Tester::outputPtr = &std::cout;
