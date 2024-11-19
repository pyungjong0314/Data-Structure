#pragma once

#ifndef __DNODE_H__
#define __DNODE_H__

#include <cassert>
#include <cstdlib>
#include <iostream> 

using namespace std;

template <class Item>
class dnode {
public:
	dnode(const Item& init_data = Item(), dnode* init_front_link = NULL, dnode* init_back_link = NULL) {
		data_field = init_data;
		link_force = init_front_link;	// 다음 노드를 가르키는 포인터 초기화
		link_back = init_back_link;		// 이전 노드를 가르키는 포인터 초기화
	}
	void set_data(const Item& new_data) { data_field = new_data; }
	void set_pre_link(dnode* new_front_link) { link_force = new_front_link; }
	void set_after_link(dnode* new_back_link) { link_back = new_back_link; }
	Item data() const { return data_field; }
	dnode* pre_link() { return link_force; }
	const dnode* pre_link() const { return link_force; }
	dnode* after_link() { return link_back; }
	const dnode* after_link() const { return link_back; }

private:
	Item data_field;
	dnode* link_force;
	dnode* link_back;
};

template <class Item>
size_t list_length(const dnode<Item>* head_ptr) {
    size_t count = 0;
    const dnode<Item>* cursor;
    // 맨 처음부터 마지막 노드까지 이동
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->after_link())
        ++count;

    return count;
}

template <class Item>
dnode<Item>* list_search(dnode<Item>* head_ptr, const Item& target_data) {
    dnode<Item>* cursor;
    // 맨 처음부터 마지막 노드까지 이동
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->after_link()) {
        // 데이터가 있으면 데이터가 있는 노드의 포인터 반환
        if (cursor->data() == target_data) {
            return cursor;
        }
    }
    return NULL;
}
template <class Item>
const dnode<Item>* list_search(const dnode<Item>* head_ptr, const Item& target_data) {
    const dnode<Item>* cursor;
    // 처음부터 마지막 노드까지 이동
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->after_link()) {
        if (cursor->data() == target_data) {
            // 데이터를 찾으면 포인터 반환
            return cursor;
        }
    }
    // 데이터가 없으면 NULL 반환
    return NULL;
}

template <class Item>
dnode<Item>* list_locate(dnode<Item>* head_ptr, size_t location) {
    // location이 유효한지 확인
    assert(0 < location);
    // 노드의 길이보다 작은지 확인
    assert(list_length(head_ptr) >= location);
    dnode<Item>* cursor = head_ptr;
    // 맨 처음부터 위치만큼 이동
    for (size_t i = 1; (i < location) && (cursor != NULL); ++i) {
        cursor = cursor->after_link();
    }
    return cursor;
}

template <class Item>
void list_head_insert(dnode<Item>*& head_ptr, const Item& insert_data) {
    // 새로운 노드
    dnode<Item>* new_dnode = new dnode<Item>(insert_data, nullptr, head_ptr);
    // 노드가 존재하면 새로운 노드와 연결
    if (head_ptr != nullptr) {
        head_ptr->set_pre_link(new_dnode);
    }
    // head_ptr 변경
    head_ptr = new_dnode;
}

template <class Item>
void list_insert(dnode<Item>* pre_ptr, const Item& insert_data) {
    // 새로운 노드
    dnode<Item>* new_node = new dnode<Item>(insert_data, pre_ptr, pre_ptr->after_link());
    // 삽입 이전 노드와 연결
    pre_ptr->set_after_link(new_node);

    if (new_node->after_link() != nullptr) {
        // 삽입 다음 노드와 삽입 노드를 연결
        new_node->after_link()->set_pre_link(new_node);
    }
}


template <class Item>
void list_head_remove(dnode<Item>*& head_ptr) {
    dnode<Item>* remove_ptr = head_ptr;
    // head_ptr 변경
    head_ptr = head_ptr->after_link();
    // 이전 노드의 연결을 지움
    if (head_ptr != nullptr)
        head_ptr->set_pre_link(NULL);

    delete remove_ptr;
}

template <class Item>
void list_remove(dnode<Item>* pre_ptr) {
    if (pre_ptr->after_link() == NULL)
        return;
    // 삭제할 노드 포인터
    dnode<Item>* remove_ptr = pre_ptr->after_link();
    // 삭제할 노드의 전 노드와 삭제할 노드의 다음 노드 연결
    pre_ptr->set_after_link(remove_ptr->after_link());

    if (remove_ptr->after_link() != NULL) {
        // 삭제할 노드의 다음노드의 pre_ptr 연결
        remove_ptr->after_link()->set_pre_link(pre_ptr);
    }
    delete remove_ptr;
}

template <class Item>
void list_clear(dnode<Item>*& head_ptr) {
    while (head_ptr != NULL) { // head_ptr부터 마지막까지 지움
        list_head_remove(head_ptr);
    }
}

template <class Item>
void list_copy(const dnode<Item>* source_ptr, dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr) {
    head_ptr = NULL;
    tail_ptr = NULL;
    if (source_ptr == NULL) return;
    tail_ptr = head_ptr;
    // 맨 처음 노드 삽입
    list_head_insert(head_ptr, source_ptr->data());
    tail_ptr = head_ptr;
    // 마지막 노드까지 삽입
    source_ptr = source_ptr->after_link();
    while (source_ptr != nullptr) {
        list_insert(tail_ptr, source_ptr->data());
        tail_ptr = tail_ptr->after_link();
        source_ptr = source_ptr->after_link();
    }
}
#endif