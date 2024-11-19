#pragma once

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "ourdeque.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;

class evaluator {
public:
    string read_expression();
    string convert_to_postfix(string s);
    double evaluate_postfix(string s);
};

// �������� �켱������ ��ȯ�ϴ� �Լ�
int get_operator_precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0; // �����ڰ� �ƴ� ���
}


string evaluator::read_expression() {
    int i = 0;
    string input;
    string infix = "";
    dequeue<char> infix_str;

    cout << "infix�� �Է����ּ���('quit' �Է����� ����): ";
    // ������ ���� �Է� �ޱ�
    getline(cin, input);

    // input�� deque�� ����
    for (i = 0; i < input.length(); i++) {
        if (strchr("+-/*", input[i]) != NULL) {
            // ������ �յڿ� ����
            infix_str.push_back(' ');
            infix_str.push_back(input[i]);
            infix_str.push_back(' ');
        }
        else if (strchr("(", input[i]) != NULL) {
            // ���� ��ȣ �ڿ� ����
            infix_str.push_back(input[i]);
            infix_str.push_back(' ');
        }
        else if (strchr(")", input[i]) != NULL) {
            // ������ ��ȣ �տ� ����
            infix_str.push_back(' ');
            infix_str.push_back(input[i]);
        }
        else if (input[i] == ' ') {
            // ���� ����
            continue;
        }
        else {
            // ����, ������, ��ȣ�� ������ ���� push ����.
            infix_str.push_back(input[i]);
        }
    }

    // infix�� ������ ����
    while (1) {
        if (infix_str.empty() == 1) {
            break;
        }
        // string �߰�
        infix.push_back(infix_str.front());
        infix_str.pop_front();
    }

    infix.push_back(' ');
    cout << "infix :" << infix << endl;
    return infix;
}


string evaluator::convert_to_postfix(string s) {
    const char BLANK = ' ';
    string postfix = "";
    map<char, double> variable_values;
    dequeue<char> operator_stack;

    istringstream iss(s);
    string token;
    while (iss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1) || (isalpha(token[0]) && token.size() == 1) || (token[0] == '.')) {
            // ������ ǥ��
            postfix += token + BLANK;
        }
        else if (token.size() == 1 && isblank(token[0])) {
            // ���� ����
            continue;
        }
        else if (token == "(") {
            // ���� ��ȣ: ������ ���ÿ� Ǫ��
            operator_stack.push_back('(');
        }
        else if (token == ")") {
            // ������ ��ȣ: ������ ���ÿ��� ���� ��ȣ�� ���� ������ �����ڸ� ���
            while (!operator_stack.empty() && operator_stack.back() != '(') {
                postfix += operator_stack.back();
                operator_stack.pop_back();
                postfix += BLANK;
            }
            if (!operator_stack.empty() && operator_stack.back() == '(') {
                operator_stack.pop_back(); // ���� ��ȣ�� ��
            }
        }
        else if (token.size() >= 2 && token[0] == '-' && isdigit(token[1])) {
            // ����
            postfix += token + BLANK;
        }
        else {
            // ������
            char op = token[0];
            while (!operator_stack.empty() && operator_stack.back() != '(' && get_operator_precedence(operator_stack.back()) >= get_operator_precedence(op)) {
                // ���ÿ��� �켱������ ���ų� ���� �����ڸ� ���Ͽ� ���
                postfix += operator_stack.back();
                operator_stack.pop_back();
                postfix += BLANK;
            }
            // ���� �����ڸ� ���ÿ� Ǫ��
            operator_stack.push_back(op);
        }
    }

    // ���ÿ� �����ִ� ��� �����ڸ� ���
    while (!operator_stack.empty()) {
        postfix += operator_stack.back();
        operator_stack.pop_back();
        postfix += BLANK;
    }

    cout << "postfix : " << postfix << endl;
    return postfix;
}


double evaluator::evaluate_postfix(string s) {
    const char BLANK = ' ';
    // ���� �̸� �� �� ����
    map<char, double> variable_values; 

    dequeue<double> value_stack;

    istringstream iss(s);
    string token;
    while (iss >> token) {
        if (isdigit(token[0]) || ((token[0] == '-' || token[0] == '.') && (isdigit(token[1]) || token[1] == '.'))) {
            // ����, ���� ����, �Ǵ� ������ ��� ���ÿ� Ǫ��
            value_stack.push_back(stod(token));
        }
        else if (isalpha(token[0]) && token.size() == 1) {
            char variable = token[0];
            double value;

            if (variable_values.find(variable) == variable_values.end()) {
                // ���� ���� �˷����� ���� ��� ����ڷκ��� �Է� ����
                cout << "Enter " << variable << ": ";
                cin >> value;
                // ���� ���ڸ� ����
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                variable_values[variable] = value;
            }
            else {
                value = variable_values[variable];
            }

            // ���� ���� ���ÿ� Ǫ��
            value_stack.push_back(value);
        }
        else if (token.size() == 1 && isblank(token[0])) { // ������ ����
            continue;
        }
        else {
            double operand2 = value_stack.back();
            value_stack.pop_back();
            double operand1 = value_stack.back();
            value_stack.pop_back();

            double result;
            char op = token[0];
            switch (op) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0) {
                    cerr << "Error (0���� ����)" << endl;
                    return 0.0; // ���� ó��
                }
                result = operand1 / operand2;
                break;
            default:
                cerr << "Error (�˼� ���� ������)" << endl;
                return 0.0; // ���� ó��
            }
            value_stack.push_back(result);
        }
    }

    cout << "Result : " << value_stack.front() << endl << endl;
    return value_stack.front();
}


#endif