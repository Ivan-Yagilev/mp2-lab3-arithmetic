// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <string>
#include <vector>
#include <iostream>
#include "stack.h"

using std::string;
using std::vector;

const string allowed_lexemes = "0123456789.()+-/*";

class Lexeme
{
private:
	char operation;
	double value;
	bool type;
public:
	Lexeme() = default;
	Lexeme(const double& _value) 
	{
		value = _value;
		type = true;
	}
	Lexeme(const char& _operation) 
	{
		operation = _operation;
		type = false;
	}
	void print_lexeme() 
	{
		if (type)
			std::cout << value << " ";

		else
			std::cout << operation << " ";

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

class Arithmetic
{
private:
	vector<Lexeme> lexemes;
public:
	Arithmetic() = default;

	void string_to_lexeme(string& expression);
	void term_to_polish();
	double calculate();
	void print() 
	{
		for (size_t i = 0; i < lexemes.size(); i++) 
		{
			Lexeme lexeme(lexemes[i]);
			lexeme.print_lexeme();
		}
	}
};

bool brackets(const string& s);
bool symbols(const string& s);
bool validation(const string& s);