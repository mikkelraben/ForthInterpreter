#include "Operations.h"
#include "UserInterface.h"


//I/O

std::vector<StackNumber> Operations::PrintStackNumber(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 1);
    ASSERT_TRUE(runtime.userInterface.get() != nullptr);
    runtime.userInterface->PrintStackNumber(nodes[0]);
    return std::vector<StackNumber>({});
}

std::vector<StackNumber> Operations::PrintAscii(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 1);
    ASSERT_TRUE(runtime.userInterface.get() != nullptr)
        runtime.userInterface->PrintAscii(nodes[0]);
    return std::vector<StackNumber>({});
}

std::vector<StackNumber> Operations::PrintCarriageReturn(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 0);
    ASSERT_TRUE(runtime.userInterface.get() != nullptr);
    runtime.userInterface->PrintCarriageReturn();
    return std::vector<StackNumber>({});
}

std::vector<StackNumber> Operations::PrintString(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 0);
    ASSERT_TRUE(runtime.userInterface.get() != nullptr);
    if (auto info = runtime.orders()[runtime.currentOrder()]->info)
    {
        auto stringLocation = info->stringLocation;
        ASSERT_TRUE(runtime.orders()[stringLocation]->special == OperationType::string);
        auto string = std::dynamic_pointer_cast<StackString>(runtime.orders()[stringLocation]);
        runtime.userInterface->PrintString(string->string);
        runtime.currentOrder()++;
    }
    else
    {
        ASSERT_TRUE(false);
    }
    return std::vector<StackNumber>();
}

//Conditional Operations
std::vector<StackNumber> Operations::If(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 1);
    size_t thenLocation = runtime.orders()[runtime.currentOrder()]->info->endLocation;


    size_t elseLocation = runtime.orders()[runtime.currentOrder()]->info->elseLocation;

    //if the if statement evaluates false then skip all orders until end
    if (!nodes[0].variable)
    {
        if (elseLocation != -1)
        {
            runtime.currentOrder() = elseLocation;
        }
        else
        {
            runtime.currentOrder() = thenLocation;
        }
    }

    return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::NOP(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 0);
    return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::Else(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 0);

    runtime.currentOrder() = runtime.orders()[runtime.currentOrder()]->info->endLocation;

    return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::Do(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 2);
    auto doOrder = runtime.orders()[runtime.currentOrder()];
    auto loopOrder = runtime.orders()[doOrder->info->endLocation];
    loopOrder->info->loopStartingValue = nodes[0].variable;
    loopOrder->info->loopEndValue = nodes[1].variable;

    //if false goto end
    if (nodes[0].variable >= nodes[1].variable)
    {
        runtime.currentOrder() = doOrder->info->endLocation;
    }

    //check for impossible loop?
    if (nodes[0].variable < nodes[1].variable)
    {
        //TODO figure out how a wrong loop should be handled
    }

    return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::qDo(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 2);
    auto doOrder = runtime.orders()[runtime.currentOrder()];
    auto loopOrder = runtime.orders()[doOrder->info->endLocation];
    //this do loop executes one more time
    loopOrder->info->loopStartingValue = nodes[0].variable - 1;
    loopOrder->info->loopEndValue = nodes[1].variable;

    //if false goto end
    if (nodes[0].variable >= nodes[1].variable)
    {
        runtime.currentOrder() = doOrder->info->endLocation;
    }

    //check for impossible loop?
    if (nodes[0].variable < nodes[1].variable)
    {

    }


    //check if condition is true if it is false skip to after loop and
    return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::Loop(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    //check if condition is true if it is true goto beginning of the loop and
    auto& loopOrder = runtime.orders()[runtime.currentOrder()];
    loopOrder->info->loopStartingValue++;
    //if true goto start
    if (loopOrder->info->loopStartingValue < loopOrder->info->loopEndValue)
    {
        runtime.currentOrder() = loopOrder->info->startLocation;

    }


    //goto do statement
    return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::I(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    //return the current iteration in nearest do loop
    auto loopPosition = runtime.orders()[runtime.currentOrder()]->info->startLocation;
    auto loopOrder = runtime.orders()[loopPosition];
    auto thenOrder = runtime.orders()[loopOrder->info->endLocation];

    return std::vector<StackNumber>({ StackNumber(thenOrder->info->loopStartingValue) });
}

std::vector<StackNumber> Operations::While(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 1);
    if (nodes[0].variable == 0)
    {
        runtime.currentOrder() = runtime.orders()[runtime.currentOrder()]->info->endLocation;
    }
    return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::Repeat(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 0);

    runtime.currentOrder() = runtime.orders()[runtime.currentOrder()]->info->startLocation;

    return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::Begin(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::CallFunction(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    auto info = runtime.orders()[runtime.currentOrder()]->info;
    auto stringLocation = info->stringLocation;
    ASSERT_TRUE(runtime.orders()[stringLocation]->special == OperationType::string);
    auto string = std::dynamic_pointer_cast<StackString>(runtime.orders()[stringLocation]);



    runtime.callStack.push(runtime.storage.functions.at(string->string));
    runtime.Evaluate();

    runtime.currentOrder() = stringLocation;

    return std::vector<StackNumber>();
}


std::vector<StackNumber> Operations::BeginDefinition(std::vector<StackNumber>& nodes, Runtime& runtime)
{
    ASSERT_TRUE(nodes.size() == 0);

    runtime.currentOrder() = runtime.orders()[runtime.currentOrder()]->info->endLocation;

    return std::vector<StackNumber>();
}
