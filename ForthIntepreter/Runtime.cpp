#include "Runtime.h"
#include "Operations.h"
#include "UserInterface.h"
#include "Exceptions.h"
#include <format>
#include <ranges>



void Runtime::AddOrder(std::shared_ptr<Node> node)
{
    //cannot add order to an empty function
    ASSERT_TRUE(currentFunction() != nullptr);
    currentFunction()->orders.emplace_back(node);
}

void Runtime::Evaluate()
{
    std::stack<StackNumber> oldStack;
    try
    {
        //make a copy of the stack incase a Runtime error happens and the program needs to revert
        oldStack = stack;
        ValidateOrders();
        addDefinitions();
        RunOrders();
    }
    catch (ForthExceptions& e)
    {

        if (userInterface)
        {
            userInterface->PrintString(e.errorType + ": ");
            userInterface->PrintString(e.errorMessage);
            if (dynamic_cast<RuntimeError*>(&e))
            {
                userInterface->PrintCarriageReturn();
                userInterface->PrintString("Stack at failure: ");
                userInterface->PrintStack(stack);
                userInterface->PrintCarriageReturn();
            }
        }
        stack = oldStack;
    }
}

void Runtime::RunOrders()
{
    for (currentFunction()->currentOrder = 0; currentFunction()->currentOrder < currentFunction()->orders.size(); currentFunction()->currentOrder++)
    {
        auto node = currentFunction()->orders[currentFunction()->currentOrder];
        if (auto op = std::dynamic_pointer_cast<Operator>(node))
        {
            if (stack.size() < op->op.numberOfInput)
            {
                throw RuntimeError("Stack Underflow");
            }
            std::vector<StackNumber> variables;
            std::vector<StackNumber> returnValues;

            for (size_t j = 0; j < op->op.numberOfInput; j++)
            {
                variables.push_back(stack.top());

                stack.pop();
            }
            returnValues = op->op.function(variables, *this);

            for (auto const& returnValue : returnValues)
            {
                stack.push(returnValue);
            }
            continue;
        }
        if (auto var = std::dynamic_pointer_cast<StackNumber>(node))
        {
            stack.push(*var.get());
            continue;
        }
        if (auto var = std::dynamic_pointer_cast<StackString>(node))
        {
            assert(false);
        }
        currentFunction()->currentOrder++;
    }
    popFunctionFromCallStack();
}

std::shared_ptr<Function> Runtime::currentFunction()
{
    return callStack.top();
}

void Runtime::addMaintoCallStack()
{
    std::vector<std::shared_ptr<Node>> orders;
    callStack.push(std::make_shared<Function>("main", orders));
}

void Runtime::addFunctionToCallStack(std::shared_ptr<Function> function)
{
    function->currentOrder = 0;
    callStack.push(function);
}

void Runtime::popFunctionFromCallStack()
{
    callStack.pop();
}

void Runtime::addDefinitions()
{
    auto is_Function = [](std::shared_ptr<Node> node) { return node->special == OperationType::FunctionBegin; };

    for (auto& node : std::views::filter(orders(), is_Function))
    {

        auto startLocation = node->info->startLocation;
        auto endLocation = node->info->endLocation;

        auto functionNameNode = orders()[startLocation + 1];
        auto functionNameString = std::dynamic_pointer_cast<StackString>(functionNameNode);

        if (storage.functions.contains(functionNameString->string))
        {
            throw SyntaxError("Word already used for another function or variable");
        }
        //find the orders
        std::vector<std::shared_ptr<Node>> functionOrders = { orders().begin() + startLocation + 2,orders().begin() + endLocation };

        storage.functions[functionNameString->string] = std::make_shared<Function>(functionNameString->string, functionOrders);
        //orders().erase(orders().begin() + startLocation, orders().begin() + endLocation + 1);
    }
}

size_t& Runtime::currentOrder()
{
    return currentFunction()->currentOrder;
}

std::vector<std::shared_ptr<Node>>& Runtime::orders()
{
    return currentFunction()->orders;
}

void addInfo(std::shared_ptr<Node> node)
{
    if (!node->info)
    {
        node->info = std::make_shared<ExtraInfo>();
    }
}

