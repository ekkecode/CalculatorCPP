#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

bool isNumber(char x)
{
    char numbers[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    for (char& c : numbers)
    {
        if (x == c)
        {
            return true;
        }
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

double calculate(string equation)
{
    //Special case for negative number (a bit stupid but the most efficient way)
    //The only case where an operation will be accepted before an number is if it's negative
    //Checks for negative number and manually adds the following number in the vector as a negative one
    bool isNegative = equation[0] == '-';

    vector<double> numbers;
    vector<char> operations;

    cout << "Input:" << equation << endl;

    for (int i = 0; i <= equation.length(); i++)
    {
        char c = equation[i];
        //cout << ":" << c << ":" << endl;
        //Skips if the char is blankspace
        if (c == ' ' || c == ' ') continue;

        //CheckForNumber
        if (isNumber(c))
        {
            int numberBeginning = i;
            int numberEnding = i;

            for (int y = numberBeginning; y <= equation.length(); y++)
            {
                if (!isNumber(equation[y]))
                {
                    numberEnding = y;
                    i = y - 1;
                    break;
                }
            }

            double number = stod(equation.substr(numberBeginning, numberEnding));
            numbers.push_back(number);
        }
        else if (isOperator(c))
        {
            operations.push_back(c);
        }
        else
        {
            continue;
        }
    }

    double sum = 0;

    if (!isNegative)
    {
        operations.insert(operations.begin(), '+');
    }

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
    //cout << "Svar: " << findFirstSubequation(input) << endl;
    while(hasParantes(input))
    {
        SubString sa = findFirstSubequation(input);
        double value = calculate(sa.value);
        input = input.erase(sa.start, sa.length);
        input = input.insert(sa.start, to_string(value));

        cout << "Snart-Svar" << input << endl;
    }

    //cout << "Slutligen: " << calculate(input) << endl;
    return calculate(input);
}
