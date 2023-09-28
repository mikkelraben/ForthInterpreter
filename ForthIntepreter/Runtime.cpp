#include "Runtime.h"
#include "Operations.h"




void Runtime::AddOrder(std::shared_ptr<Node> node)
{
	orders.emplace_back(node);
}

void Runtime::Evaluate()
{
	for (currentOrder = 0; currentOrder < orders.size(); currentOrder++)
	{
		auto node = orders[currentOrder];
		if (auto op = std::dynamic_pointer_cast<Operator>(node))
		{
			if (stack.size() < op->op.numberOfInput)
			{
				throw std::exception("Stack Underflow");
			}
			std::vector<StackNumber> variables;
			std::vector<StackNumber> returnValues;
			if (op->op.special != OperationType::printString)
			{
				for (size_t j = 0; j < op->op.numberOfInput; j++)
				{
					variables.push_back(stack.top());

					stack.pop();
				}
				returnValues = op->op.function(variables, *this);
			}
			else
			{
				//check the next order exists which includes a string
				assert(orders.size() >= currentOrder + 2);
				if (auto string = std::dynamic_pointer_cast<StackString>(orders[currentOrder+1]))
				{
					returnValues = op->op.stringFunction(*string, *this);
					//skip string order
					currentOrder++;
				}
				else
				{
					throw std::exception("Couldn't find a string");
				}
			}

			for (auto const& returnValue : returnValues)
			{
				stack.push(returnValue);
			}
			continue;
		}
		if (auto var = std::dynamic_pointer_cast<StackNumber>(node))
		{
			stack.push(*var.get());
			continue;
		}
		if (auto var = std::dynamic_pointer_cast<StackString>(node))
		{
			assert(false);
		}
		
	}
	orders.clear();
}
