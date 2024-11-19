#include <iostream>
#include "ourset_doubly_linked_list.h"

using namespace std;

int main() {

    cout << "OURSET1에 들어갈 숫자들을 입력<음수 입력하면 중단> (insert함수 사용)\n";
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

    cout << "OURSET2에 들어갈 숫자들을 입력<음수 입력하면 중단> \n";
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
    cout << "같으면 1 / 다르면 0 : ";
    cout << ourset1.operator==(ourset2) << "\n";

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET1 : ";
    ourset1.show_contents();
    cout << "OURSET2 : ";
    ourset2.show_contents();
    cout << "ourset1 != ourset2\n";
    cout << "같으면 0 / 다르면 1 : ";
    cout << ourset1.operator!=(ourset2) << "\n";

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET1 : ";
    ourset1.show_contents();
    cout << "constructor호출 ourset3생성 / copy constructor 호출 ourset4에 ourset1내용 대입\n";
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
    cout << "grab 호출 ourset5<랜덤>\n";
    ourset::value_type random_data = ourset1.grab();
    cout << "Random Data : " << random_data << "\n";

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET5 : ";
    ourset5.show_contents();
    cout << "count 호출 랜덤으로 뽑은 내용 갯수 카운트\n";
    cout << "Random Data " << random_data << " : ";
    cout << ourset5.count(random_data) << "개" << "\n";

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET5 : ";
    ourset5.show_contents();
    cout << "erase_one 호출 랜덤으로 뽑은" << random_data << "삭제\n";
    ourset5.erase_one(random_data);
    cout << "OURSET5 : ";
    ourset5.show_contents();

    cout << "\n---------------------------------------------------------\n";
    cout << "OURSET5 : ";
    ourset5.show_contents();
    cout << "sort 호출해서 bag5 정렬\n";
    ourset5.sort();
    cout << "OURSET5 : ";
    ourset5.show_contents();

    return 0;
}
