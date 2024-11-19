#include <iostream>
#include "evaluator.h"
#include <string>

int main() {
	evaluator convert;
	//유저 infix 입력값을 string infix에 저장
	string infix = convert.read_expression();
	//입력이 quit이면 프로세스 종료
	if (infix == "quit ") {
		exit(0);
	}
	else {
		//입력 infix를 postfix로 변환
		string postfix = convert.convert_to_postfix(infix);
		//변환된 postfix를 통해 계산 결과값 반환
		convert.evaluate_postfix(postfix);
		//반복
		main();
	}

	return 0;
}