enum class LoopTypes
{
    If,
    Do,
    While,
    Definition,
};

struct LoopInfo
{
    LoopTypes type;
    size_t beginning;
};

std::string LoopErrorMessage(LoopInfo loopType)
{
    std::string errorMessage;
    switch (loopType.type)
    {
        using enum LoopTypes;
    case If:
        errorMessage = "Expected Then for if statement at position: ";
        break;
    case Do:
        errorMessage = "Expected Loop for do loop at position: ";
        break;
    case While:
        errorMessage = "Expected Repeat for while loop at postion: ";
        break;
    case Definition:
        errorMessage = "Expected ; for function at postion: ";
        break;
    default:
        break;
    }

    return errorMessage + std::to_string(loopType.beginning);
}

//checks if all orders are valid
void Runtime::ValidateOrders()
{
    //check strings
    for (size_t i = 0; i < orders().size(); i++)
    {
        if (orders()[i]->special == OperationType::printString)
        {
            if (orders().size() < i)
            {
                throw SyntaxError("Could not find string to print");
            }
            if (orders()[i + 1]->special == OperationType::string)
            {
                addInfo(orders()[i]);
                orders()[i]->info->stringLocation = i + 1;
            }
            else
            {
                throw SyntaxError("Could not find string to print");
            }
        }
        if (orders()[i]->special == OperationType::CallFunction)
        {
            if (orders().size() < i)
            {
                throw SyntaxError("Could not find function name");
            }
            if (orders()[i + 1]->special == OperationType::string)
            {
                addInfo(orders()[i]);
                orders()[i]->info->stringLocation = i + 1;
            }
            else
            {
                throw SyntaxError("Could not find function name");
            }
        }

    }


    //check loops, if statements and loops borders 
    std::vector<LoopInfo> loopStack;
    for (size_t i = 0; i < orders().size(); i++)
    {
        if (orders()[i]->validated)
        {
            continue;
        }

        //If statement
        if (orders()[i]->special == OperationType::If)
        {
            loopStack.emplace_back(LoopTypes::If, i);
            addInfo(orders()[i]);
        }

        if (orders()[i]->special == OperationType::Else)
        {
            bool foundIf = false;
            for (int j = loopStack.size() - 1; j >= 0; j--)
            {
                if (loopStack[j].type == LoopTypes::If)
                {
                    size_t ifLocation = loopStack[j].beginning;
                    if (orders()[ifLocation]->info->elseLocation != -1)
                    {
                        throw SyntaxError(std::format("Else statement at position: {} is inside an if statement that already has an else statement", i));
                    }
                    orders()[ifLocation]->info->elseLocation = i;
                    addInfo(orders()[i]);
                    orders()[i]->info->endLocation = orders()[ifLocation]->info->endLocation;
                    foundIf = true;
                    break;
                }
            }
            if (!foundIf)
            {
                throw SyntaxError("Expected If");
            }
        }

        if (orders()[i]->special == OperationType::Then)
        {
            if (loopStack.empty())
            {
                throw SyntaxError("Expected If");
            }
            if (loopStack.back().type == LoopTypes::If)
            {
                auto startLoop = loopStack.back().beginning;
                orders()[startLoop]->info->endLocation = i;
                orders()[startLoop]->validated = true;
                orders()[i]->validated = true;
                loopStack.pop_back();
            }
            else
            {
                throw SyntaxError(LoopErrorMessage(loopStack.back()));
            }
        }

        //Do loop
        if (orders()[i]->special == OperationType::Do)
        {
            loopStack.emplace_back(LoopTypes::Do, i);
            addInfo(orders()[i]);
        }
        if (orders()[i]->special == OperationType::Loop)
        {
            if (loopStack.empty())
            {
                throw SyntaxError("Expected Do");
            }
            if (loopStack.back().type == LoopTypes::Do)
            {
                auto startLoop = loopStack.back().beginning;
                orders()[startLoop]->info->endLocation = i;
                orders()[startLoop]->validated = true;
                orders()[i]->validated = true;
                addInfo(orders()[i]);
                orders()[i]->info->startLocation = startLoop;
                loopStack.pop_back();
            }
            else
            {
                throw SyntaxError(LoopErrorMessage(loopStack.back()));
            }
        }

        if (orders()[i]->special == OperationType::I)
        {

            addInfo(orders()[i]);
            if (loopStack.back().type == LoopTypes::Do)
            {
                orders()[i]->info->startLocation = loopStack.back().beginning;
            }
            else
            {
                throw SyntaxError("\"I\" must be inside Do loop");
            }

        }

        //begin-while-repeat loop
        if (orders()[i]->special == OperationType::Begin)
        {
            loopStack.emplace_back(LoopTypes::While, i);
            addInfo(orders()[i]);
        }
        // #TODO no validation for while loop right now
        if (orders()[i]->special == OperationType::While)
        {
            if (loopStack.back().type == LoopTypes::While)
            {
                auto startLoop = loopStack.back().beginning;
                orders()[startLoop]->info->whileLocation = i;
            }
            else
            {
                throw SyntaxError("Expected Begin");
            }

        }

        if (orders()[i]->special == OperationType::Repeat)
        {
            if (loopStack.empty())
            {
                throw SyntaxError("Expected Begin");
            }
            if (loopStack.back().type == LoopTypes::While)
            {

                auto startLoop = loopStack.back().beginning;
                auto whilePosition = orders()[startLoop]->info->whileLocation;
                if (whilePosition == -1)
                {
                    throw SyntaxError("No While Statement inside Begin-Repeat");
                }
                addInfo(orders()[whilePosition]);
                orders()[whilePosition]->info->endLocation = i;
                orders()[startLoop]->info->endLocation = i;
                orders()[startLoop]->validated = true;
                orders()[i]->validated = true;
                addInfo(orders()[i]);
                orders()[i]->info->startLocation = startLoop;
                loopStack.pop_back();
            }
            else
            {
                throw SyntaxError(LoopErrorMessage(loopStack.back()));
            }
        }

        //Functions
        if (orders()[i]->special == OperationType::FunctionBegin)
        {
            loopStack.emplace_back(LoopTypes::Definition, i);
            addInfo(orders()[i]);
        }
        if (orders()[i]->special == OperationType::FunctionEnd)
        {
            if (loopStack.empty())
            {
                throw SyntaxError("Expected Function");
            }
            if (loopStack.back().type == LoopTypes::Definition)
            {
                auto startDefinition = loopStack.back().beginning;
                orders()[startDefinition]->info->endLocation = i;
                orders()[startDefinition]->info->startLocation = startDefinition;
                loopStack.pop_back();

                for (size_t j = startDefinition + 1; j < i; j++)
                {
                    orders()[j]->validated = false;
                }
            }
            else
            {
                throw SyntaxError(LoopErrorMessage(loopStack.back()));
            }
        }

    }
    if (!loopStack.empty())
    {
        throw SyntaxError(LoopErrorMessage(loopStack.back()));
    }

    //size_t currentThen = -1;
    ////check and assign else statements
    //for (int i = 0; i < orders().size(); i++)
    //{
    //    if (orders()[i]->special == OperationType::Else)
    //    {
    //        size_t ifLocation = -1;
    //        for (size_t j = i; j != 0; j--)
    //        {
    //            if (orders()[j]->special == OperationType::If)
    //            {
    //                ifLocation = j;
    //            }
    //            if (orders()[j]->special == OperationType::Then)
    //            {
    //                ifLocation = -1;
    //            }
    //        }
    //        if (ifLocation == -1)
    //        {
    //            throw SyntaxError(std::format("Else statement at position: {} outside an if statement", i));
    //        }
    //        if (orders()[ifLocation]->info->elseLocation != -1)
    //        {
    //            throw SyntaxError(std::format("Else statement at position: {} is inside an if statement that already has an else statement", i));
    //        }
    //        orders()[ifLocation]->info->elseLocation = i;

    //        addInfo(orders()[i]);
    //        orders()[i]->info->endLocation = orders()[ifLocation]->info->endLocation;
    //    }
    //}
}
