#include <iostream>
#include <string>
#include "stack.cpp"
using namespace std;

int precedence(char operation)
{
    switch (operation)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

class Operations
{
private:
    // Operator priority: a higher number is applied first
    int precedence(char operation)
    {
        switch (operation)
        {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
        }
    }

    bool isOperand(char value)
    {
        return (value >= 'A' && value <= 'Z') ||
               (value >= 'a' && value <= 'z') ||
               (value >= '0' && value <= '9');
    }

    bool isOperator(char value)
    {
        return value == '+' || value == '-' || value == '*' ||
               value == '/' || value == '^';
    }

public:
    string infixToPostfix(const string &infix)
    {
        Stack operators;
        string postfix;

        for (size_t i = 0; i < infix.length(); i++)
        {
            char value = infix[i];

            if (value == ' ')
            {
                continue;
            }

            // Operands go straight to the output
            if (isOperand(value))
            {
                postfix += value;
            }
            else if (value == '(')
            {
                operators.push(string(1, value));
            }
            else if (value == ')')
            {
                // Pop operators until the matching '(' is reached, then throw away the '('
                while (!operators.isEmpty() && operators.peek() != "(")
                {
                    postfix += operators.pop();
                }
                if (!operators.isEmpty())
                {
                    operators.pop();
                }
            }
            else if (isOperator(value))
            {
                // Before pushing, pop operators with higher or equal priority, since they must be applied first
                while (!operators.isEmpty() && operators.peek() != "(" &&
                       precedence(operators.peek()[0]) >= precedence(value))
                {
                    postfix += operators.pop();
                }
                operators.push(string(1, value));
            }
        }

        // Whatever operators are left go at the end
        while (!operators.isEmpty())
        {
            postfix += operators.pop();
        }

        return postfix;
    }

    string postfixToInfix(const string &postfix)
    {
        Stack operands;

        for (char value : postfix)
        {
            if (value == ' ')
            {
                continue;
            }

            if (isOperand(value))
            {
                operands.push(string(1, value));
            }
            else if (isOperator(value) && !operands.isEmpty())
            {
                // Operator: combine the last two operands. The first pop is the RIGHT operand,
                // the second pop is the LEFT operand.
                string operand1 = operands.pop();
                string operand2 = operands.pop();
                operands.push("(" + operand2 + " " + string(1, value) + " " + operand1 + ")");
            }
        }

        return operands.isEmpty() ? "" : operands.pop();
    }

    string prefixToInfix(const string &prefix)
    {
        Stack operands;

        // Prefix is read from right to left. 'i-- > 0' counts down safely, since size_t can't go below 0
        for (size_t i = prefix.length(); i-- > 0;)
        {
            char value = prefix[i];

            if (value == ' ')
            {
                continue;
            }

            if (isOperand(value))
            {
                operands.push(string(1, value));
            }
            else if (isOperator(value) && !operands.isEmpty())
            {
                // Reading right to left, the first pop is the LEFT operand and the second is the RIGHT
                string operand1 = operands.pop();
                string operand2 = operands.pop();
                operands.push("(" + operand1 + " " + string(1, value) + " " + operand2 + ")");
            }
        }

        return operands.isEmpty() ? "" : operands.pop();
    }
};

int main()
{
    Operations operations;
    int choice;
    string expression;

    cout << "1. Infix to postfix\n";
    cout << "2. Postfix to infix\n";
    cout << "3. Prefix to infix\n";
    cout << "Enter your choice: ";
    cin >> choice;
    // Drop the newline left by cin >> so getline reads the expression
    cin.ignore();

    switch (choice)
    {
    case 1:
        cout << "Enter the infix expression: ";
        getline(cin, expression);
        cout << "Postfix expression: " << operations.infixToPostfix(expression) << '\n';
        break;
    case 2:
        cout << "Enter the postfix expression: ";
        getline(cin, expression);
        cout << "Infix expression: " << operations.postfixToInfix(expression) << '\n';
        break;
    case 3:
        cout << "Enter the prefix expression: ";
        getline(cin, expression);
        cout << "Infix expression: " << operations.prefixToInfix(expression) << '\n';
        break;
    default:
        cout << "Invalid choice.\n";
    }
}