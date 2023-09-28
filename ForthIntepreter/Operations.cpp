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

//Conditional Operations
std::vector<StackNumber> Operations::If(std::vector<StackNumber>& nodes, Runtime& runtime)
{
	size_t thenLocation = 0;
	for (size_t i = runtime.currentOrder; i < runtime.orders.size(); i++)
	{
		if (runtime.orders[i]->special == OperationType::Then)
		{
			thenLocation = i;
			break;
		}
	}

	size_t elseLocation = 0;
	for (size_t i = runtime.currentOrder; i < runtime.orders.size(); i++)
	{
		if (runtime.orders[i]->special == OperationType::Else)
		{
			elseLocation = i;
			break;
		}
	}

	if (thenLocation == 0)
	{
		throw std::exception("Could not find a Then for an if statement");
	}


	//if the if statement evaluates false then skip all orders until end
	if (!nodes[0].variable)
	{
		if (elseLocation < thenLocation && elseLocation != 0)
		{
			runtime.currentOrder = elseLocation;
		}
		else
		{
			runtime.currentOrder = thenLocation;
		}
	}

	return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::Then(std::vector<StackNumber>& nodes, Runtime& runtime)
{
	return std::vector<StackNumber>();
}

std::vector<StackNumber> Operations::Else(std::vector<StackNumber>& nodes, Runtime& runtime)
{
	//check if inside if statement
	//find the next then and goto
	size_t ifLocation = -1;
	for (size_t i = runtime.currentOrder; i != 0; i--)
	{
		if (runtime.orders[i]->special == OperationType::If)
		{
			ifLocation = i;
			break;
		}
		if (runtime.orders[i]->special == OperationType::Then)
		{
			ifLocation = -1;
			break;
		}
	}
	if (ifLocation == -1)
	{
		throw std::exception("Else statement outside an if statement");
	}

	size_t thenLocation = 0;
	for (size_t i = runtime.currentOrder; i < runtime.orders.size(); i++)
	{
		if (runtime.orders[i]->special == OperationType::Then)
		{
			thenLocation = i;
			break;
		}
	}

	if (thenLocation == 0)
	{
		throw std::exception("Could not find a Then for an if statement");
	}
	runtime.currentOrder = thenLocation;

	return std::vector<StackNumber>();
}

