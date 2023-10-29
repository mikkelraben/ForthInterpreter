#pragma once
#include "standardLibraries.h"
#include "Runtime.h"

class UserInterface
{
public:
    virtual std::string TakeInputFromUser() = 0;
    virtual void PrintStack(std::stack<StackNumber> stack) = 0;
    virtual void PrintStackNumber(StackNumber variable) = 0;
    virtual void PrintAscii(StackNumber ascii) = 0;
    virtual void PrintString(std::string string) = 0;
    virtual void PrintCarriageReturn() = 0;
};

class ConsoleInterface : public UserInterface
{

public:
    std::string TakeInputFromUser() override;
    void PrintStack(std::stack<StackNumber> stack) override;
    void PrintStackNumber(StackNumber variable) override;
    void PrintAscii(StackNumber ascii) override;
    void PrintString(std::string string) override;
    void PrintCarriageReturn() override;
    ConsoleInterface() = default;
};