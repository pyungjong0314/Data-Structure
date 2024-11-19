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
		link_force = init_front_link;	// ���� ��带 ����Ű�� ������ �ʱ�ȭ
		link_back = init_back_link;		// ���� ��带 ����Ű�� ������ �ʱ�ȭ
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
    // �� ó������ ������ ������ �̵�
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->after_link())
        ++count;

    return count;
}

template <class Item>
dnode<Item>* list_search(dnode<Item>* head_ptr, const Item& target_data) {
    dnode<Item>* cursor;
    // �� ó������ ������ ������ �̵�
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->after_link()) {
        // �����Ͱ� ������ �����Ͱ� �ִ� ����� ������ ��ȯ
        if (cursor->data() == target_data) {
            return cursor;
        }
    }
    return NULL;
}
template <class Item>
const dnode<Item>* list_search(const dnode<Item>* head_ptr, const Item& target_data) {
    const dnode<Item>* cursor;
    // ó������ ������ ������ �̵�
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->after_link()) {
        if (cursor->data() == target_data) {
            // �����͸� ã���� ������ ��ȯ
            return cursor;
        }
    }
    // �����Ͱ� ������ NULL ��ȯ
    return NULL;
}

template <class Item>
dnode<Item>* list_locate(dnode<Item>* head_ptr, size_t location) {
    // location�� ��ȿ���� Ȯ��
    assert(0 < location);
    // ����� ���̺��� ������ Ȯ��
    assert(list_length(head_ptr) >= location);
    dnode<Item>* cursor = head_ptr;
    // �� ó������ ��ġ��ŭ �̵�
    for (size_t i = 1; (i < location) && (cursor != NULL); ++i) {
        cursor = cursor->after_link();
    }
    return cursor;
}

template <class Item>
void list_head_insert(dnode<Item>*& head_ptr, const Item& insert_data) {
    // ���ο� ���
    dnode<Item>* new_dnode = new dnode<Item>(insert_data, nullptr, head_ptr);
    // ��尡 �����ϸ� ���ο� ���� ����
    if (head_ptr != nullptr) {
        head_ptr->set_pre_link(new_dnode);
    }
    // head_ptr ����
    head_ptr = new_dnode;
}

template <class Item>
void list_insert(dnode<Item>* pre_ptr, const Item& insert_data) {
    // ���ο� ���
    dnode<Item>* new_node = new dnode<Item>(insert_data, pre_ptr, pre_ptr->after_link());
    // ���� ���� ���� ����
    pre_ptr->set_after_link(new_node);

    if (new_node->after_link() != nullptr) {
        // ���� ���� ���� ���� ��带 ����
        new_node->after_link()->set_pre_link(new_node);
    }
}


template <class Item>
void list_head_remove(dnode<Item>*& head_ptr) {
    dnode<Item>* remove_ptr = head_ptr;
    // head_ptr ����
    head_ptr = head_ptr->after_link();
    // ���� ����� ������ ����
    if (head_ptr != nullptr)
        head_ptr->set_pre_link(NULL);

    delete remove_ptr;
}

template <class Item>
void list_remove(dnode<Item>* pre_ptr) {
    if (pre_ptr->after_link() == NULL)
        return;
    // ������ ��� ������
    dnode<Item>* remove_ptr = pre_ptr->after_link();
    // ������ ����� �� ���� ������ ����� ���� ��� ����
    pre_ptr->set_after_link(remove_ptr->after_link());

    if (remove_ptr->after_link() != NULL) {
        // ������ ����� ��������� pre_ptr ����
        remove_ptr->after_link()->set_pre_link(pre_ptr);
    }
    delete remove_ptr;
}

template <class Item>
void list_clear(dnode<Item>*& head_ptr) {
    while (head_ptr != NULL) { // head_ptr���� ���������� ����
        list_head_remove(head_ptr);
    }
}

template <class Item>
void list_copy(const dnode<Item>* source_ptr, dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr) {
    head_ptr = NULL;
    tail_ptr = NULL;
    if (source_ptr == NULL) return;
    tail_ptr = head_ptr;
    // �� ó�� ��� ����
    list_head_insert(head_ptr, source_ptr->data());
    tail_ptr = head_ptr;
    // ������ ������ ����
    source_ptr = source_ptr->after_link();
    while (source_ptr != nullptr) {
        list_insert(tail_ptr, source_ptr->data());
        tail_ptr = tail_ptr->after_link();
        source_ptr = source_ptr->after_link();
    }
}
#endif