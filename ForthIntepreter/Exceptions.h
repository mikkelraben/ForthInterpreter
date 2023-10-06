#pragma once
#include "standardLibraries.h"

class ForthExceptions
{
public:
    std::string errorMessage;
    std::string errorType;
    virtual ~ForthExceptions() {};
};

class RuntimeError : public ForthExceptions
{
public:
    explicit RuntimeError(const std::string& _errorMessage) 
    { 
        errorType = "Runtime Error"; 
        errorMessage = _errorMessage; 
    }
};

class SyntaxError : public ForthExceptions
{
public:
    explicit SyntaxError(const std::string& _errorMessage) 
    { 
        errorType = "Syntax Error"; 
        errorMessage = _errorMessage; 
    }
};