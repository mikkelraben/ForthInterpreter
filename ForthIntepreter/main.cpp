#include "UserInterface.h"
#include "Runtime.h"
#include "Operations.h"

int main()
{    
    auto ui = std::make_shared<ConsoleInterface>();
    
    auto runtime = Runtime();
    runtime.userInterface = ui;

    runtime.AddOrder(std::make_shared<StackNumber>(78));
    runtime.AddOrder(std::make_shared<StackNumber>(9));
    runtime.AddOrder(std::make_shared<Operator>(Operators::add));
    runtime.AddOrder(std::make_shared<Operator>(Operators::emitAscii));
    runtime.AddOrder(std::make_shared<StackNumber>(111));
    runtime.AddOrder(std::make_shared<Operator>(Operators::emitAscii));
    runtime.Evaluate();
    runtime.AddOrder(std::make_shared<StackNumber>(119));
    runtime.AddOrder(std::make_shared<Operator>(Operators::emitAscii));
    runtime.AddOrder(std::make_shared<StackNumber>(33));
    runtime.AddOrder(std::make_shared<Operator>(Operators::emitAscii));

    runtime.AddOrder(std::make_shared<Operator>(Operators::printString));
    runtime.AddOrder(std::make_shared<StackString>("Some String"));

    runtime.AddOrder(std::make_shared<StackNumber>(33));
    runtime.AddOrder(std::make_shared<StackNumber>(33));
    runtime.AddOrder(std::make_shared<Operator>(Operators::add));

    //runtime.AddOrder(std::make_shared<Operator>(Operators::printCarriageReturn));
    runtime.Evaluate();

    ui->PrintStack(runtime.stack);
}