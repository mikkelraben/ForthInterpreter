#pragma once
#include "Runtime.h"



struct Operations
{
	//Basic Arithmetic
	static std::vector<StackNumber> Add(std::vector<StackNumber>& nodes, Runtime& runtime)
	{
		assert(nodes.size() == 2);

		auto variable = StackNumber(nodes[1].variable + nodes[0].variable);
		return std::vector<StackNumber>({ variable });
	}
	static std::vector<StackNumber> Subtract(std::vector<StackNumber>& nodes, Runtime& runtime)
	{
		assert(nodes.size() == 2);

		auto variable = StackNumber(nodes[1].variable - nodes[0].variable);
		return std::vector<StackNumber>({ variable });
	}

	static std::vector<StackNumber> Multiply(std::vector<StackNumber>& nodes, Runtime& runtime)
	{
		assert(nodes.size() == 2);

		auto variable = StackNumber(nodes[1].variable * nodes[0].variable);
		return std::vector<StackNumber>({ variable });
	}
	static std::vector<StackNumber> Divide(std::vector<StackNumber>& nodes, Runtime& runtime)
	{
		assert(nodes.size() == 2);

		auto variable = StackNumber(nodes[1].variable / nodes[0].variable);
		return std::vector<StackNumber>({ variable });
	}

	//Boolean Logic

	//Stack Manipulation
	static std::vector<StackNumber> Duplicate(std::vector<StackNumber>& nodes, Runtime& runtime)
	{
		assert(nodes.size() == 1);
		return std::vector<StackNumber>({ nodes[0],nodes[0] });
	}
	static std::vector<StackNumber> Drop(std::vector<StackNumber>& nodes, Runtime& runtime)
	{
		assert(nodes.size() == 1);
		return std::vector<StackNumber>({});
	}
	static std::vector<StackNumber> Swap(std::vector<StackNumber>& nodes, Runtime& runtime)
	{
		assert(nodes.size() == 2);
		return std::vector<StackNumber>({ nodes[0],nodes[1] });
	}
	static std::vector<StackNumber> Over(std::vector<StackNumber>& nodes, Runtime& runtime)
	{
		assert(nodes.size() == 2);
		return std::vector<StackNumber>({ nodes[1],nodes[0],nodes[1] });
	}
	static std::vector<StackNumber> Rotate(std::vector<StackNumber>& nodes, Runtime& runtime)
	{
		assert(nodes.size() == 3);
		return std::vector<StackNumber>({ nodes[0],nodes[1],nodes[2] });
	}

	//I/O
	static std::vector<StackNumber> PrintStackNumber(std::vector<StackNumber>& nodes, Runtime& runtime);
	static std::vector<StackNumber> PrintAscii(std::vector<StackNumber>& nodes, Runtime& runtime);
	static std::vector<StackNumber> PrintCarriageReturn(std::vector<StackNumber>& nodes, Runtime& runtime);
	static std::vector<StackNumber> PrintString(StackString string, Runtime& runtime);
};

class Operators
{
public:
	//Basic Arithmetic
	const static inline Operation add = Operation(2, 1, Operations::Add,false);
	const static inline Operation subtract = Operation(2, 1, Operations::Subtract,false);
	const static inline Operation multiply = Operation(2, 1, Operations::Multiply,false);
	const static inline Operation divide = Operation(2, 1, Operations::Divide,false);	
	
	//Boolean Logic
	//static Operation equal = Operation(1,1,);
	//static Operation lessThan = Operation(1,1,);
	//static Operation largerThan = Operation(1,1,);
	//static Operation And = Operation(1,1,);
	//static Operation Or = Operation(1,1,);
	//static Operation Not = Operation(1,1,);

	//Stack Manipulation

	const static inline Operation duplicate = Operation(1, 2, Operations::Duplicate,false);
	const static inline Operation drop = Operation(1, 0, Operations::Drop,false);
	const static inline Operation swap = Operation(2, 2, Operations::Swap,false);
	const static inline Operation over = Operation(2, 3, Operations::Over,false);
	const static inline Operation rotate = Operation(3, 3, Operations::Rotate,false);

	const static inline Operation printVariable = Operation(1, 0, Operations::PrintStackNumber,false);
	const static inline Operation emitAscii = Operation(1, 0, Operations::PrintAscii,false);
	const static inline Operation printCarriageReturn = Operation(0, 0, Operations::PrintCarriageReturn,false);
	const static inline Operation printString = Operation(0, 0, Operations::PrintString, true);
};
