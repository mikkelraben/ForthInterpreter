#include "UserInterface.h"
#include "Runtime.h"
#include "Operations.h"
#include "Test.h"

int main()
{    
    auto ui = std::make_shared<ConsoleInterface>();

    RunTests(ui);
    
    auto runtime = Runtime();
    runtime.userInterface = ui;

    runtime.addMaintoCallStack();
    runtime.AddOrder(std::make_shared<StackNumber>(4));
    runtime.AddOrder(std::make_shared<StackNumber>(5));
    runtime.AddOrder(std::make_shared<Operator>(Operators::lessThan));
    runtime.AddOrder(std::make_shared<Operator>(Operators::If));
    runtime.AddOrder(std::make_shared<Operator>(Operators::printString));
    runtime.AddOrder(std::make_shared<StackString>("True"));

    runtime.AddOrder(std::make_shared<StackNumber>(10));
    runtime.AddOrder(std::make_shared<StackNumber>(0));
    runtime.AddOrder(std::make_shared<Operator>(Operators::Do));
    runtime.AddOrder(std::make_shared<Operator>(Operators::printCarriageReturn));
    runtime.AddOrder(std::make_shared<Operator>(Operators::I));
    runtime.AddOrder(std::make_shared<Operator>(Operators::printVariable));

    runtime.AddOrder(std::make_shared<Operator>(Operators::Loop));

    runtime.AddOrder(std::make_shared<Operator>(Operators::Else));

    runtime.AddOrder(std::make_shared<Operator>(Operators::printString));
    runtime.AddOrder(std::make_shared<StackString>("False"));
    runtime.AddOrder(std::make_shared<Operator>(Operators::Then));


    runtime.AddOrder(std::make_shared<Operator>(Operators::CallFunction));
    runtime.AddOrder(std::make_shared<StackNumber>(4));
    runtime.AddOrder(std::make_shared<StackNumber>(5));
    runtime.AddOrder(std::make_shared<Operator>(Operators::add));
    runtime.AddOrder(std::make_shared<StackNumber>(0));
    runtime.AddOrder(std::make_shared<Operator>(Operators::Begin));
    runtime.AddOrder(std::make_shared<Operator>(Operators::duplicate));
    runtime.AddOrder(std::make_shared<StackNumber>(5));
    runtime.AddOrder(std::make_shared<Operator>(Operators::lessThan));
    runtime.AddOrder(std::make_shared<Operator>(Operators::While));
    runtime.AddOrder(std::make_shared<Operator>(Operators::duplicate));
    runtime.AddOrder(std::make_shared<StackNumber>(1));
    runtime.AddOrder(std::make_shared<Operator>(Operators::add));
    runtime.AddOrder(std::make_shared<Operator>(Operators::Repeat));



    
    runtime.Evaluate();

    

    ui->PrintStack(runtime.stack);
}