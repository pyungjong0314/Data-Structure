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

// 연산자의 우선순위를 반환하는 함수
int get_operator_precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0; // 연산자가 아닌 경우
}


string evaluator::read_expression() {
    int i = 0;
    string input;
    string infix = "";
    dequeue<char> infix_str;

    cout << "infix를 입력해주세요('quit' 입력으로 종료): ";
    // 유저로 부터 입력 받기
    getline(cin, input);

    // input을 deque에 저장
    for (i = 0; i < input.length(); i++) {
        if (strchr("+-/*", input[i]) != NULL) {
            // 연산자 앞뒤에 공백
            infix_str.push_back(' ');
            infix_str.push_back(input[i]);
            infix_str.push_back(' ');
        }
        else if (strchr("(", input[i]) != NULL) {
            // 왼쪽 괄호 뒤에 공백
            infix_str.push_back(input[i]);
            infix_str.push_back(' ');
        }
        else if (strchr(")", input[i]) != NULL) {
            // 오른쪽 괄호 앞에 공백
            infix_str.push_back(' ');
            infix_str.push_back(input[i]);
        }
        else if (input[i] == ' ') {
            // 공백 무시
            continue;
        }
        else {
            // 공백, 연산자, 괄호를 제외한 값은 push 해줌.
            infix_str.push_back(input[i]);
        }
    }

    // infix에 데이터 삽입
    while (1) {
        if (infix_str.empty() == 1) {
            break;
        }
        // string 추가
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
            // 연산자 표시
            postfix += token + BLANK;
        }
        else if (token.size() == 1 && isblank(token[0])) {
            // 공백 무시
            continue;
        }
        else if (token == "(") {
            // 왼쪽 괄호: 연산자 스택에 푸시
            operator_stack.push_back('(');
        }
        else if (token == ")") {
            // 오른쪽 괄호: 연산자 스택에서 왼쪽 괄호를 만날 때까지 연산자를 출력
            while (!operator_stack.empty() && operator_stack.back() != '(') {
                postfix += operator_stack.back();
                operator_stack.pop_back();
                postfix += BLANK;
            }
            if (!operator_stack.empty() && operator_stack.back() == '(') {
                operator_stack.pop_back(); // 왼쪽 괄호를 팝
            }
        }
        else if (token.size() >= 2 && token[0] == '-' && isdigit(token[1])) {
            // 음수
            postfix += token + BLANK;
        }
        else {
            // 연산자
            char op = token[0];
            while (!operator_stack.empty() && operator_stack.back() != '(' && get_operator_precedence(operator_stack.back()) >= get_operator_precedence(op)) {
                // 스택에서 우선순위가 높거나 같은 연산자를 팝하여 출력
                postfix += operator_stack.back();
                operator_stack.pop_back();
                postfix += BLANK;
            }
            // 현재 연산자를 스택에 푸시
            operator_stack.push_back(op);
        }
    }

    // 스택에 남아있는 모든 연산자를 출력
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
    // 변수 이름 및 값 저장
    map<char, double> variable_values; 

    dequeue<double> value_stack;

    istringstream iss(s);
    string token;
    while (iss >> token) {
        if (isdigit(token[0]) || ((token[0] == '-' || token[0] == '.') && (isdigit(token[1]) || token[1] == '.'))) {
            // 숫자, 음수 숫자, 또는 변수인 경우 스택에 푸시
            value_stack.push_back(stod(token));
        }
        else if (isalpha(token[0]) && token.size() == 1) {
            char variable = token[0];
            double value;

            if (variable_values.find(variable) == variable_values.end()) {
                // 변수 값이 알려지지 않은 경우 사용자로부터 입력 받음
                cout << "Enter " << variable << ": ";
                cin >> value;
                // 엔터 문자를 제거
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                variable_values[variable] = value;
            }
            else {
                value = variable_values[variable];
            }

            // 변수 값을 스택에 푸시
            value_stack.push_back(value);
        }
        else if (token.size() == 1 && isblank(token[0])) { // 공백은 무시
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
                    cerr << "Error (0으로 나눔)" << endl;
                    return 0.0; // 에러 처리
                }
                result = operand1 / operand2;
                break;
            default:
                cerr << "Error (알수 없는 연산자)" << endl;
                return 0.0; // 에러 처리
            }
            value_stack.push_back(result);
        }
    }

    cout << "Result : " << value_stack.front() << endl << endl;
    return value_stack.front();
}


#endif