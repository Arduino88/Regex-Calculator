#include <algorithm>
#include <conio.h>
#include <cmath>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <locale>
#include <limits>
#include <functional>

using namespace std;

string validCharString = "+-/*^r";

struct input {
    double structInput1;
    double structInput2;
    char structOperation;
};

enum operation 
{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER,
    ROOT,
};

bool checkString(string str, const string& acceptableChars)
{
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
  regex pattern("[+-]?[0-9]*\\.?[0-9]+[" + acceptableChars + "][+-]?[0-9]*\\.?[0-9]+");
  return regex_match(str, pattern);
}

operation charToEnum (char inputOperation) 
{
    operation selectedOperation;
    switch (inputOperation) 
    {
        case '+':
            selectedOperation = ADDITION;
            break;
        case '-':
            selectedOperation = SUBTRACTION;
            break;
        case '*':
            selectedOperation = MULTIPLICATION;
            break;
        case '/':
            selectedOperation = DIVISION;
            break;
        case '^':
            selectedOperation = POWER;
            break;
        case 'r':
            selectedOperation = ROOT;
            break;
    }
    return selectedOperation;
}

double calculate(const double &input1, const double &input2, operation calculateOperation) {
    switch (calculateOperation) 
    {
        case ADDITION:
            return (input1 + input2);
            break;
        case SUBTRACTION:
            return (input1 - input2);
            break;
        case MULTIPLICATION:
            return (input1 * input2);
            break;
        case DIVISION:
            return (input1 / input2);
            break;
        case POWER:
            return (pow (input1, input2));
            break;
        case ROOT:
            return (pow (input1, 1.0 / input2));
            break;
        default:
            return 0;
    }
}

void parseRawInput(string &rInput, string operatorList, input &i)
{
    int operatorLocation = rInput.find_first_of(operatorList);
    i.structOperation = rInput[operatorLocation];
    i.structInput1 = stod(rInput.substr(0, operatorLocation));
    i.structInput2 = stod(rInput.substr(operatorLocation + 1, rInput.length()));
}

bool menu(string &menuRawInput) {
    cout << "\nFunction List: Addition (+)\n               Subtraction (-)\n               Multiplication (+)\n               Division (/)\n               Exponent (^)\n               Root (r)\n\nType \"Exit\" to exit program.\nType any key and hit enter to continue.";
    cin >> menuRawInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(menuRawInput == "Exit") {
        return false;
    } else {
        return true;
    }
}

int main() {
    system("PAUSE");
    input inputPrimary;
    string rawInput, exitInput;
    operation mainSelectedOperation;
    double result;
    bool loopMain = true, displayHeader = true , doGetline = true;
    while (loopMain) {
        if(displayHeader){
            cout << "-------------------------------------------\nCalculator v1.5 by Simon Siena (E for Menu)\n-------------------------------------------\n\n";
        }
        cout << "Enter the desired calculation: ";
        getline(cin, rawInput);
        exitInput = rawInput;
        transform(exitInput.begin(), exitInput.end(), exitInput.begin(), [](unsigned char c) {
            return toupper(c);
        });
        if(((exitInput.find_first_not_of("E") == string::npos) || (exitInput.find_first_not_of("E") > 0)) && !(exitInput.length() > 1)) {
                loopMain = menu(rawInput);
        } else {
            if (!checkString(rawInput, validCharString)) {
                cout << "ERROR - Please enter a valid calculation (ex: 3 + 12)\n";
            } else {
                parseRawInput(rawInput, validCharString, inputPrimary);
                result = calculate(inputPrimary.structInput1, inputPrimary.structInput2, charToEnum(inputPrimary.structOperation));
                cout << "Solution: " << result << "\n\n";
            }
            displayHeader = false;
        }
    }
    return 0;
}

