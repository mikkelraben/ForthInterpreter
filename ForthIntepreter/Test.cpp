#include "Test.h"
#include "Operations.h"
#include "Tokenizer.h"

//TODO add tests for all arithmetic operators, boolean operators and basic stack manipulation

//TODO figure out how tasks work like the one you are reading now

class Test
{
public:
    std::string name;
    std::string_view input;
    std::vector<StackNumber> expectedStack;
    std::string_view expectedOutput;
    bool RunTest();
};

class TestInterface : public UserInterface
{

public:
    std::string TakeInputFromUser() override;
    void PrintStack(std::stack<StackNumber> stack) override;
    void PrintStackNumber(StackNumber variable) override;
    void PrintAscii(StackNumber ascii) override;
    void PrintString(std::string string) override;
    void PrintCarriageReturn() override;
    TestInterface() = default;
};

void AddTests(std::vector<Test>& tests);

void RunTests(std::shared_ptr<UserInterface> ui)
{




    ui->PrintString("Calculating fizzbuzz 1000000 times 10 times and averaging the speed");
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < 10; i++)
    {
        auto Testui = std::make_shared<TestInterface>();
        auto runtime = Runtime();
        runtime.userInterface = Testui;

        auto tokenizer = Tokenizer(runtime);
        std::shared_ptr<Function> function;

        std::string command = R"(: fizzbuzz 1000000 1 DO I 3 MOD 0 = I 5 MOD 0 = OR IF I 3 MOD 0 = IF ." Fizz" THEN I 5 MOD 0 = IF ." Buzz" THEN ELSE I . THEN CR LOOP ; fizzbuzz)";
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
        ui->PrintString("\nok");
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    //calculate delta
    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    ui->PrintString(std::format("The average time was {} milliseconds", delta / 10));

    ui->PrintString("Done");
    ui->TakeInputFromUser();

    //ui->PrintString("Commencing Tests\n");
    //int passed = 0;
    //int failed = 0;

    //std::vector<Test> tests;
    //AddTests(tests);

    //for (auto& test : tests)
    //{
    //    if (!test.RunTest())
    //    {
    //        ui->PrintString("The Test: \"" + test.name + "\" Failed\n");
    //        failed++;
    //    }
    //    else
    //    {
    //        passed++;
    //    }
    //}

    //ui->PrintCarriageReturn();
    //ui->PrintString(std::to_string(passed) + " Passed\t" + std::to_string(failed) + " Failed\n\n");
}

bool Test::RunTest()
{
    return false;
}

void AddTests(std::vector<Test>& tests)
{
#pragma region Algebra
#pragma endregion

#pragma region Boolean

#pragma endregion

#pragma region Stack Manipulation

#pragma endregion

}

std::string TestInterface::TakeInputFromUser()
{
    return std::string();
}

void TestInterface::PrintStack(std::stack<StackNumber> stack)
{
}

void TestInterface::PrintStackNumber(StackNumber variable)
{
}

void TestInterface::PrintAscii(StackNumber ascii)
{
}

void TestInterface::PrintString(std::string string)
{
}

void TestInterface::PrintCarriageReturn()
{
}
