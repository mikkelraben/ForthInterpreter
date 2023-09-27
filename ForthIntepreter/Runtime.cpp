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
			for (size_t j = 0; j < op->op.numberOfInput; j++)
			{
				variables.push_back(stack.top());

				stack.pop();
			}
			auto returnValues = op->op.function(variables,*this);

			for (auto const& returnValue : returnValues)
			{
				stack.push(returnValue);
			}
		}
		if (auto var = std::dynamic_pointer_cast<StackNumber>(node))
		{
			stack.push(*var.get());
		}
		
	}
	orders.clear();
}
