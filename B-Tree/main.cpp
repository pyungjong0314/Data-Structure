#include <iostream>
#include "btree.hpp"

using namespace std;

int main() {
	// int�� �����͸� �����ϴ� bag���� btree
	bTree<int> btree;
	char buf[10] = { 0 };
	int num;
	size_t count;

;	while (strcmp(buf, "quit")) {
		cout << "B-Tree �Է�: ";
		cin >> buf;
		if (!strcmp(buf, "insert")) {
			cin >> num;
			btree.insert(num);
			cout << "===== <B-Tree> =====" << endl;
			btree.show_contents(0);
		}
		else if (!strcmp(buf, "erase")) {
			cin >> num;
			btree.erase_one(num);
			cout << "===== <B-Tree> =====" << endl;
			btree.show_contents(0);
		}
		else if (!strcmp(buf, "count")) {
			cin >> num;
			count = btree.count(num);
			cout << "COUNT " << num << ": " << count << endl;
			cout << endl;
		}
	}

	btree.clear();

	cout << "B-Tree clear" << endl;
	cout << "===== <B-Tree> =====" << endl;
	btree.show_contents(0);


	return 0;
}


