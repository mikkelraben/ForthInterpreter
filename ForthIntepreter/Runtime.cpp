#include "Runtime.h"
#include "Operations.h"




void Runtime::AddOrder(std::shared_ptr<Node> node)
{
	orders.emplace_back(node);
}

void Runtime::Evaluate()
{
	for (size_t i = 0; i < orders.size(); i++)
	{
		auto node = orders[i];
		if (auto op = std::dynamic_pointer_cast<Operator>(node))
		{
			if (stack.size() < op->op.numberOfInput)
			{
				throw std::exception("Stack Underflow");
			}
			std::vector<StackNumber> variables;
			std::vector<StackNumber> returnValues;
			if (!op->op.string)
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
				assert(orders.size() >= i + 2);
				if (auto string = std::dynamic_pointer_cast<StackString>(orders[i+1]))
				{
					returnValues = op->op.stringFunction(*string, *this);
					//skip string order
					i++;
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
			break;
		}
		if (auto var = std::dynamic_pointer_cast<StackNumber>(node))
		{
			stack.push(*var.get());
			break;
		}
		if (auto var = std::dynamic_pointer_cast<StackString>(node))
		{
			assert(false);
		}
		
	}
	orders.clear();
}
