// реализация функций и классов для вычисления арифметических выражений

#include "../include/arithmetic.h"
void Arithmetic::string_to_lexeme(string& expression)
{
	string str_number;
	double number;
	size_t i = 0;
	while (i < expression.length()) 
	{
		// - операции
		if (expression[i] == '+' || expression[i] == '*' || expression[i] == '/') 
		{ 
			Lexeme operation(expression[i]);
			lexemes.push_back(operation);
			i++;
		}
		else if (expression[i] == '-') 
		{
			if (i == 0) 
			{
				Lexeme unary_minus('_');
				lexemes.push_back(unary_minus);
				i++;
				continue;
			}
			if (i > 0) 
			{
				if (lexemes[i - 1].get_operation() != ')' && lexemes[i - 1].get_type() == false) 
				{
					Lexeme unary_minus('_');
					lexemes.push_back(unary_minus);
					i++;
				}
				else 
				{
					Lexeme minus('-');
					lexemes.push_back(minus);
					i++;
				}
			}
		}
		// - значения
		else if (expression[i] >= '0' && expression[i] <= '9' || (expression[i] == '.')) 
		{ 
			int point_counter = 0;
			while (expression[i] >= '0' && expression[i] <= '9' || (expression[i] == '.')) 
			{
				str_number += expression[i];
				i++;
				if (expression[i] == '.')
					point_counter++;

				if (point_counter > 1)
					throw "Too much points";
			}
			number = stof(str_number);
			Lexeme number(number);
			lexemes.push_back(number);
			str_number.clear();
		}
		else if (expression[i] == ')' || expression[i] == '(') 
		{
			Lexeme bracket(expression[i]);
			lexemes.push_back(bracket);
			i++;
		}
	}
}
void Arithmetic::term_to_polish()
{
	unsigned size = lexemes.size();
	vector <Lexeme> postfix;
	Stack <Lexeme> operations;
	for (unsigned i = 0; i < size; i++) 
	{
		// - если число
		if (lexemes[i].get_type() == true) 
			postfix.push_back(lexemes[i]);
		// - если операция
		else 
		{
			if (lexemes[i].get_operation() == '(') 
			{
				operations.push(lexemes[i]);
				continue;
			}
			else if (lexemes[i].get_operation() == ')') 
			{
				while (operations.get_top().get_operation() != '(')
					postfix.push_back(operations.pop());

				operations.pop(); // извлечение (
				continue;
			}

			if (i > 0 && lexemes[i].get_operation() == '_')
				operations.push(lexemes[i]);
			else 
			{
				while (!operations.empty() && operations.get_top().priority() >= lexemes[i].priority())
					postfix.push_back(operations.pop());

				operations.push(lexemes[i]);
			}
		}
	}
	while (!operations.empty())
		postfix.push_back(operations.pop());

	lexemes = postfix;
}
double Arithmetic::calculate()
{
	Stack <Lexeme> stack;
	Lexeme termOperand1, termOperand2;
	double operand1, operand2, res;
	for (unsigned i = 0; i < lexemes.size(); i++) 
	{
		if (lexemes[i].get_type() == true)
			stack.push(lexemes[i].get_value());

		else if (lexemes[i].get_operation() == '_') 
		{
			res = (-1) * stack.pop().get_value();
			stack.push(res);
			continue;
		}
		else 
		{
			termOperand2 = stack.pop();
			termOperand1 = stack.pop();
			operand1 = termOperand1.get_value();
			operand2 = termOperand2.get_value();
			if (lexemes[i].get_operation() == '+')
				res = operand1 + operand2;
			if (lexemes[i].get_operation() == '-')
				res = operand1 - operand2;
			if (lexemes[i].get_operation() == '*')
				res = operand1 * operand2;
			if (lexemes[i].get_operation() == '/') 
			{
				if (operand2 == 0) 
					throw "Division by the zero";
				res = operand1 / operand2;
			}

			stack.push(res);
		}
	}
	Lexeme result = stack.pop();
	return result.get_value();
}
bool brackets(const string& s)
{
	bool flag = true;
	int count = 0, stringSize = s.length();
	for (int i = 0; i < stringSize; i++) 
	{
		if (s[i] == '(') 
		{
			count++;
			flag = false;
			if (i < stringSize && s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/')
				throw "Operation after bracket";
			
			if (i > 0 && s[i - 1] >= '0' && s[i] <= '9')
				throw "Number before opening bracket";
		}
		if (s[i] == ')') 
		{
			count--;
			flag = true;
		}
	}
	return (flag == true && count == 0);
}
bool symbols(const string& s)
{
	bool flag = false;
	int stringSize = s.length(), allowedTermsSize = allowed_lexemes.length();
	for (int i = 0; i < stringSize; i++) 
	{
		for (int j = 0; j < allowedTermsSize; j++) 
		{
			if (s[i] != allowed_lexemes[j]) 
			{
				flag = false;
				continue;
			}
			else 
			{
				flag = true;
				break;
			}
		}
		if (flag)
			continue;
		else return false;
	}
	return true;
}
bool validation(const string& s)
{
	if (!brackets(s))
		throw "Wrong brackets";
	
	else if (!symbols(s))
		throw "Can be used: 0123456789.()+-/* without space";
	
	else if (s[0] == '+' || s[0] == '*' || s[0] == '/')
		throw "Operation cannot be at the beginning";
	
	else if (s[s.length() - 1] == '+' || s[s.length() - 1] == '-' || s[s.length() - 1] == '*' || s[s.length() - 1] == '/')
		throw "Operation cannot be at the end";
	
	else return true;
}
int Lexeme::priority()
{
	if (operation == '(' || operation == ')') 
	{ 
		return 0; 
	}
	else if (operation == '+' || operation == '-') 
	{ 
		return 1;
	}
	else if (operation == '*' || operation == '/') 
	{ 
		return 2; 
	}
	else if (operation == '_') 
	{ 
		return 3; 
	}
	else 
		throw "Problems";
}