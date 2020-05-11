#pragma once
#include <string>

static const char* AllOperands = "01abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const char* DigitOperands = "01";

static const char* NonDigitOperands = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const char IllegalValue = '-';

// Функция проверяет принадлежность символа value строке str
bool CharBelongsToString(const char& value, const char* str);

// Функция проверяет value на числовые операнды
bool IsDigitOperand(const char& value);

// Функция проверяет value на операторы
bool IsOperator(const char& value);

// Фукнкция возвращает приоритет операций
int Priority(const char& value);

// Проверяет цифра ли символ
bool IsDigit(const char& value);

// Перевод цифры char в цифру int
int CharToInt(const char& value);

// Переводит цифру int в цифру char
char IntToChar(const int& value);

// Проверка на возможность вычисления выражение (есть или нет буквенные переменные)
bool CanEvaluateValue(const std::string& inputValue);

// Функция вычисляет значение логической операции
char CalcBinOperation(const char& left, const char& right, const char& op);
