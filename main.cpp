#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

#include "ArrayStack.h"

using namespace std;

// Token

struct Token {
    string value;   // number, operator, or parenthesis
};

// Tokenizer

bool isDigitChar(char c) {
    return c >= '0' && c <= '9';
}

bool isOpChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isParenChar(char c) {
    return c == '(' || c == ')';
}

vector<Token> tokenize(const string& line) {
    vector<Token> tokens;

    int i = 0;
    while (i < static_cast<int>(line.size())) {
        char c = line[i];

        if (isspace(static_cast<unsigned char>(c))) {
            i++;
            continue;
        }

        // number token
        if (isDigitChar(c)) {
            string num = "";
            while (i < static_cast<int>(line.size()) && isDigitChar(line[i])) {
                num += line[i];
                i++;
            }
            tokens.push_back(Token{num});
            continue;
        }

        // operator or parenthesis token
        if (isOpChar(c) || isParenChar(c)) {
            string s(1, c);
            tokens.push_back(Token{s});
            i++;
            continue;
        }

        // invalid character
        tokens.push_back(Token{"INVALID"});
        return tokens;
    }

    return tokens;
}

// Helpers

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

bool isNumber(const string& s) {
    // If the string is empty, it can't be a number
    if (s.empty()) {
        return false;
    }

    // Check every character in the string
    for (char c : s) {
        // If any character is not a digit, it's not a number
        if (!isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    // All characters were digits, so it is a number
    return true;
}

int precedence(const string& op) {
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    // A postfix expression can't be empty
    if (tokens.empty()) {
        return false;
    }

    // Represents how many numbers/results currently "available"
    int depth = 0;

    for (const Token& token : tokens) {
        string v = token.value;

        // If the tokenizer marked something invalid, expression is invalid
        if (v == "INVALID") {
            return false;
        }

        // Parentheses are not allowed in postfix expressions
        if (v == "(" || v == ")") {
            return false;
        }

        // If it's a number, it adds one value to "stack"
        if (isNumber(v)) {
            depth++;
        }
        // If it's an operator, need two values to work
        else if (isOperator(v)) {
            if (depth < 2) {
                return false; // not enough operands for this operator
            }

            // Using two operands and producing one result
            // depth goes down by 1
            depth--;
        }
        // Anything else is invalid
        else {
            return false;
        }
    }

    // Valid post fix expression must end with exactly one final result
    return depth == 1;
}

bool isValidInfix(const vector<Token>& tokens) {
    // Empty input cannot be a valid infix expression
    if (tokens.empty()) {
        return false;
    }

    // Track parentheses, must never go negative, must end at 0
    int openParens = 0;

    // At the start ( and after an operator or "(" ) we expect a number or "("
    bool expectNumberOrLeftParen = true;

    for (const Token& token : tokens) {
        string v = token.value;

        // Tokenizer found an invalid character earlier
        if (v == "INVALID") {
            return false;
        }

        if (expectNumberOrLeftParen) {
            // Expecting number or "("
            if (isNumber(v)) {
                expectNumberOrLeftParen = false;  // Next expect operator or ")" or end
            }
            else if (v == "(") {
                openParens++;
                // Still expect number or "(" next
            }
            else {
                return false; // Invalid order
            }
        }
        else {
            // Expecting operator or ")" ( or end )
            if (isOperator(v)) {
                expectNumberOrLeftParen = true;   // After an operator, need a number or "("
            }
            else if (v == ")") {
                openParens--;
                if (openParens < 0) {
                    return false; // Too many closing parentheses
                }
                // After ")", still expect operator or ")" or end
            }
            else {
                return false; // Invalid order
            }
        }
    }

    // Parentheses must balance out
    if (openParens != 0) {
        return false;
    }

    // Expression must end after a number or ")"
    // If still expecting a number/"(", it means it ended with an operator or "("
    if (expectNumberOrLeftParen) {
        return false;
    }

    return true;
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    // TODO
    return output;
}

// Evaluation

// Decision: use double division (no integer truncation)
double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;

    for (const Token& token : tokens) {
        string v = token.value;

        // If it's a number push it onto the stack
        if (isNumber(v)) {
            double number = stod(v);
            stack.push(number);
        }
        // If it's an operator we need two numbers to apply it
        else if (isOperator(v)) {
            // Make sure there are at least 2 values available
            if (stack.size() < 2) {
                throw runtime_error("not enough operands for operator");
            }

            double right = stack.top();
            stack.pop();

            double left = stack.top();
            stack.pop();

            double answer = 0.0;

            if (v == "+") {
                answer = left + right;
            } else if (v == "-") {
                answer = left - right;
            } else if (v == "*") {
                answer = left * right;
            } else if (v == "/") {
                if (right == 0.0) {
                    throw runtime_error("division by zero");
                }
                answer = left / right; // double division
            } else {
                // This should not happen if isOperator is correct
                throw runtime_error("unknown operator");
            }

            // Push the result back on the stack
            stack.push(answer);
        }
        // Anything else is invalid in postfix evaluation
        else {
            throw runtime_error("invalid token in evalPostfix");
        }
    }

    // At the end, there should be exactly one result left
    if (stack.size() != 1) {
        throw runtime_error("postfix expression did not end with one result");
    }

    return stack.top();
}

// Main

int main() {

    string line;
    getline(cin, line);

    vector<Token> tokens = tokenize(line);

    // Temporary test for isValidInfix
    // TODO: Delete test in next commit
    cout << "Tokens: ";
    for (const auto& t : tokens) {
        cout << "[" << t.value << "] ";
    }
    cout << endl;

    bool infixOk = isValidInfix(tokens);

    cout << "Is this valid INFIX? ";
    if (infixOk) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    if (isValidPostfix(tokens)) {
        cout << "FORMAT: POSTFIX\n";
        cout << "RESULT: " << evalPostfix(tokens) << "\n";
    }
    else if (isValidInfix(tokens)) {
        vector<Token> postfix = infixToPostfix(tokens);
        cout << "FORMAT: INFIX\n";
        cout << "POSTFIX: ";
        for (const auto& t : postfix) {
            cout << t.value << " ";
        }
        cout << "\n";
        cout << "RESULT: " << evalPostfix(postfix) << "\n";
    }
    else {
        cout << "FORMAT: NEITHER\n";
        cout << "ERROR: invalid expression\n";
    }

    return 0;
}
