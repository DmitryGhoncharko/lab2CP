#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(const string& expression) {
    stack<char> operatorStack;
    string postfix;
    unordered_map<char, int> precedenceMap = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

    for (char token : expression) {
        if (isdigit(token)) {
            postfix += token;
        } else if (token == '(') {
            operatorStack.push(token);
        } else if (token == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        } else {

            while (!operatorStack.empty() && precedenceMap[operatorStack.top()] >= precedence(token)) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}

int main() {
    string expression;
    cout << "Введите инфиксное выражение: ";
    getline(cin, expression);

    string postfix = infixToPostfix(expression);
    cout << "Постфиксное (обратная польская) нотация: " << postfix << endl;

    return 0;
}
