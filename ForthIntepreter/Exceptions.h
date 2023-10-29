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

class ParseError : public ForthExceptions
{
public:
    size_t beginToken;
    size_t endToken;

    explicit ParseError(const std::string& token, size_t _beginToken, size_t _endToken) : beginToken(_beginToken), endToken(_endToken)
    {
        errorType = "Parser Error";
        errorMessage = std::format("Could not parse token: {}", token);
    }

};