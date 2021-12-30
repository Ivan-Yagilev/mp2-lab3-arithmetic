// реализация функций и классов для вычисления арифметических выражений

#include "../include/arithmetic.h"

int Lexeme::priority()
{
	if (operation == '(' || operation == ')')
		return 0;
	else if (operation == '+' || operation == '-')
		return 1;
	else if (operation == '*' || operation == '/')
		return 2;
	else if (operation == '_')
		return 3;
}

void Solver::string_to_lexeme(string& expression)
{
	for (size_t i = 0; i < expression.length(); i++)
	{
		// operations
		for (size_t j = 0; j < oper.length()-2; j++)
		{
			if (expression[i] == oper[j])
			{
				Lexeme l(expression[i]);
				lex.push_back(l);
			}
		}
		
		if (expression[i] == '-')
		{
			if (i == 0)
			{
				Lexeme l('_');
				lex.push_back(l);
			}
			else
			{
				if (expression[i - 1] != ')' && (expression[i - 1] == '+' || expression[i - 1] == '-' || expression[i - 1] == '*' || expression[i - 1] == '/' || expression[i - 1] == '('))
				{
					Lexeme l('_');
					lex.push_back(l);
				}
				else
				{
					Lexeme l('-');
					lex.push_back(l);
				}
			}
		}

		// variables
		for (size_t j = 10; j <= number.length(); j++)
		{
			if (expression[i] == number[j])
			{
				if (i > 0 && ((expression[i-1] >= '0' && expression[i-1] <= '9') || (expression[i - 1] >= 'a' && expression[i - 1] <= 'z')))
				{
					Lexeme m('*');
					lex.push_back(m);
				}
				Lexeme l(expression[i]);
				lex.push_back(l);
			}
		}

		// values
		if ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.')
		{
			int point_count = 0;
			string str_number;
			int k = 0;
			if ((i+k) <= expression.length()) {
				while ((expression[i + k] >= '0' && expression[i + k] <= '9') || expression[i + k] == '.')
				{
					str_number += expression[i + k];
					k++;
					if (expression[i + k] == '.')
					{
						point_count++;
						if (point_count > 1)
							throw "many point error";
					}
				}
			}
			i = i + k - 1;
			double numb = stof(str_number);
			Lexeme l(numb);
			lex.push_back(l);
		}
	}
}

void Solver::lexeme_to_reverse()
{
	vector <Lexeme> reverse;
	Stack <Lexeme> op(lex.size());
	Variables v;
	for (size_t i = 0; i < lex.size(); i++)
	{
		if (lex[i].get_type() == false && lex[i].get_operation() <= 'z' && lex[i].get_operation() >= 'a')
		{
			bool flag2 = false;
			for (size_t j = 0; j < v.key.size(); j++)
			{
				if (lex[i].get_operation() == v.key[j])
					flag2 = true;
			}
			if (!flag2)
			{
				v.key.push_back(lex[i].get_operation());
				cout << "Enter the value of the ";
				lex[i].print_lexeme();
				cout << endl;
				double numb;
				while (true)
				{
					cin >> numb;
					std::stringstream ss;
					ss << numb;
					string str_numb;
					ss >> str_numb;
					bool f = false;
					for (size_t j = 0; j <= str_numb.length(); j++)
					{
						if (strchr("0123456789.", str_numb[j]) == nullptr)
						{
							cout << "incorrect input" << endl;
							f = true;
							break;
						}
					}
					if (f)
						exit(1);
					break;
				}
				v.var.push_back(numb);
			}
		}
	}

	for (size_t i = 0; i < lex.size(); i++)
	{
		if (lex[i].get_type() == true)
			reverse.push_back(lex[i]);
		else
		{
			bool flag = false;
			if (lex[i].get_operation() <= 'z' && lex[i].get_operation() >= 'a')
			{
				flag = true;
				for (size_t j = 0; j < v.key.size(); j++)
				{
					if (lex[i].get_operation() == v.key[j])
					{
						reverse.push_back(v.var[j]);
					}
				}
			}

			if (lex[i].get_operation() == '(')
			{
				op.push(lex[i]);
				continue;
			}
			else if (lex[i].get_operation() == ')')
			{
				while (op.get_end().get_operation() != '(')
					reverse.push_back(op.pop());
				op.pop();
				continue;
			}

			if (i > 0 && lex[i].get_operation() == '_')
				op.push(lex[i]);
			else
			{
				while (!op.empty() && op.get_end().priority() >= lex[i].priority())
					reverse.push_back(op.pop());
				if (!flag)
					op.push(lex[i]);
			}
		}
	}
	while (!op.empty())
		reverse.push_back(op.pop());
	lex = reverse;
}

