#include "dnode.h" 
#include "ourset_doubly_linked_list.h"
#include <cstdlib> 
#include <cassert>

#include <iostream> 

using namespace std;

ourset::ourset() {
    head_ptr = NULL;
    tail_ptr = NULL;
    many_nodes = 0;
}

ourset::ourset(const ourset& source) {
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    many_nodes = source.many_nodes;
}

ourset::~ourset() {
    list_clear(head_ptr);
    many_nodes = 0;
}

void ourset::operator = (const ourset& source) {
    if (this == &source)
        return;
    // ourset 초기화
    list_clear(head_ptr);
    // source copy
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    many_nodes = source.many_nodes;
}

void ourset::operator+=(const ourset& addend) {
    dnode* copy_ptr = addend.head_ptr;
    if (head_ptr == nullptr) {
        head_ptr = copy_ptr;
    }
    // addend 처음부터 마지막 노드까지 반복
    while (copy_ptr != nullptr) {
        // 데이터 삽입
        bool insert = list_insert(tail_ptr, copy_ptr->data());
        if (insert) { // 데이터 존재 유무
            ++many_nodes;
        }
        copy_ptr = copy_ptr->after_link();
    }
}


bool ourset::operator == (const ourset& right) {
    // 노드 개수 확인
    if (many_nodes != right.many_nodes) {
        return false;
    }

    dnode* exist;
    dnode* target_ptr = head_ptr;
    // 처음부터 마지막 노드까지 반복
    while (target_ptr != NULL) {
        // 데이터 존재 확인
        value_type target_data = target_ptr->data();
        exist = list_search(right.head_ptr, target_data);
        if (exist == NULL) {
            return false;
        }
        target_ptr = target_ptr->after_link();
    }
    return true;
}

bool ourset::operator != (const ourset& right) {
    if (many_nodes != right.many_nodes) {
        return true;
    }

    dnode* exist;
    dnode* target_ptr = head_ptr;
    while (target_ptr != NULL) {
        value_type target_data = target_ptr->data();
        exist = list_search(right.head_ptr, target_data);
        if (exist == NULL) {
            return true;
        }
        target_ptr = target_ptr->after_link();
    }
    return false;
}

bool ourset::erase_one(const value_type& target) {
    // 목표 데이터 노드 확인
    dnode* target_ptr = list_search(head_ptr, target);
    if (target_ptr == NULL)
        return false;
    // 목표 데이터를 맨 앞으로 이동하고 삭제
    target_ptr->set_data(head_ptr->data());
    list_head_remove(head_ptr);

    --many_nodes;
    return true;
}

ourset::size_type ourset::count(const value_type& target) const {
    const dnode* cursor;
    // 데이터가 존재하면 1, 없으면 0 (ourset)
    cursor = list_search(head_ptr, target);
    if (cursor != NULL)
        return 1;
    return 0;
}

ourset::value_type ourset::grab() {
    size_type i;
    const dnode* cursor;

    assert(size() > 0);
    i = (rand() % size()) + 1;
    // 랜덤한 위치에 있는 데이터
    cursor = list_locate(head_ptr, i);
    return cursor->data();
}

void ourset::insert(const value_type& insert_data) {
    // 노드의 맨 처음에 데이터 삽입
    list_head_insert(head_ptr, insert_data);
    ++many_nodes;
}

void ourset::show_contents() {
    dnode* cursor;
    if (head_ptr == nullptr) {
        cout << "\n";
        return;
    }
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->after_link()) {
        cout << cursor->data() << " ";
    }
    cout << "\n";
}

ourset operator+(const ourset& set1, const ourset& set2) {
    ourset result;
    // 집합 1 복사
    result = set1;
    // 집합 2 삽입
    result += set2;
    return result;
}


void ourset::sort() {
    ourset ourset_temp;

    while (list_length(head_ptr) > 0) {
        value_type temp = head_ptr->data();
        // 가장 작은 데이터부터 한 개씩 지워가며 찾는다.
        for (dnode* cursor = head_ptr->after_link(); cursor != NULL; cursor = cursor->after_link()) {
            if (cursor->data() < temp) { // 데이터 최솟값
                temp = cursor->data();
            }
        }
        // 가장 작은 수부터 temp set에 넣는다.
        this->erase_one(temp);
        ourset_temp.insert(temp);
    }
    // 가장 큰 수부터 set에 다시 넣어준다.
    for (dnode* cursor = ourset_temp.head_ptr; cursor != NULL; cursor = cursor->after_link()) {
        this->insert(cursor->data());
    }
    return;
}