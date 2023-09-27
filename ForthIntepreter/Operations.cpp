#include "Operations.h"
#include "UserInterface.h"


//I/O

inline std::vector<StackNumber> Operations::PrintStackNumber(std::vector<StackNumber>& nodes, Runtime& runtime)
{
	assert(nodes.size() == 1);
	assert(runtime.userInterface.get());
	runtime.userInterface->PrintStackNumber(nodes[0]);
	return std::vector<StackNumber>({});
}

inline std::vector<StackNumber> Operations::PrintAscii(std::vector<StackNumber>& nodes, Runtime& runtime)
{
	assert(nodes.size() == 1);
	assert(runtime.userInterface.get());
	runtime.userInterface->PrintAscii(nodes[0]);
	return std::vector<StackNumber>({});
}

inline std::vector<StackNumber> Operations::PrintCarriageReturn(std::vector<StackNumber>& nodes, Runtime& runtime)
{
	assert(nodes.size() == 0);
	assert(runtime.userInterface.get());
	runtime.userInterface->PrintCarriageReturn();
	return std::vector<StackNumber>({});
}

std::vector<StackNumber> Operations::PrintString(StackString string, Runtime& runtime)
{
	assert(runtime.userInterface.get());
	runtime.userInterface->PrintString(string.string);
	return std::vector<StackNumber>();
}
