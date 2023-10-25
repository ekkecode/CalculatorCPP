#include <iostream>
#include <iomanip>
#include <cassert>
#include <list>

using namespace std;

double calculate(string);
double MainCalculate(string);

int main()
{

    string input;

    while (input != "fuckyou")
    {
        cout << "Vanligen ange din input: ";
        cin >> input;
        //input = "30     + 2 * 10";

        double answer = MainCalculate(input);
        cout << "Svar: " << answer << endl << endl << endl;
    }

    return 0;
}
