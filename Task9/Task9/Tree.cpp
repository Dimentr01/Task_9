#include <iostream>
#include <iomanip>
#include "Helpers.h"
#include "Tree.h"
#include "Stack.hpp"

// Функция выводит дерево на печать через inorder обход
void ShowTreeInorder(Tree* top, int n)
{
	if (top == NULL)
		return;
	ShowTreeInorder(top->Left, n + 1);
	std::cout << std::setw(n * 3) << top->value << std::endl;
	ShowTreeInorder(top->Right, n + 1);
}

Tree* CreateSymbolElement(const char& symbol)
{
	auto elem = new Tree;
	elem->value = symbol;
	elem->Left = nullptr;
	elem->Right = nullptr;
	return elem;
}

Tree* CreateNegationElement(const char& symbol, Tree* left)
{
	auto elem = new Tree;
	elem->value = symbol;
	elem->Left = left;
	elem->Right = nullptr;
	return elem;
}

Tree* CreateSumOrMultiplyElement(const char& symbol, Tree* left, Tree* right)
{
	auto elem = new Tree;
	elem->value = symbol;
	elem->Left = left;
	elem->Right = right;
	return elem;
}

// Функция строит дерево по инфиксной записи и возвращает указатель на вершину дерева
Tree* CreateTreeViaInfix(const std::string& expr)
{
	if (expr.empty())
		return nullptr;

	// for result tree
	auto stackTree = new Stack<Tree*>;
	stackTree = nullptr;
	// for operations
	auto stackChar = new Stack<char>;
	stackChar = nullptr;

	for (auto symbol : expr)
	{
		// если символ
		if (CharBelongsToString(symbol, AllOperands))
		{
			auto elem = CreateSymbolElement(symbol);
			StackPush(&stackTree, elem);
		}
		else if (IsOperator(symbol))
		{
			if (symbol == '!' || symbol == '(')
			{
				StackPush(&stackChar, symbol);
			}
			else if (symbol == ')')
			{
				while (true)
				{
					auto tempElem = StackTop(stackChar);
					StackPop(&stackChar);
					if (tempElem == '(')
						break;

					if (tempElem == '!')
					{
						auto left = StackTop(stackTree);
						StackPop(&stackTree);
						auto elem = CreateNegationElement(tempElem, left);
						StackPush(&stackTree, elem);
					}
					else
					{
						auto right = StackTop(stackTree);
						StackPop(&stackTree);
						auto left = StackTop(stackTree);
						StackPop(&stackTree);
						auto elem = CreateSumOrMultiplyElement(tempElem, left, right);
						StackPush(&stackTree, elem);
					}
				}
			}
			else if (symbol == '+' || symbol == '*')
			{
				while (true)
				{
					if (StackIsEmpty(stackChar))
						break;
					auto tempElem = StackTop(stackChar);
					if (tempElem == '!' ||
						Priority(tempElem) > Priority(symbol) ||
						tempElem == symbol)
					{
						if (tempElem == '!')
						{
							auto left = StackTop(stackTree);
							StackPop(&stackTree);
							auto elem = CreateNegationElement(tempElem, left);
							StackPush(&stackTree, elem);
						}
						else
						{
							auto right = StackTop(stackTree);
							StackPop(&stackTree);
							auto left = StackTop(stackTree);
							StackPop(&stackTree);
							auto elem = CreateSumOrMultiplyElement(tempElem, left, right);
							StackPush(&stackTree, elem);
						}

						StackPop(&stackChar);
					}
					else
						break;
				}
				StackPush(&stackChar, symbol);
			}
		}
	}

	while (!StackIsEmpty(stackChar))
	{
		auto tempElem = StackTop(stackChar);
		StackPop(&stackChar);

		if (tempElem == '!')
		{
			auto left = StackTop(stackTree);
			StackPop(&stackTree);
			auto elem = CreateNegationElement(tempElem, left);
			StackPush(&stackTree, elem);
		}
		else
		{
			auto right = StackTop(stackTree);
			StackPop(&stackTree);
			auto left = StackTop(stackTree);
			StackPop(&stackTree);
			auto elem = CreateSumOrMultiplyElement(tempElem, left, right);
			StackPush(&stackTree, elem);
		} 
	}

	return StackTop(stackTree);
}

// Функция вычсляет значения дерева через postorder обход
char EvalValueTree(Tree* element)
{
	if (IsDigitOperand(element->value))
		return element->value;

	if (IsOperator(element->value))
	{
		if (element->value == '!')
		{
			auto leftValue = EvalValueTree(element->Left);
			if (leftValue == '0')
				return '1';

			return '0';
		}
		
		auto leftValue = EvalValueTree(element->Left);
		auto rightValue = EvalValueTree(element->Right);
		return(CalcBinOperation(leftValue, rightValue, element->value));
	}
	
	return IllegalValue;
}
