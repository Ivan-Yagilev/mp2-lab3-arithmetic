// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <string>
#include <vector>
#include <iostream>
#include "stack.h"
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

const string oper = "()+*/.-";
const string number = "0123456789abcdefghijklmnopqrstuvwxyz";

class Lexeme
{
private:
	char operation;
	double value;
	int type;
public:
	Lexeme() = default;
	Lexeme(const double& tmp_value)
	{
		value = tmp_value;
		type = true;
	}
	Lexeme(const char& tmp_operation)
	{
		operation = tmp_operation;
		type = false;
	}

	void print_lexeme()
	{
		if (type)
			cout << value;
		else
			cout << operation;
	}

	double get_value()
	{
		return value;
	}

	char get_operation()
	{
		return operation;
	}

	bool get_type()
	{
		return type;
	}

	int priority();
};

class Solver
{
private:
	vector <Lexeme> lex;
public:
	void string_to_lexeme(string& expression);
	void lexeme_to_reverse();
	void print()
	{
		for (size_t i = 0; i < lex.size(); i++)
			lex[i].print_lexeme();
	}
	double calculation();
};

class Variables
{
public:
	Variables() = default;
	vector<char> key;
	vector<double> var;
};


bool validation(const string& str);
bool input(const string& str);
bool symbols_check(const string& str);
bool brackets_check(const string& str);
bool points_operation_check(const string& str);