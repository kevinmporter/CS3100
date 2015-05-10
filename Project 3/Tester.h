//
//  Tester.h
//  Project3
//
//  Created by Erik Buck on 2/12/15.
//  Copyright (c) 2015 WSU. All rights reserved.
//

#ifndef Project3_Tester_h
#define Project3_Tester_h

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ConcreteArray.h"


////////////////////////////////////////////////////////
typedef ConcreteArray<long *> longPtrArray;


///////////////////////////////////////////////////////////
/// This class exists solely to group related test
/// functions, types, and variables together.
struct Tester
{
   ////////////////////////////////////////////////////////
   ///
   static std::ostream *outputPtr;
   
   ////////////////////////////////////////////////////////
   /// Function to add a constant to number to value at
   /// address stored in argument
   template<typename numericType, numericType constant=3>
   static numericType *addConstantViaPointer(numericType *aPtr)
   {
      assert(nullptr != aPtr);
      
      *aPtr = *aPtr + constant;
      return aPtr;
   }
   
   
   ////////////////////////////////////////////////////////
   /// A "Functor" to transform values stored in a
   /// collection.  A functor is a class that works like
   /// a function by overloading the () operator.
   template <class T> struct transformIterable
   {
      T *operator() (T *x) const
      {
         std::transform(x->begin(), x->end(), x->begin(),
            addConstantViaPointer<long, 19>);
         return x;
      }
   };
   
   
   ////////////////////////////////////////////////////////
   static void appendLongOutput(long *aPtr)
   {
      (*Tester::outputPtr) << *aPtr << " ";
   }
   
   
   ////////////////////////////////////////////////////////
   template<typename T>
   static void appendIterableOutput(T *aPtr)
   {
      (*Tester::outputPtr)  << "(";
      std::copy(aPtr->begin(), aPtr->end(),
                std::ostream_iterator<void *>(*outputPtr, " "));
      (*Tester::outputPtr)  << ")\n";
   }
   
   
   ////////////////////////////////////////////////////////
   template<typename T>
   static void appendIterableOfIterableOutput(T *aPtr)
   {
      (*Tester::outputPtr)  << "(";
      std::for_each(aPtr->begin(), aPtr->end(), appendLongOutput);
      (*Tester::outputPtr)  << ")\n";
   }
   
   
   ////////////////////////////////////////////////////////
   template<typename T1, typename T2>
   static void performTestTransformOriginal()
   {
      // C Array used to populate new c++ arrays
      long * const cArray[] =
      {
         new long(100),
         new long(-3),
         new long(-2),
         new long(-1),
         new long(0),
         new long(1),
         new long(2),
         new long(3),
         new long(-100),
         new long(0),
      };
      
      T1 vectorPtrVector;
      
      // Create instances of ConcreteArray of ConcreteArray of pointers
      vectorPtrVector.push_back(
         new T2(cArray, cArray + (sizeof(cArray) / sizeof(const long *))));
      vectorPtrVector.push_back(
         new T2(cArray, cArray + (sizeof(cArray) / sizeof(const long *))));
      
      std::for_each(vectorPtrVector.begin(), vectorPtrVector.end(),
                    appendIterableOfIterableOutput<T2>);
      
      std::transform(vectorPtrVector.begin(),
                     vectorPtrVector.end(),
                     vectorPtrVector.begin(),
                     transformIterable<T2>());
      
      std::for_each(vectorPtrVector.begin(), vectorPtrVector.end(),
                    appendIterableOfIterableOutput<T2>);
   }
   
   
   ////////////////////////////////////////////////////////
   template<typename T1, typename T2>
   static void performTestTransformShallowCopy()
   {
      // C Array used to populate new c++ arrays
      long * const cArray[] =
      {
         new long(100),
         new long(-3),
         new long(-2),
         new long(-1),
         new long(0),
         new long(1),
         new long(2),
         new long(3),
         new long(-100),
         new long(0),
      };
      
      // Collect initial values
      std::ostringstream testOutputStream1;
      Tester::outputPtr = &testOutputStream1;
      
      T1 vectorPtrVector;
      
      // Create instances of ConcreteArray of ConcreteArray of pointers
      vectorPtrVector.push_back(
         new T2(cArray, cArray + (sizeof(cArray) / sizeof(const long *))));
      vectorPtrVector.push_back(
         new T2(cArray, cArray + (sizeof(cArray) / sizeof(const long *))));
      
      std::for_each(vectorPtrVector.begin(), vectorPtrVector.end(),
                    appendIterableOfIterableOutput<T2>);
      
      T1 shallowCopy(vectorPtrVector);
      
      // Collect test values
      std::ostringstream testOutputStream2;
      Tester::outputPtr = &testOutputStream2;
      
      std::for_each(shallowCopy.begin(), shallowCopy.end(),
                    appendIterableOfIterableOutput<T2>);
      
      if(testOutputStream1.str() != testOutputStream2.str())
      {
         std::cerr << "Test Failed!\n\tExpected:\n";
         std::cerr << testOutputStream1.str() << std::endl;
         std::cerr << "\tActual:\n";
         std::cerr << testOutputStream2.str() << std::endl;
         
         exit(-1);
      }
      
      // Change final values via pointers in the copy
      // (should change final values of original too because both
      //  original and copy have pointers to the same final values)
      std::transform(shallowCopy.begin(),
                     shallowCopy.end(),
                     shallowCopy.begin(),
                     transformIterable<T2>());
      
      // Collect test values
      std::ostringstream testOutputStream3;
      Tester::outputPtr = &testOutputStream3;
      
      std::for_each(vectorPtrVector.begin(), vectorPtrVector.end(),
                    appendIterableOfIterableOutput<T2>);
      
      // Collect test values
      std::ostringstream testOutputStream4;
      Tester::outputPtr = &testOutputStream4;
      
      std::for_each(shallowCopy.begin(), shallowCopy.end(),
                    appendIterableOfIterableOutput<T2>);
      
      if(testOutputStream3.str() != testOutputStream4.str())
      {
         std::cerr << "Test Failed!\n\tExpected:\n";
         std::cerr << testOutputStream3.str() << std::endl;
         std::cerr << "\tActual:\n";
         std::cerr << testOutputStream4.str() << std::endl;
         
         exit(-1);
      }
      
      Tester::outputPtr = &std::cout;
   }
   
   
   ////////////////////////////////////////////////////////
   template<typename T1, typename T2>
   static void performTestTransformShallowCopy2()
   {
      // C Array used to populate new c++ arrays
      long * const cArray[] =
      {
         new long(100),
         new long(-3),
         new long(-2),
         new long(-1),
         new long(0),
         new long(1),
         new long(2),
         new long(3),
         new long(-100),
         new long(0),
      };
      
      // Collect initial values
      std::ostringstream testOutputStream1;
      Tester::outputPtr = &testOutputStream1;
      
      T1 vectorPtrVector;
      
      // Create instances of ConcreteArray of ConcreteArray of pointers
      vectorPtrVector.push_back(
         new T2(cArray, cArray + (sizeof(cArray) / sizeof(const long *))));
      vectorPtrVector.push_back(
         new T2(cArray, cArray + (sizeof(cArray) / sizeof(const long *))));
      
      std::for_each(vectorPtrVector.begin(), vectorPtrVector.end(),
                    appendIterableOutput<T2>);
      
      T1 shallowCopy(vectorPtrVector);
      
      // Collect test values
      std::ostringstream testOutputStream2;
      Tester::outputPtr = &testOutputStream2;
      
      std::for_each(shallowCopy.begin(), shallowCopy.end(),
                    appendIterableOutput<T2>);
      
      if(testOutputStream1.str() != testOutputStream2.str())
      {
         std::cerr << "Test Failed!\n\tExpected:\n";
         std::cerr << testOutputStream1.str() << std::endl;
         std::cerr << "\tActual:\n";
         std::cerr << testOutputStream2.str() << std::endl;
         
         exit(-1);
      }
      
      // Change final values via pointers in the copy
      // (should change final values of original too because both
      //  original and copy have pointers to the same final values)
      std::transform(shallowCopy.begin(),
                     shallowCopy.end(),
                     shallowCopy.begin(),
                     transformIterable<T2>());
      
      // Collect test values
      std::ostringstream testOutputStream3;
      Tester::outputPtr = &testOutputStream3;
      
      std::for_each(vectorPtrVector.begin(), vectorPtrVector.end(),
                    appendIterableOutput<T2>);
      
      // Collect test values
      std::ostringstream testOutputStream4;
      Tester::outputPtr = &testOutputStream4;
      
      std::for_each(shallowCopy.begin(), shallowCopy.end(),
                    appendIterableOutput<T2>);
      
      if(testOutputStream3.str() != testOutputStream4.str())
      {
         std::cerr << "Test Failed!\n\tExpected:\n";
         std::cerr << testOutputStream3.str() << std::endl;
         std::cerr << "\tActual:\n";
         std::cerr << testOutputStream4.str() << std::endl;
         
         exit(-1);
      }
      
      Tester::outputPtr = &std::cout;
   }
   
   
   ////////////////////////////////////////////////////////
   template<typename T1, typename T2>
   static void performTestTransformDeepCopy()
   {
      // C Array used to populate new c++ arrays
      long * const cArray[] =
      {
         new long(100),
         new long(-3),
         new long(-2),
         new long(-1),
         new long(0),
         new long(1),
         new long(2),
         new long(3),
         new long(-100),
         new long(0),
      };
      
      // Collect initial values
      std::ostringstream testOutputStream1;
      Tester::outputPtr = &testOutputStream1;
      
      T1 vectorPtrVector;
      
      // Create instances of ConcreteArray of ConcreteArray of pointers
      vectorPtrVector.push_back(
         new T2(cArray, cArray + (sizeof(cArray) / sizeof(const long *))));
      vectorPtrVector.push_back(
         new T2(cArray, cArray + (sizeof(cArray) / sizeof(const long *))));
      
      std::for_each(vectorPtrVector.begin(), vectorPtrVector.end(),
                    appendIterableOutput<T2>);
      
      T1 *aDeepCopy = deepCopy<T1>(&vectorPtrVector);
      
      // Collect test values
      std::ostringstream testOutputStream2;
      Tester::outputPtr = &testOutputStream2;
      
      std::for_each(aDeepCopy->begin(), aDeepCopy->end(),
                    appendIterableOutput<T2>);
      
      if(testOutputStream1.str() == testOutputStream2.str())
      {
         std::cerr << "Test Failed!\n\tExpected contents to be different:\n";
         std::cerr << testOutputStream1.str() << std::endl;
         std::cerr << "\tvs.\n";
         std::cerr << testOutputStream2.str() << std::endl;
         
         exit(-1);
      }
      
      // Change final values via pointers in the copy
      // (should change final values of original too because both
      //  original and copy have pointers to the same final values)
      std::transform(aDeepCopy->begin(),
                     aDeepCopy->end(),
                     aDeepCopy->begin(),
                     transformIterable<T2>());
      
      // Collect test values
      std::ostringstream testOutputStream3;
      Tester::outputPtr = &testOutputStream3;
      
      std::for_each(vectorPtrVector.begin(), vectorPtrVector.end(),
                    appendIterableOutput<T2>);
      
      // Collect test values
      std::ostringstream testOutputStream4;
      Tester::outputPtr = &testOutputStream4;
      
      std::for_each(aDeepCopy->begin(), aDeepCopy->end(),
                    appendIterableOutput<T2>);
      
      if(testOutputStream3.str() == testOutputStream4.str())
      {
         std::cerr << "Test Failed!\n\tExpected contents to be different:\n";
         std::cerr << testOutputStream3.str() << std::endl;
         std::cerr << "\tvs.\n";
         std::cerr << testOutputStream4.str() << std::endl;
         
         exit(-1);
      }
      
      Tester::outputPtr = &std::cout;
   }
   
   
   
   
   ////////////////////////////////////////////////////////
   template<typename T1, typename T2>
   static void performTestTransformDeepAssignment()
   {
      // C Array used to populate new c++ arrays
      long * const cArray[] =
      {
         new long(100),
         new long(-3),
         new long(-2),
         new long(-1),
         new long(0),
         new long(1),
         new long(2),
         new long(3),
         new long(-100),
         new long(0),
      };
      
      // Collect initial values
      std::ostringstream testOutputStream1;
      Tester::outputPtr = &testOutputStream1;
      
      T1 vectorPtrVector;
      T1 aDeepAssignment;
      
      // Create instances of ConcreteArray of ConcreteArray of pointers
      vectorPtrVector.push_back(
         new T2(cArray, cArray + (sizeof(cArray) / sizeof(const long *))));
      vectorPtrVector.push_back(
         new T2(cArray, cArray + (sizeof(cArray) / sizeof(const long *))));
      
      std::for_each(vectorPtrVector.begin(), vectorPtrVector.end(),
                    appendIterableOutput<T2>);
      
      // Test assignment operator
      aDeepAssignment = vectorPtrVector;
      
      // Collect test values
      std::ostringstream testOutputStream2;
      Tester::outputPtr = &testOutputStream2;
      
      std::for_each(aDeepAssignment.begin(), aDeepAssignment.end(),
                    appendIterableOutput<T2>);
      
      if(testOutputStream1.str() == testOutputStream2.str())
      {
         std::cerr << "Test Failed!\n\tExpected contents to be different:\n";
         std::cerr << testOutputStream1.str() << std::endl;
         std::cerr << "\tvs.\n";
         std::cerr << testOutputStream2.str() << std::endl;
         
         exit(-1);
      }
      
      // Change final values via pointers in the copy
      // (should change final values of original too because both
      //  original and copy have pointers to the same final values)
      std::transform(aDeepAssignment.begin(),
                     aDeepAssignment.end(),
                     aDeepAssignment.begin(),
                     transformIterable<T2>());
      
      // Collect test values
      std::ostringstream testOutputStream3;
      Tester::outputPtr = &testOutputStream3;
      
      std::for_each(vectorPtrVector.begin(), vectorPtrVector.end(),
                    appendIterableOfIterableOutput<T2>);
      
      // Collect test values
      std::ostringstream testOutputStream4;
      Tester::outputPtr = &testOutputStream4;
      
      std::for_each(aDeepAssignment.begin(), aDeepAssignment.end(),
                    appendIterableOfIterableOutput<T2>);
      
      if(testOutputStream3.str() == testOutputStream4.str())
      {
         std::cerr << "Test Failed!\n\tExpected contents to be different:\n";
         std::cerr << testOutputStream3.str() << std::endl;
         std::cerr << "\tvs.\n";
         std::cerr << testOutputStream4.str() << std::endl;
         
         exit(-1);
      }
      
      Tester::outputPtr = &std::cout;
   }
   
   
   static void performTestWorksLikeVector()
   {
      // Collect initial values
      std::ostringstream testOutputStream1;
      Tester::outputPtr = &testOutputStream1;
      
      performTestTransformOriginal<std::vector<longPtrArray *>, longPtrArray>();
      
      // Collect test values
      std::ostringstream testOutputStream2;
      Tester::outputPtr = &testOutputStream2;
      
      performTestTransformOriginal<ConcreteArray<longPtrArray *>, longPtrArray>();
      
      if(testOutputStream1.str() != testOutputStream2.str())
      {
         std::cerr << "Test Failed!\n\tExpected:\n";
         std::cerr << testOutputStream1.str() << std::endl;
         std::cerr << "\tActual:\n";
         std::cerr << testOutputStream2.str() << std::endl;
         
         exit(-1);
      }
   }

};


#endif
