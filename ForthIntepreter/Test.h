#pragma once

#include "UserInterface.h"
#include <iostream>

#ifdef _DEBUG
    #define Break() __debugbreak()
#else
    #define Break() abort()
#endif

#define AssertFunction(assertString, result, file, line, value)                                                   \
if (result != value)                                                                                    \
{                                                                                                   \
    std::cout << (std::string("\nAssert: \"") + assertString  + "\" Expected: " + std::to_string(value) + " Got: " + std::to_string(result) + std::string(" Failed in File: ") + std::string(file) + " Line: " + std::to_string(line));   \
    Break();                                                                                        \
}                                                                                                   \

#define ASSERT_TRUE(assertation) AssertFunction(#assertation, assertation, __FILE__, __LINE__,true)

#define ASSERT_FALSE(assertation) AssertFunction(#assertation, assertation, __FILE__, __LINE__,false)

void RunTests(std::shared_ptr<UserInterface> ui);