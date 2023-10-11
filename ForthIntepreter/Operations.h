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
	static std::vector<StackNumber> Then(std::vector<StackNumber>& nodes, Runtime& runtime);
	static std::vector<StackNumber> Else(std::vector<StackNumber>& nodes, Runtime& runtime);

	static std::vector<StackNumber> Do(std::vector<StackNumber>& nodes, Runtime& runtime);
	static std::vector<StackNumber> qDo(std::vector<StackNumber>& nodes, Runtime& runtime);
	static std::vector<StackNumber> Loop(std::vector<StackNumber>& nodes, Runtime& runtime);
	static std::vector<StackNumber> I(std::vector<StackNumber>& nodes, Runtime& runtime);

	static std::vector<StackNumber> While(std::vector<StackNumber>& nodes, Runtime& runtime);
	static std::vector<StackNumber> Repeat(std::vector<StackNumber>& nodes, Runtime& runtime);
	static std::vector<StackNumber> Begin(std::vector<StackNumber>& nodes, Runtime& runtime);

	static std::vector<StackNumber> CallFunction(std::vector<StackNumber>& nodes, Runtime& runtime);
};

class Operators
{
public:
	//Basic Arithmetic
	const static inline Operation add = Operation(2, 1, Operations::Add,OperationType::normal);
	const static inline Operation subtract = Operation(2, 1, Operations::Subtract,OperationType::normal);
	const static inline Operation multiply = Operation(2, 1, Operations::Multiply,OperationType::normal);
	const static inline Operation divide = Operation(2, 1, Operations::Divide,OperationType::normal);
	
	//Boolean Logic
	const static inline Operation equal = Operation(2,1, Operations::Equal,OperationType::normal);
	const static inline Operation lessThan = Operation(2,1, Operations::LessThan,OperationType::normal);
	const static inline Operation largerThan = Operation(2,1, Operations::LargerThan,OperationType::normal);
	const static inline Operation And = Operation(2,1, Operations::And,OperationType::normal);
	const static inline Operation Or = Operation(2,1, Operations::Or,OperationType::normal);
	const static inline Operation Not = Operation(1,1, Operations::Not,OperationType::normal);

	//Stack Manipulation

	const static inline Operation duplicate = Operation(1, 2, Operations::Duplicate,OperationType::normal);
	const static inline Operation drop = Operation(1, 0, Operations::Drop,OperationType::normal);
	const static inline Operation swap = Operation(2, 2, Operations::Swap,OperationType::normal);
	const static inline Operation over = Operation(2, 3, Operations::Over,OperationType::normal);
	const static inline Operation rotate = Operation(3, 3, Operations::Rotate,OperationType::normal);

	const static inline Operation printVariable = Operation(1, 0, Operations::PrintStackNumber,OperationType::normal);
	const static inline Operation emitAscii = Operation(1, 0, Operations::PrintAscii,OperationType::normal);
	const static inline Operation printCarriageReturn = Operation(0, 0, Operations::PrintCarriageReturn,OperationType::normal);
	const static inline Operation printString = Operation(0, 0, Operations::PrintString, OperationType::printString);

	//Conditional Operations
	const static inline Operation If = Operation(1, 0, Operations::If, OperationType::If);
	const static inline Operation Then = Operation(0, 0, Operations::Then, OperationType::Then);
	const static inline Operation Else = Operation(0, 0, Operations::Else, OperationType::Else);


	const static inline Operation Do = Operation(2, 0, Operations::Do, OperationType::Do);
	//?DO
	const static inline Operation qDo = Operation(2, 0, Operations::qDo, OperationType::Do);
	const static inline Operation Loop = Operation(0, 0, Operations::Loop, OperationType::Loop);
	const static inline Operation I = Operation(0, 1, Operations::I, OperationType::I);

	const static inline Operation Begin = Operation(0, 0, Operations::Begin, OperationType::Begin);
	const static inline Operation While = Operation(1, 0, Operations::While, OperationType::While);
	const static inline Operation Repeat = Operation(0, 0, Operations::Repeat, OperationType::Repeat);

	const static inline Operation CallFunction = Operation(0, 0, Operations::CallFunction, OperationType::Function);
};
