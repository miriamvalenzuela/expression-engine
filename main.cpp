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

int precedence(const string& op) {
    // TODO
    return 0;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    // TODO
    return false;
}

bool isValidInfix(const vector<Token>& tokens) {
    // TODO
    return false;
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
    // TODO
    return 0.0;
}

// Main

int main() {


    string line;
    getline(cin, line);

    vector<Token> tokens = tokenize(line);

    // Temporary Test for Tokenize
    // TODO: Delete test in next commit.
    cout << "TOKENS: ";
    for (const auto& t : tokens) cout << "[" << t.value << "] ";
    cout << endl;

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
