#pragma once
#include "Runtime.h"
#include "Exceptions.h"
#include "Test.h"

struct Operations
{
    //Basic Arithmetic
    static std::vector<StackNumber> Add(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);

        auto variable = StackNumber(nodes[1].variable + nodes[0].variable);
        return std::vector<StackNumber>({ variable });
    }
    static std::vector<StackNumber> Mod(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);

        auto variable = StackNumber(nodes[1].variable % nodes[0].variable);
        return std::vector<StackNumber>({ variable });
    }

    static std::vector<StackNumber> Subtract(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);

        auto variable = StackNumber(nodes[1].variable - nodes[0].variable);
        return std::vector<StackNumber>({ variable });
    }

    static std::vector<StackNumber> Multiply(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);

        auto variable = StackNumber(nodes[1].variable * nodes[0].variable);
        return std::vector<StackNumber>({ variable });
    }
    static std::vector<StackNumber> Divide(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);
        if (nodes[0].variable == 0)
        {
            throw RuntimeError("Can't divide by 0");
        }

        auto variable = StackNumber(nodes[1].variable / nodes[0].variable);
        return std::vector<StackNumber>({ variable });
    }

    //Boolean Logic
    static std::vector<StackNumber> Equal(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);

        auto variable = StackNumber(nodes[1].variable == nodes[0].variable ? -1 : 0);
        return std::vector<StackNumber>({ variable });
    }
    static std::vector<StackNumber> LessThan(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);

        auto variable = StackNumber(nodes[1].variable < nodes[0].variable ? -1 : 0);
        return std::vector<StackNumber>({ variable });
    }
    static std::vector<StackNumber> LargerThan(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);

        auto variable = StackNumber(nodes[1].variable > nodes[0].variable ? -1 : 0);
        return std::vector<StackNumber>({ variable });
    }
    static std::vector<StackNumber> And(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);

        auto variable = StackNumber(nodes[1].variable && nodes[0].variable ? -1 : 0);
        return std::vector<StackNumber>({ variable });
    }
    static std::vector<StackNumber> Or(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);

        auto variable = StackNumber(nodes[1].variable || nodes[0].variable ? -1 : 0);
        return std::vector<StackNumber>({ variable });
    }
    static std::vector<StackNumber> Not(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 1);

        auto variable = StackNumber(!nodes[0].variable ? -1 : 0);
        return std::vector<StackNumber>({ variable });
    }

    //Stack Manipulation
    static std::vector<StackNumber> Duplicate(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 1);
        return std::vector<StackNumber>({ nodes[0],nodes[0] });
    }
    static std::vector<StackNumber> Drop(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 1);
        return std::vector<StackNumber>({});
    }
    static std::vector<StackNumber> Swap(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);
        return std::vector<StackNumber>({ nodes[0],nodes[1] });
    }
    static std::vector<StackNumber> Over(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 2);
        return std::vector<StackNumber>({ nodes[1],nodes[0],nodes[1] });
    }
    static std::vector<StackNumber> Rotate(std::vector<StackNumber>& nodes, Runtime& runtime)
    {
        ASSERT_TRUE(nodes.size() == 3);
        return std::vector<StackNumber>({ nodes[0],nodes[1],nodes[2] });
    }

    //I/O
    static std::vector<StackNumber> PrintStackNumber(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> PrintAscii(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> PrintCarriageReturn(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> PrintString(std::vector<StackNumber>& nodes, Runtime& runtime);

    //Conditional Operations
    static std::vector<StackNumber> If(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> NOP(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> Else(std::vector<StackNumber>& nodes, Runtime& runtime);

    static std::vector<StackNumber> Do(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> qDo(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> Loop(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> I(std::vector<StackNumber>& nodes, Runtime& runtime);

    static std::vector<StackNumber> While(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> Repeat(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> Begin(std::vector<StackNumber>& nodes, Runtime& runtime);

    static std::vector<StackNumber> CallFunction(std::vector<StackNumber>& nodes, Runtime& runtime);
    static std::vector<StackNumber> BeginDefinition(std::vector<StackNumber>& nodes, Runtime& runtime);
};