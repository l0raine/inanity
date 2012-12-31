#ifndef ___INANITY_GRAPHICS_SHADERS_OPERATION_NODE_HPP___
#define ___INANITY_GRAPHICS_SHADERS_OPERATION_NODE_HPP___

#include "Node.hpp"

BEGIN_INANITY_SHADERS

/// Класс выражения-операции.
class OperationNode : public Node
{
public:
	/// Максимальное количество аргументов.
	static const int maxArgumentsCount = 4;

	/// Операция.
	enum Operation
	{
		operationAssign,
		operationNegate,
		operationAdd,
		operationSubtract,
		operationMultiply,
		operationDivide,
		operationFloat1111to4,
		operationFloat31to4,
		operationDot,
		operationCross,
		operationMul,
		operationNormalize
	};

private:
	/// Операция.
	Operation operation;
	/// Аргументы.
	ptr<Node> a, b, c, d;
	/// Количество аргументов.
	int argumentsCount;

public:
	/// Конструкторы.
	OperationNode(Operation operation);
	OperationNode(Operation operation, ptr<Node> a);
	OperationNode(Operation operation, ptr<Node> a, ptr<Node> b);
	OperationNode(Operation operation, ptr<Node> a, ptr<Node> b, ptr<Node> c);
	OperationNode(Operation operation, ptr<Node> a, ptr<Node> b, ptr<Node> c, ptr<Node> d);

	Type GetType() const;

	Operation GetOperation() const;
	int GetArgumentsCount() const;

	ptr<Node> GetA() const;
	ptr<Node> GetB() const;
	ptr<Node> GetC() const;
	ptr<Node> GetD() const;

	ptr<Node> GetArgument(int number) const;
};

END_INANITY_SHADERS

#endif