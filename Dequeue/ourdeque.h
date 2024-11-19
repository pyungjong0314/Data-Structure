#pragma once

#ifndef __OURDEQUE_H__
#define __OURDEQUE_H__

#include <cstdlib>
#include "dnode.h"

using namespace std;

template <class Item>
class dequeue {
public:
	dequeue();
	dequeue(const dequeue<Item>& source);
	~dequeue();
	void pop_front();
	void pop_back();
	void push_front(const Item& front_entry);
	void push_back(const Item& back_entry);
	void operator =(const dequeue<Item>& source);
	bool empty() const { return (count == 0); }
	Item front() const;
	Item back() const;
	size_t size() const { return count; }
	// ������ ���� ���� Ȯ��
	bool exist(const Item& target);

private:
	dnode<Item>* front_ptr;
	dnode<Item>* back_ptr;
	size_t count;
};

template <class Item>
dequeue<Item>::dequeue() {
	count = 0;
	front_ptr = NULL;
	back_ptr = NULL;
}

template <class Item>
dequeue<Item>::dequeue(const dequeue<Item>& source) {
	count = source.count;
	list_copy(source.front_ptr, front_ptr, back_ptr);
}

template <class Item>
dequeue<Item>::~dequeue() {
	list_clear(front_ptr);
}

template <class Item>
void dequeue<Item>::pop_front() { // dequeue�� ó�� ����
	assert(!empty());
	list_head_remove(front_ptr);
	--count;
}

template <class Item>
void dequeue<Item>::pop_back() { // dequeue�� ������ ����
	assert(!empty());
	if (count == 1) { // �����Ͱ� 1�� ���� ��� front_ptr, back_ptr�� NULL
		list_head_remove(front_ptr);
		back_ptr = nullptr;
	}
	else {
		// �� �� �ٷ� �� ���
		dnode<Item>* pre_back_ptr = back_ptr->pre_link();
		// �� �� ��� ����
		list_remove(pre_back_ptr);
		// �� �� ��� ����
		back_ptr = pre_back_ptr;
	}
	--count;
}

template <class Item>
void dequeue<Item>::push_front(const Item& front_entry) { // dequeue�� ó���� ����
	list_head_insert(front_ptr, front_entry);
	if (empty()) { // ó�� ������ ����
		back_ptr = front_ptr;
	}
	++count;
}

template <class Item>
void dequeue<Item>::push_back(const Item& back_entry) { // dequeue�� �������� ����
	if (empty()) { // ó�� ������ ����
		list_head_insert(front_ptr, back_entry);
		back_ptr = front_ptr;
	}
	else { 
		list_insert(back_ptr, back_entry);
		back_ptr = back_ptr->after_link(); // back_ptr�� ���ο� �����ͷ� ����
	}
	++count;
}

template <class Item>
Item dequeue<Item>::front() const {
	assert(!empty());
	return front_ptr->data();
}

template <class Item>
Item dequeue<Item>::back() const {
	assert(!empty());
	return back_ptr->data();
}

template <class Item>
void dequeue<Item>::operator =(const dequeue<Item>& source) {
	if (this == &source)
		return;
	list_clear(front_ptr);
	list_copy(source.front_ptr, front_ptr, back_ptr);
	count = source.count;
}

template <class Item>
bool dequeue<Item>::exist(const Item& target) {
	if (list_search(front_ptr, target) != NULL) {
		return true;
	}
	else {
		return false;
	}
}
#endif

