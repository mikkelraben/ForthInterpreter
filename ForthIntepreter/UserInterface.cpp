#include "UserInterface.h"
#include <iostream>

std::string TakeInputFromUser()
{
    std::string input;
    std::cin >> input;
    return input;
}

std::vector<std::shared_ptr<Node>> ConsoleInterface::TakeInputFromUser()
{
    return std::vector<std::shared_ptr<Node>>();
}

void ConsoleInterface::PrintStack(std::stack<StackNumber> stack)
{
    std::cout << std::endl << "Stack:" << std::endl;
    std::cout << "top -> ";

    auto stackSize = stack.size();
    for (size_t i = 0; i < stackSize; i++)
    {
        std::cout << stack.top().variable << " ";
        stack.pop();
    }
}

void ConsoleInterface::PrintStackNumber(StackNumber variable)
{
    std::cout << variable.variable;
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
