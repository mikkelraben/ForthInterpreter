#include "UserInterface.h"
#include "Runtime.h"
#include "Operations.h"

int main()
{    
    auto ui = std::make_shared<ConsoleInterface>();
    
    auto runtime = Runtime();
    runtime.userInterface = ui;

    runtime.AddOrder(std::make_shared<StackNumber>(4));
    runtime.AddOrder(std::make_shared<StackNumber>(5));
    runtime.Evaluate();
    ui->PrintStack(runtime.stack);
    runtime.AddOrder(std::make_shared<Operator>(Operators::lessThan));
    runtime.AddOrder(std::make_shared<Operator>(Operators::duplicate));
    runtime.AddOrder(std::make_shared<Operator>(Operators::If));
    runtime.AddOrder(std::make_shared<Operator>(Operators::printString));
    runtime.AddOrder(std::make_shared<StackString>("True"));
    runtime.AddOrder(std::make_shared<Operator>(Operators::Then));

    runtime.AddOrder(std::make_shared<Operator>(Operators::Not));

    runtime.AddOrder(std::make_shared<Operator>(Operators::If));
    runtime.AddOrder(std::make_shared<Operator>(Operators::printString));
    runtime.AddOrder(std::make_shared<StackString>("False"));
    runtime.AddOrder(std::make_shared<Operator>(Operators::Then));

    
    runtime.Evaluate();
    //runtime.AddOrder(std::make_shared<Operator>(Operators::printCarriageReturn));

    ui->PrintStack(runtime.stack);
}