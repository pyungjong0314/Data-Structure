#include "dnode.h"
#include <cassert>

using namespace std;

size_t list_length(const dnode* head_ptr) {
    size_t count = 0;
    const dnode* cursor;
    // 맨 처음부터 마지막 노드까지 이동
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->after_link())
        ++count;

    return count;
}

dnode* list_search(dnode* head_ptr, const dnode::value_type& target_data) {
    dnode* cursor;
    // 맨 처음부터 마지막 노드까지 이동
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->after_link()) {
        // 데이터가 있으면 데이터가 있는 노드의 포인터 반환
        if (cursor->data() == target_data) {
            return cursor;
        }
    }
    return NULL;
}
const dnode* list_search(const dnode* head_ptr, const dnode::value_type& target_data) {
    const dnode* cursor;
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->after_link()) {
        if (cursor->data() == target_data) {
            return cursor;
        }
    }
    return NULL;
}

dnode* list_locate(dnode* head_ptr, size_t location) {
    // location이 유효한지 확인
    assert(0 < location);
    // 노드의 길이보다 작은지 확인
    assert(list_length(head_ptr) >= location);
    dnode* cursor = head_ptr;
    // 맨 처음부터 위치만큼 이동
    for (size_t i = 1; (i < location) && (cursor != NULL); ++i) {
        cursor = cursor->after_link();
    }
    return cursor;
}

dnode* find_head_ptr(dnode* ptr) {
    if (ptr == NULL)
        return NULL;

    // 노드를 현재 위치에서 맨 앞으로 이동
    dnode* cursor = ptr;
    while (cursor->pre_link() != NULL) {
        cursor = cursor->pre_link();
    }
    // head_ptr 반환
    return cursor;
}

bool list_head_insert(dnode*& head_ptr, const dnode::value_type& insert_data) {
    // ourset에 중복된 데이터 확인
    if (list_search(head_ptr, insert_data) != nullptr) {
        return false;
    }
    dnode* new_dnode = new dnode(insert_data, nullptr, head_ptr);
    if (head_ptr != nullptr) { // 노드가 존재하면 link_force 연결
        head_ptr->set_pre_link(new_dnode);
    }
    head_ptr = new_dnode;

    return true;
}

bool list_insert(dnode* pre_ptr, const dnode::value_type& insert_data) {
    if (pre_ptr == nullptr)
        return false;
    // head_ptr을 찾아서 insert_data 존재 확인
    dnode* find_head = find_head_ptr(pre_ptr);
    if (list_search(find_head, insert_data) != NULL)
        return false;
    // 노드 연결
    dnode* new_node = new dnode(insert_data, pre_ptr, pre_ptr->after_link());
    if (pre_ptr->after_link() != nullptr) { // 맨 마지막 노드 확인
        pre_ptr->after_link()->set_pre_link(new_node);
    }
    pre_ptr->set_after_link(new_node);
    return true;
}


void list_head_remove(dnode*& head_ptr) {
    dnode* remove_ptr = head_ptr;
    head_ptr = head_ptr->after_link();
    // 이전 노드의 연결을 지움
    if (head_ptr != nullptr)
        head_ptr->set_pre_link(NULL);

    delete remove_ptr;
}

void list_remove(dnode* pre_ptr) {
    if (pre_ptr->after_link() == NULL)
        return;
    // 삭제할 노드 포인터
    dnode* remove_ptr = pre_ptr->after_link();
    // 노드 연결 변경
    pre_ptr->set_after_link(remove_ptr->after_link());

    if (remove_ptr->after_link() != NULL) {
        remove_ptr->after_link()->set_pre_link(pre_ptr);
    }
    delete remove_ptr;
}

void list_clear(dnode*& head_ptr) {
    while (head_ptr != NULL) { // head_ptr부터 마지막까지 지움
        list_head_remove(head_ptr);
    }
}

void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr) {
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