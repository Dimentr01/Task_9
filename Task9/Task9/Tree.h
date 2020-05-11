#pragma once
#include <string>

// узел дерева
struct Tree
{
	char value;
	Tree* Left;
	Tree* Right;
};

// Функция строит дерево по инфиксной записи и возвращает указатель на вершину дерева
Tree* CreateTreeViaInfix(const std::string& expr);

// Функция выводит дерево на печать через inorder обход
void ShowTreeInorder(Tree* top, int n);

// Функция вычсляет значения дерева через postorder обход
char EvalValueTree(Tree* element);