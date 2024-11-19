#include <iostream>
#include "ourset_doubly_linked_list.h"

using namespace std;

int main() {

    cout << "OURSET1�� �� ���ڵ��� �Է�<���� �Է��ϸ� �ߴ�> (insert�Լ� ���)\n";
    ourset ourset1;
    ourset::value_type user_input;
    cout << "Input : ";
    cin >> user_input;
    while (user_input >= 0) {

        ourset1.insert(user_input);
        cout << "OURSET1 : ";
        ourset1.show_contents();
        cout << "Input : ";
        cin >> user_input;
    }
    cout << "OURSET1 : ";
    ourset1.show_contents();
    cout << "\n---------------------------------------------------------\n";

    cout << "OURSET2�� �� ���ڵ��� �Է�<���� �Է��ϸ� �ߴ�> \n";
    ourset ourset2;
    ourset::value_type user_input2;
    cout << "Input : ";
    cin >> user_input2;
    while (user_input2 >= 0) {

        ourset2.insert(user_input2);
        cout << "OURSET2 : ";
        ourset2.show_contents();
        cout << "Input : ";
        cin >> user_input2;
    }
    cout << "OURSET2 : ";
    ourset2.show_contents();

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET1 : ";
    ourset1.show_contents();
    cout << "OURSET2 : ";
    ourset2.show_contents();
    cout << "ourset1 == ourset2\n";
    cout << "������ 1 / �ٸ��� 0 : ";
    cout << ourset1.operator==(ourset2) << "\n";

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET1 : ";
    ourset1.show_contents();
    cout << "OURSET2 : ";
    ourset2.show_contents();
    cout << "ourset1 != ourset2\n";
    cout << "������ 0 / �ٸ��� 1 : ";
    cout << ourset1.operator!=(ourset2) << "\n";

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET1 : ";
    ourset1.show_contents();
    cout << "constructorȣ�� ourset3���� / copy constructor ȣ�� ourset4�� ourset1���� ����\n";
    ourset* ourset3 = new ourset();
    ourset* ourset4 = new ourset(ourset1);
    cout << "OURSET3 : ";
    ourset3->show_contents();
    cout << "OURSET4 : ";
    ourset4->show_contents();

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET1 : ";
    ourset1.show_contents();
    cout << "OURSET3 : ";
    ourset3->show_contents();
    cout << "ourset3 = ourset1\n";
    cout << "OURSET1 : ";
    ourset1.show_contents();
    cout << "OURSET3 : ";
    ourset3->operator=(ourset1);
    ourset3->show_contents();

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET2 : ";
    ourset2.show_contents();
    cout << "OURSET3 : ";
    ourset3->show_contents();
    cout << "ourset3 += ourset2\n";
    ourset3->operator+=(ourset2);
    cout << "OURSET2 : ";
    ourset2.show_contents();
    cout << "OURSET3 : ";
    ourset3->show_contents();

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET1 : ";
    ourset1.show_contents();
    cout << "OURSET2 : ";
    ourset2.show_contents();
    cout << "ourset5 = ourset1 + ourset2\n";
    ourset ourset5;
    ourset5 = operator+(ourset1, ourset2);
    cout << "OURSET1 : ";
    ourset1.show_contents();
    cout << "OURSET2 : ";
    ourset2.show_contents();
    cout << "OURSET5 : ";
    ourset5.show_contents();

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET5 : ";
    ourset5.show_contents();
    cout << "grab ȣ�� ourset5<����>\n";
    ourset::value_type random_data = ourset1.grab();
    cout << "Random Data : " << random_data << "\n";

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET5 : ";
    ourset5.show_contents();
    cout << "count ȣ�� �������� ���� ���� ���� ī��Ʈ\n";
    cout << "Random Data " << random_data << " : ";
    cout << ourset5.count(random_data) << "��" << "\n";

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET5 : ";
    ourset5.show_contents();
    cout << "erase_one ȣ�� �������� ����" << random_data << "����\n";
    ourset5.erase_one(random_data);
    cout << "OURSET5 : ";
    ourset5.show_contents();

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET5 : ";
    ourset5.show_contents();
    cout << "sort ȣ���ؼ� bag5 ����\n";
    ourset5.sort();
    cout << "OURSET5 : ";
    ourset5.show_contents();

    return 0;
}
