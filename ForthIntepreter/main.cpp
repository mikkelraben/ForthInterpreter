#include "UserInterface.h"
#include "Runtime.h"
#include "Operations.h"
#include "Test.h"
#include "Tokenizer.h"

int main()
{
    auto ui = std::make_shared<ConsoleInterface>();


    RunTests(ui);

    auto runtime = Runtime();
    runtime.userInterface = ui;

    auto tokenizer = Tokenizer(runtime);
    std::shared_ptr<Function> function;

    //std::vector<std::string> commands = { "4 5 < IF .\" True\" 10 0 DO CR I . LOOP ELSE .\" False\" THEN 4 5 + 0 BEGIN DUP 5 < WHILE DUP 1 + REPEAT : foo 100 + ;" , "foo" };
    while (true)
    {
        std::string command = ui->TakeInputFromUser();


        try
        {
            function = std::make_shared<Function>(tokenizer.parseInput(command));
            runtime.addFunctionToCallStack(function);
            runtime.Evaluate();

        }
        catch (const ParseError& error)
        {
            ui->PrintString(" ");
            ui->PrintString(error.errorMessage);
        }
        ui->PrintString(" ok");

        ui->PrintCarriageReturn();

    }
}