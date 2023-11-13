#include "UserInterface.h"
#include <iostream>
#include <ranges>


std::string ConsoleInterface::TakeInputFromUser()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsoleInterface::PrintStack(std::stack<StackNumber> stack)
{
    std::cout << std::endl << "Stack:" << std::endl;

    std::vector<StackNumber> stackVector;
    while (!stack.empty())
    {
        stackVector.push_back(stack.top());
        stack.pop();
    }

    for (const auto& number : std::views::reverse(stackVector))
    {
        std::cout << number.variable << " ";
    }

    std::cout << "<- top ";
}

void ConsoleInterface::PrintStackNumber(StackNumber variable)
{
    std::cout << variable.variable << " ";
}

void ConsoleInterface::PrintAscii(StackNumber variable)
{
    std::cout << (char)variable.variable;
}

void ConsoleInterface::PrintString(std::string string)
{
    std::cout << string;
}

void ConsoleInterface::PrintCarriageReturn()
{
    std::cout << std::endl;
}
