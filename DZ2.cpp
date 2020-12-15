#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>

int priority(char top_op, char cur_op)
{
	int top_op_prio, cur_op_prio;
	switch (top_op)
	{
	case '^': 
		top_op_prio = 3;
		break;
	case '*':
	case '/':
		top_op_prio = 2;
		break;
	case '+':
	case '-':
		top_op_prio = 1;
		break;
	case '(':
		top_op_prio = 0;
	}

	switch (cur_op)
	{
	case '^':
		cur_op_prio = 3;
		break;
	case '*':
	case '/':
		cur_op_prio = 2;
		break;
	case '+':
	case '-':
		cur_op_prio = 1;
		break;
	}

	return top_op_prio - cur_op_prio;
}

bool isoper(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool isfunc(std::string s)
{
	const char* c = s.c_str();
	return !(strcmp(c, "cos") && strcmp(c, "sin") && strcmp(c, "tan") && strcmp(c, "ctg") && strcmp(c, "sqr") && strcmp(c, "exp"));
}

const double pi = 3.14159;
const double e = 2.71828;

int main()
{
	std::cout << "List of operators:\ncos, sin, tan, ctg, sqr, exp\n+, -, *, /, ^\n";
	std::cout << "Consts: pi and e\n";
	std::cout << "Write fractions with dots\n";
	double a, b;
	std::string count_it;
	std::getline(std::cin, count_it);
	//обработка строки и возможных ошибок перед использованием ОПЗ
	int dots = 0;
	bool f = 0;
	std::string x;
	for (int i = 0; i < count_it.length(); ++i)
	{
		if (count_it[i] == 'x')
		{
			if (!f)
			{
				std::cout << "Insert x\n";
				std::cin >> x;
				f = 1;
			}
			count_it.erase(i, 1);
			count_it.insert(i, x);
		}
		if (count_it[i] == 'i' && i != 0)
		{
			if (count_it[i - 1] == 'p') count_it.erase(i, 1);
		}
		if (count_it[i] == ' ') count_it.erase(i, 1);
		if (count_it[i] == '-' && (i == 0 || (!(isdigit(count_it[i - 1])) && count_it[i - 1] != ')'
			&& count_it[i - 1] != 'p' && count_it[i - 1] != 'E')))
		{
			count_it.insert(i, "0");
		}
		if (count_it[i] == 'e')
		{
			if (i == count_it.length() - 1) count_it[i] = 'E';
			else if (!isalpha(count_it[i + 1])) count_it[i] = 'E';
		}
	}
	//std::cout << count_it << std::endl;
	int left = 0;
	int right = 0;
	for (int i = 0; i < count_it.length(); ++i)
	{
		if (count_it[i] == '(')
		{
			if (i != (count_it.length() - 1) && !isalpha(count_it[i + 1]) && !isdigit(count_it[i + 1]) && count_it[i + 1] != '(')
			{

				std::cout << "Inavalid input";
				return 0;
			}
			if (i != 0 && !(isoper(count_it[i - 1]) || isalpha(count_it[i - 1]) || count_it[i - 1] == '('))
			{
				std::cout << "Inavalid input";
				return 0;
			}
			left++;
		}
		else if (count_it[i] == ')')
		{
			if (i != (count_it.length() - 1) && !isoper(count_it[i + 1]) && count_it[i + 1] != ')')
			{
				std::cout << "Inavalid input";
				return 0;
			}
			if (i != 0 && !isdigit(count_it[i - 1]) && count_it[i - 1] != ')')
			{
				std::cout << "Inavalid input";
				return 0;
			}
			right++;
		}
		else if (count_it[i] == '.')
		{
			dots++;
			if ((i != (count_it.length() - 1) && !isdigit(count_it[i + 1])) || (i == count_it.length() - 1))
			{
				std::cout << "Dot without fraction part";
				return 0;
			}
			if (i == 0 || (i != 0 && !isdigit(count_it[i - 1])))
			{
				std::cout << "Dot without integer part";
				return 0;
			}
		}
		else if (isalpha(count_it[i]))
		{
			if (count_it[i] == 'E' || count_it[i] == 'p' || count_it[i] == 'x')
			{
				i -= 2;
			}
			else if (i >= count_it.length() - 5)
			{
				std::cout << "Unexpected function";
				return 0;
			}
			else if (!(isfunc(count_it.substr(i, 3))))
			{
				std::cout << "Unexpected function: " << count_it.substr(i, 3);
				return 0;
			}
			else if (count_it[i + 3] != '(')
			{
				std::cout << "Invalid input";
				return 0;
			}
			else if (i != 0 && !isoper(count_it[i - 1]) && count_it[i - 1] != '(')
			{
				std::cout << "Invalid input";
				return 0;
			}
			i += 2;
		}
		else if (isdigit(count_it[i]))
		{
			if (i != (count_it.length() - 1) && !(isdigit(count_it[i + 1]) || count_it[i + 1] == '.' ||
				isoper(count_it[i + 1]) || count_it[i + 1] == ')'))
			{
				std::cout << "Invalid input";
				return 0;
			}
			else if (i != 0 && !(isdigit(count_it[i - 1]) || count_it[i - 1] == '.' ||
				isoper(count_it[i - 1]) || count_it[i - 1] == '('))
			{
				std::cout << "Invalid input";
				return 0;
			}
		}
		else if (isoper(count_it[i]))
		{
			if (i == 0 || i == (count_it.length() - 1))
			{
				std::cout << "Invalid input";
				return 0;
			}
			if (isoper(count_it[i + 1]) || isoper(count_it[i - 1]))
			{
				std::cout << "Invalid input";
				return 0;
			}
		}
		else
		{
		std::cout << "Unexpected symbol";
		return 0;
		}
		if (dots && !isdigit(count_it[i]) && count_it[i] != '.') dots--;
		if (dots >= 2)
		{
			std::cout << "Too many dots" << std::endl;
			return 0;
		}
		if (left - right < 0)
		{
			std::cout << "Order of brackets";
			return 0;
		}
	}
	if (left != right)
	{
		std::cout << "Not enough brackets" << std::endl;
		return 0;
	}
	//std::cout << count_it;
	//начало основной части программы
	std::string in;
	std::string part = "";
	f = 0;
	std::cout << std::endl;
	std::stack<std::string> st_OPZ;
	for (int i = 0; i < count_it.length(); ++i)
	{
		if (isdigit(count_it[i]) || count_it[i] == 'p' || count_it[i] == 'E' || count_it[i] == '.')
		{
			in += count_it[i];
			//std::cout << in << std::endl;
			f = 1;
		}
		else
		{
			if (f)
			{
				in += " ";
				f = 0;
			}
			if (isalpha(count_it[i]))
			{
				st_OPZ.push(count_it.substr(i, 3));
				i += 2;
			}
			if (count_it[i] == '(') st_OPZ.push("(");
			if (count_it[i] == ')')
			{
				while (st_OPZ.top() != "(")
				{
					in += st_OPZ.top();
					in += " ";
					st_OPZ.pop();
				}
				st_OPZ.pop();
				if (!st_OPZ.empty())
				{
					if (isfunc(st_OPZ.top()))
					{
						in += st_OPZ.top();
						in += " ";
						st_OPZ.pop();
					}
				}
			}
			if (isoper(count_it[i]))
			{
				if (st_OPZ.empty())
				{
					part += count_it[i];
					st_OPZ.push(part);
					part = "";
				}
				else
				{
					part = st_OPZ.top();
					while ((priority(part[0], count_it[i]) >= 0) && (!st_OPZ.empty() && st_OPZ.top() != "("))
					{
						in += st_OPZ.top();
						in += " ";
						st_OPZ.pop();
					}
					part = "";
					part += count_it[i];
					st_OPZ.push(part);
					part = "";
				}
			}
		}
		//std::cout << in << "|" << std::endl;
		//if (!st_OPZ.empty()) std::cout << st_OPZ.top() << std::endl;
	}
	in += " ";
	while (!st_OPZ.empty())
	{
		in += st_OPZ.top();
		in += " ";
		st_OPZ.pop();
	}
	//std::cout << "|" << in << "|\n";
	std::stringstream OPZ;
	
	OPZ << in;
	while (OPZ >> part)
	{
		if (!(isoper(part[0]) || isfunc(part)))
		{
			if (part[0] == 'E')
			{
				st_OPZ.push(std::to_string(e));
			}
			else if (part[0] == 'p')
			{
				st_OPZ.push(std::to_string(pi));
			}
			else
			{
				st_OPZ.push(part);
			}
		}
		else
		{
			if (isfunc(part))
			{
				if (!st_OPZ.empty())
				{
					a = std::stod(st_OPZ.top());
					st_OPZ.pop();
				}
				if (part == "sin")
					st_OPZ.push(std::to_string(sin(a)));
				if (part == "cos")
					st_OPZ.push(std::to_string(cos(a)));
				if (part == "tan")
					st_OPZ.push(std::to_string(tan(a)));
				if (part == "ctg")
					st_OPZ.push(std::to_string(1 / tan(a)));
				if (part == "sqr")
				{
					if (a < 0)
					{
						std::cout << "sqrt from negative value cannot be taken";
						return 0;
					}
					st_OPZ.push(std::to_string(sqrt(a)));
				}
				if (part == "exp")
					st_OPZ.push(std::to_string(pow(e, a)));
			}
			else
			{
				if (!st_OPZ.empty())
				{
					a = std::stod(st_OPZ.top());
					st_OPZ.pop();
				}
				if (!st_OPZ.empty())
				{
					b = std::stod(st_OPZ.top());
					st_OPZ.pop();
				}
				if (part[0] == '+')
					st_OPZ.push(std::to_string(b + a));
				if (part[0] == '-')
					st_OPZ.push(std::to_string(b - a));
				if (part[0] == '*')
					st_OPZ.push(std::to_string(b * a));
				if (part[0] == '/')
				{
					if (a == 0)
					{
						std::cout << "division by zero is not defined";
						return 0;
					}
					st_OPZ.push(std::to_string(b / a));
				}
				if (part[0] == '^')
					st_OPZ.push(std::to_string(pow(b, a)));
			}
		}
	}
	std::cout << "Answer: " << st_OPZ.top();
	return 0;
}

