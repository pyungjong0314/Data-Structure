#include <iostream>
#include "evaluator.h"
#include <string>

int main() {
	evaluator convert;
	//���� infix �Է°��� string infix�� ����
	string infix = convert.read_expression();
	//�Է��� quit�̸� ���μ��� ����
	if (infix == "quit ") {
		exit(0);
	}
	else {
		//�Է� infix�� postfix�� ��ȯ
		string postfix = convert.convert_to_postfix(infix);
		//��ȯ�� postfix�� ���� ��� ����� ��ȯ
		convert.evaluate_postfix(postfix);
		//�ݺ�
		main();
	}

	return 0;
}