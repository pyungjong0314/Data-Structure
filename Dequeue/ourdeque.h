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
	// 데이터 존재 유무 확인
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
void dequeue<Item>::pop_front() { // dequeue의 처음 제거
	assert(!empty());
	list_head_remove(front_ptr);
	--count;
}

template <class Item>
void dequeue<Item>::pop_back() { // dequeue의 마지막 제거
	assert(!empty());
	if (count == 1) { // 데이터가 1개 남은 경우 front_ptr, back_ptr이 NULL
		list_head_remove(front_ptr);
		back_ptr = nullptr;
	}
	else {
		// 맨 뒤 바로 앞 노드
		dnode<Item>* pre_back_ptr = back_ptr->pre_link();
		// 맨 뒤 노드 삭제
		list_remove(pre_back_ptr);
		// 맨 뒤 노드 변경
		back_ptr = pre_back_ptr;
	}
	--count;
}

template <class Item>
void dequeue<Item>::push_front(const Item& front_entry) { // dequeue의 처음에 연결
	list_head_insert(front_ptr, front_entry);
	if (empty()) { // 처음 데이터 삽입
		back_ptr = front_ptr;
	}
	++count;
}

template <class Item>
void dequeue<Item>::push_back(const Item& back_entry) { // dequeue의 마지막에 연결
	if (empty()) { // 처음 데이터 삽입
		list_head_insert(front_ptr, back_entry);
		back_ptr = front_ptr;
	}
	else { 
		list_insert(back_ptr, back_entry);
		back_ptr = back_ptr->after_link(); // back_ptr을 새로운 포인터로 변경
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

