#pragma once

#ifndef __DNODE_H__
#define __DNODE_H__

#include <cstdlib>
using namespace std;

class dnode {
public:
	typedef double value_type;
	dnode(const value_type& init_data = value_type(), dnode* init_front_link = NULL, dnode* init_back_link = NULL) {
		data_field = init_data;
		link_force = init_front_link;	// 다음 노드를 가르키는 포인터 초기화
		link_back = init_back_link;		// 이전 노드를 가르키는 포인터 초기화
	}
	void set_data(const value_type& new_data) { data_field = new_data; }
	void set_pre_link(dnode* new_front_link) { link_force = new_front_link; }
	void set_after_link(dnode* new_back_link) { link_back = new_back_link; }
	value_type data() const { return data_field; }
	dnode* pre_link() { return link_force; }
	const dnode* pre_link() const { return link_force; }
	dnode* after_link() { return link_back; }
	const dnode* after_link() const { return link_back; }

private:
	value_type data_field;
	dnode* link_force;
	dnode* link_back;
};

size_t list_length(const dnode* head_ptr);

dnode* list_search(dnode* head_ptr, const dnode::value_type& target_data);
const dnode* list_search(const dnode* head_ptr, const dnode::value_type& target_data);

dnode* list_locate(dnode* head_ptr, size_t location);

dnode* find_head_ptr(dnode* ptr);

bool list_head_insert(dnode*& head_ptr, const dnode::value_type& insert_data);

bool list_insert(dnode* pre_ptr, const dnode::value_type& insert_data);

void list_head_remove(dnode*& head_ptr);

void list_remove(dnode* pre_ptr);

void list_clear(dnode*& head_ptr);

void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr);

#endif