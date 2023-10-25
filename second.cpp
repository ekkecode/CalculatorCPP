#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

bool isNumber(char x)
{
    char numbers[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    for (char& c : numbers)
    {
        if (x == c) return true;
    }

    return false;
}

bool isOperator(char x)
{
    char numbers[4] = {'+', '-', '*', '/'};
    for (char& c : numbers)
    {
        if (x == c) return true;
    }

    return false;
}

double operate(double sum, double d, char operation)
{
    switch(operation)
    {
    case '+':
        return sum + d;
        break;
    case '-':
        return sum - d;
        break;
    case '*':
        return sum * d;
        break;
    case '/':
        return sum / d;
        break;
    default:
        return sum;
        break;
    }
}

//Linear equation, from left to right
double calculate(string equation)
{
    vector<double> numbers;
    vector<char> operations;

    int negativeSwitcher = 1;

    //Special case if first char is negative
    if (equation[0] == '-')
    {
        negativeSwitcher = -1;
    }

    bool freshOperator = false;

    for (int i = 0; i <= equation.length(); i++)
    {
        char c = equation[i];

        //CheckForNumber
        if (isNumber(c))
        {
            int numberBeginning = i;
            int numberEnding = i;

            //Find last letter in number
            for (int y = numberBeginning; y <= equation.length(); y++)
            {
                if (!isNumber(equation[y]))
                {
                    numberEnding = y;

                    //Checks if number is negative
                    if (i >= 2 && isOperator(equation[i-2]))
                    {
                        if (equation[i-1] == '-')
                        {
                            negativeSwitcher = -1;
                        }
                    }
                    else
                    {
                        negativeSwitcher = equation[0] == '-' ? -1 : 1;
                    }

                    i = y - 1;
                    break;
                }
            }

            double number = stod(equation.substr(numberBeginning, numberEnding));
            number = number * negativeSwitcher;
            numbers.push_back(number);
            freshOperator = false;
        }
        //Check for operator
        else if (isOperator(c) && i > 0)
        {
            if (freshOperator == false)
            {
                operations.push_back(c);
                freshOperator = true;
            }
        }
    }

    double sum = 0;

    operations.insert(operations.begin(), '+');
    for (double& d : numbers)
    {
        sum = operate(sum, d, operations.front());
        if (operations.size() != 0 )
        {
            operations.erase(operations.begin());
        }
    }

    return sum;
}

class SubString
{
public:
    int start;
    int length;
    string value;
    SubString(int start, int end, string value)
    {
        this->start = start;
        this->length = end - start + 1;
        this->value = value;
    }
};

SubString findFirstSubequation(string input)
{
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '(')
        {
            for (int y = i; y < input.size(); y++)
            {
                if (input[y] == ')')
                {
                    SubString sa(i, y, input.substr(i+1, y-i-1));
                    return sa;
                }
                else if (input[y] == '(')
                {
                    i = y;
                    continue;
                }
            }
        }
    }
}

bool hasParantes(string input)
{
    for (char &c : input)
    {
        if (c == '(' || c == ')')
        {
            return true;
        }
    }

    return false;
}

double MainCalculate(string input)
{
    while(hasParantes(input))
    {
        SubString sa = findFirstSubequation(input);
        double value = calculate(sa.value);
        input = input.erase(sa.start, sa.length);
        input = input.insert(sa.start, to_string(value));
    }
    return calculate(input);
}
