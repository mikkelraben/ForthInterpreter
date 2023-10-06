#include "Test.h"
#include "Operations.h"

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

void AddTests(std::vector<Test>& tests);

void RunTests(std::shared_ptr<UserInterface> ui)
{
    ui->PrintString("Commencing Tests\n");
    int passed = 0;
    int failed = 0;

    std::vector<Test> tests;
    AddTests(tests);

    for (auto& test : tests)
    {
        if (!test.RunTest())
        {
            ui->PrintString("The Test: \"" + test.name + "\" Failed\n");
            failed++;
        }
        else
        {
            passed++;
        }
    }

    ui->PrintCarriageReturn();
    ui->PrintString(std::to_string(passed) + " Passed\t" + std::to_string(failed) + " Failed\n\n");
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