double Solver::calculation()
{
	Stack <Lexeme> stack;
	Lexeme lex_operand1;
	Lexeme lex_operand2;
	double operand1, operand2, res;
	for (size_t i = 0; i < lex.size(); i++)
	{
		if (lex[i].get_type() == true)
			stack.push(lex[i].get_value());
		else if (lex[i].get_operation() == '_')
		{
			res = (-1) * stack.pop().get_value();
			stack.push(res);
		}
		else
		{
			lex_operand2 = stack.pop();
			lex_operand1 = stack.pop();
			operand1 = lex_operand1.get_value();
			operand2 = lex_operand2.get_value();
			if (lex[i].get_operation() == '-')
				res = operand1 - operand2;
			if (lex[i].get_operation() == '+')
				res = operand1 + operand2;
			if (lex[i].get_operation() == '*')
				res = operand1 * operand2;
			if (lex[i].get_operation() == '/')
			{
				if (operand2 == 0)
					throw "division error";
				res = operand1 / operand2;
			}
			stack.push(res);
		}
	}
	Lexeme result = stack.pop();
	return result.get_value();
}

bool validation(const string& str)
{
	if (brackets_check(str) == false)
		throw "brackets error";
	else if (symbols_check(str) == false)
		throw "symbols error";
	else if (input(str) == false)
		throw "input error";
	else if (points_operation_check(str) == false)
		throw "point error";
	else
		return true;
}
bool brackets_check(const string& str)
{
	if (str[0] == ')' || str[str.length() - 1] == '(')
		return false;
	int count = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			if (i < str.length())
				for (size_t j = 0; j < oper.length()-1; j++)
					if (str[i+1] == oper[j])
						throw "operation after braket";
					
			if (i > 0)
				for (size_t j = 0; j < number.length(); j++)
					if (str[i-1] == number[j])
						throw "number before bracket";
			count++;
		}
		if (str[i] == ')')
		{
			if (i < str.length())
				for (size_t j = 0; j < number.length(); j++)
					if (str[i + 1] == number[j])
						throw "number after braket";

			if (i > 0)
				for (size_t j = 0; j < oper.length(); j++)
					if (str[i - 1] == oper[j])
						throw "operation before bracket";
			count--;
		}
	}
	if (count == 0)
		return true;
}
bool symbols_check(const string& str)
{
	bool flag = false;
	for (size_t i = 0; i < str.length(); i++)
	{
		string concatenation = oper + number;
		for (size_t j = 0; j < concatenation.length(); j++) 
		{
			if (str[i] != concatenation[j])
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
		else
			return false;
				
	}
	return flag;
}
bool input(const string& str)
{
	for (size_t i = 1; i < str.length(); i++)
	{
		if (str[i - 1] <= 'z' && str[i - 1] >= 'a' && str[i] >= '0' && str[i] <= '9')
			return false;
		if ((str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == '*' || str[i - 1] == '/') && (str[i] == '+' || str[i] == '*' || str[i] == '/'))
			return false;
	}
	if ((str[0] == '+' || str[0] == '*' || str[0] == '/') || (str.length() == 1 && (str[0] == '.' || str[0] == '-')))
		return false;
	else if (str[str.length() - 1] == '+' || str[str.length() - 1] == '-' || str[str.length() - 1] == '*' || str[str.length() - 1] == '/')
		return false;
	else
		return true;
}
bool points_operation_check(const string& str)
{
	for (size_t i = 1; i < str.length(); i++)
	{
		if (str[i] == '.' && (str[i - 1] == '(' || str[i - 1] == ')' || str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == '*' || str[i - 1] == '/'))
			return false;
	}
	return true;
}