#ifndef B_TREE_H
#define B_TREE_H

#include <iostream>
#include <iomanip>

template <class Item>
class bTree {
public:
    bTree();
    ~bTree();
    void clear();
    bool empty() {
        // 데이터가 없고 subbag도 없으면 true(1)
        return ((data_count == 0) && (child_count == 0));
    }
    bool insert(const Item& entry);
    bool erase_one(const Item& target);
    size_t count(const Item& target);

    void show_contents(size_t d);   // bTree 결과 출력

private:
    static const size_t MINIMUM = 1;
    static const size_t MAXIMUM = 2 * MINIMUM;
    size_t data_count;
    Item data[MAXIMUM + 1];
    size_t child_count;
    bTree* subbag[MAXIMUM + 2];
    bool is_leaf() { return (child_count == 0); }
    // insert
    bool loose_insert(const Item& entry);
    void fix_excess(size_t index);

    // erase
    bool loose_erase(const Item& target);
    void fix_shortage(size_t index);
    void remove_biggest(Item& removed_entry);
};

template <class Item>
bTree<Item>::bTree() { // 데이터와 subbag이 없는 bTree 생성
    data_count = 0;
    child_count = 0;
}

// 전체 bTree 삭제
template <class Item>
bTree<Item>::~bTree() {
    if (is_leaf()) { //data, child 삭제
        data_count = 0;
        child_count = 0;
    }
    else { // subbag 삭제
        for (size_t i = 0; i < child_count; i++) {
            subbag[i]->clear();
        }
    }
}

// subbag 모두 삭제
template <class Item>
void bTree<Item>::clear() { // subbag 삭제
    for (size_t i = 0; i < child_count; ++i) {
        delete subbag[i];
    }
    child_count = 0;
    data_count = 0;
}


// target 수는 subbag에서 target 수 + data에서 target수
template <class Item>
size_t bTree<Item>::count(const Item& target) {
    size_t count = 0;
    if (is_leaf()) { // subbag이 없으면 data만 확인
        for (size_t i = 0; i < data_count; i++) {
            if (target == data[i]) {
                count++;
            }
        }
    }
    else { // subbag 존재하면 subbag 확인 -> data 확인
        for (size_t i = 0; i < data_count; i++) {
            count += subbag[i]->count(target);
            if (data[i] == target) {
                count++;
            }
        }
        // 가장 오른쪽 subbag 확인
        count += subbag[child_count - 1]->count(target);
    }

    return count;
}

template <class Item>
void bTree<Item>::show_contents(size_t d) {
    // Backward In - Order Traversal 사용
    // subbag이 없으면 가장 큰 데이터부터 출력
    // subbag은 root 아래에 표현하기 위해서 변수 d를 사용하여 공백
    if (data_count == 0) {
        std::cout << "EMPTY" << std::endl;
    }
    else {
        // leaf subtree이면 데이터 값 출력
        if (is_leaf()) {
            for (size_t i = data_count; i > 0; i--) {
                std::cout << std::setw(4 * d) << data[i - 1] << std::endl;
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else { // subbag이 있으면 가장 큰 subbag부터 출력
            for (size_t i = data_count; i > 0; i--) {
                // subbag 출력 -> 데이터 출력 반복
                subbag[i]->show_contents(d + 1);
                std::cout << std::setw(4 * d) << data[i - 1] << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
            }
            subbag[0]->show_contents(d + 1);
        }
    }
}

template <class Item>
bool bTree<Item>::loose_insert(const Item& entry) {
    // 데이터보다 큰 index 찾기 (데이터가 삽입될 공간)
    size_t index = 0;
    while ((index < data_count) && (data[index] < entry)) {
        index++;
    }
    // leaf bTree에 데이터 삽입
    if (is_leaf()) {
        // 데이터가 삽입될 공간을 만들기 위해서 1칸 뒤로 이동
        for (size_t i = data_count; i > index; i--) {
            data[i] = data[i - 1];
        }
        // 데이터 삽입
        data[index] = entry;
        data_count++;
        return true;
    }
    else {
        // subbag이 있으면 entry가 들어갈 subbag[index] 이동
        subbag[index]->loose_insert(entry);
        if (subbag[index]->data_count > MAXIMUM) {
            fix_excess(index);
        }
        return true;
    }
}

template <class Item>
void bTree<Item>::fix_excess(size_t index) {
    // parent 데이터 삽입(subbag[index] 가운데 데이터)
    for (size_t i = data_count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = subbag[index]->data[MINIMUM];
    data_count++;

    // parent subbag 2개로 분할
    // subbag 삽입하기 위해 한칸 이동
    for (size_t i = child_count; i > index; i--) {
        subbag[i] = subbag[i - 1];
    }

    // 새로운 subbag 생성
    bTree<Item>* new_subbag = new bTree();
    // subbag에 데이터 절반 할당
    for (size_t i = 0; i < MINIMUM; i++) {
        new_subbag->data[i] = subbag[index]->data[MINIMUM + 1 + i];
    }
    // data_count 설정
    new_subbag->data_count = MINIMUM;
    subbag[index]->data_count = MINIMUM;


    //subbag[index]->subbag 절반 할당
    // child_count 설정
    if (!subbag[index]->is_leaf()) {
        for (size_t i = 0; i < MINIMUM + 1; i++) {
            new_subbag->subbag[i] = subbag[index]->subbag[MINIMUM + 1 + i];
        }
        new_subbag->child_count = MINIMUM + 1;
        subbag[index]->child_count = MINIMUM + 1;
    }

    // subbag 연결
    subbag[index + 1] = new_subbag;
    child_count++;
}

template <class Item>
bool bTree<Item>::insert(const Item& entry) {
    loose_insert(entry);

    // root 데이터가 더 많은 경우
    if (data_count > MAXIMUM) {
        // 새로운 루트 생성
        bTree<Item>* new_root = new bTree();
        // 새로운 subbag 생성
        bTree<Item>* new_subbag = new bTree();
        for (size_t i = 0; i < data_count; i++) {
            new_subbag->data[i] = data[i];
            new_subbag->subbag[i] = subbag[i];
        }
        new_subbag->subbag[child_count - 1] = subbag[child_count - 1];
        new_subbag->data_count = data_count;
        new_subbag->child_count = child_count;

        // 왼쪽 자식 설정
        new_root->subbag[0] = new_subbag;
        new_root->child_count = 1;

        new_root->fix_excess(0);
        // 새로운 tree의 root
        *this = *new_root;
    }

    return true;
}



template <class Item>
bool bTree<Item>::loose_erase(const Item& target) {
    size_t index = 0;
    // target보다 크거나 같은 첫번째 인덱스
    while ((index < data_count) && (data[index] < target)) {
        index++;
    }
    // subbag 없고 target이 없으면 실패
    if (is_leaf() && (data[index] != target)) {
        return false;
    }
    // subbag 없고 target이 있으면 삭제 
    else if (is_leaf() && (data[index] == target)) {
        for (size_t i = index; i < data_count - 1; i++) {
            data[i] = data[i + 1];
        }
        data_count--;
        return true;
    }
    // subbag이 존재하고 target이 없으면 subbag[index] 조사
    else if(!is_leaf() && (data[index] != target)) {
        bool b =subbag[index]->loose_erase(target);
        if (!b) { // subbag에 target이 존재하지 않는다면 실패
            return false;
        }
        // subbag[index] target을 삭제하고 MINIMUM 규칙을 만족하지 않는다
        if (subbag[index]->data_count < MINIMUM) {
            fix_shortage(index);
        }
        return true;
    }
    // subbag이 존재하고 target이 있으면
    else { // subbag[index]에서 가장 큰 데이터를 target 대신하여 삽입
        subbag[index]->remove_biggest(data[index]);
        if (subbag[index]->data_count < MINIMUM) {
            fix_shortage(index);
        }
        return true;
    }
}

template <class Item>
void bTree<Item>::remove_biggest(Item& removed_entry) {
    if (is_leaf()) { // subbag이 없다
        // 가장 큰 데이터를 removed_entry에 대입하고 삭제
        removed_entry = data[data_count - 1];
        data_count--;
    }
    else { //subbag이 있으면 가장 큰 subbag으로 이동
        subbag[child_count - 1]->remove_biggest(removed_entry);
        // subbag의 데이터가 MINIMUM보다 작을때
        if (subbag[child_count - 1]->data_count < MINIMUM) {
            fix_shortage(child_count - 1);
        }
    }
}

template <class Item>
// subbag[index]의 데이터가 부족한 경우
void bTree<Item>::fix_shortage(size_t index) {
    // subbag[index]가 MINIMUN-1, subbag[index-1]가 존재하며 data > MINIMUM인 경우
    if ((index > 0)&&(subbag[index - 1]->data_count > MINIMUM)) {
        // subbag[index]는 부모의 바로 작은 데이터를 받는다.
        for (size_t i = subbag[index]->data_count; i > 0; i--) {
            // subbag[index]의 데이터 한 칸 이동
            subbag[index]->data[i] = subbag[index]->data[i - 1];
        }
        subbag[index]->data[0] = data[index - 1];
        subbag[index]->data_count++;
        // subbag[index - 1]의 큰 데이터를 부모에게 준다.
        data[index - 1] = subbag[index - 1]->data[subbag[index - 1]->data_count - 1];
        subbag[index - 1]->data_count--;

        
        // subbag[index]가 subbag을 가지고 있다면 이동
        if (!subbag[index]->is_leaf()) {
            // subbag[index]의 subbag을 한 칸 이동
            for (size_t i = subbag[index]->child_count; i > 0; i--) {
                subbag[index]->subbag[i] = subbag[index]->subbag[i - 1];
            }
            subbag[index]->subbag[0] = subbag[index - 1]->subbag[subbag[index - 1]->child_count - 1];
            subbag[index]->child_count++;
            subbag[index - 1]->child_count--;
        }
    }
    // subbag[index]가 MINIMUN-1, subbag[index+1]이 존재하며 data > MINIMUM인 경우
    else if ((index < child_count - 1) && (subbag[index + 1]->data_count > MINIMUM)) {
        // subbag[index]는 부모의 가장 작은 데이터를 받는다.
        subbag[index]->data[subbag[index]->data_count] = data[index];
        subbag[index]->data_count++;
        // 부모의 데이터에게 subbag[index+1] 가장 작은 값을 준다
        data[index] = subbag[index + 1]->data[0];
        // subbag[index+1] 한 칸 이동
        for (size_t i = 0; i < subbag[index + 1]->data_count - 1; i++) {
            subbag[index + 1]->data[i] = subbag[index + 1]->data[i + 1];
        }
        subbag[index + 1]->data_count--;
        
        
        // subbag[index]가 subbag을 가지고 있다면 이동
        if (!subbag[index]->is_leaf()) {

            // subbag[index+1] 가장 작은 subbag을 subbag[index]의 가장 큰 subbag으로 이동
            subbag[index]->subbag[subbag[index]->child_count] = subbag[index + 1]->subbag[0];
            //subbag[index + 1] 한 칸 이동
            for (size_t i = 0; i < subbag[index + 1]->child_count - 1; i++) {
                subbag[index + 1]->subbag[i] = subbag[index + 1]->subbag[i + 1];
            }
            subbag[index]->child_count++;
            subbag[index + 1]->child_count--;
        }
    }

    // subbag[i]가 MINIMUM - 1, subbag[index - 1]이 존재하며 data == MINIMUM인 경우
    else if ((index > 0) && (subbag[index - 1]->data_count == MINIMUM)) {
        // data[index - 1], subbag[index], subbag[index -1]을 subbag[index-1]에 합친다.
        // data를 subbag[index - 1] 이동
        subbag[index - 1]->data[subbag[index - 1]->data_count] = data[index - 1];
        for (size_t i = index; i < data_count; i++) { // 데이터 한칸 이동
            data[i - 1] = data[i];
        }
        data_count--;
        subbag[index - 1]->data_count++;
        // subbag[index]를 subbag[index - 1]이동
        for (size_t i = 0; i < subbag[index]->data_count; i++) {
            subbag[index - 1]->data[subbag[index - 1]->data_count + i] = subbag[index]->data[i];
        }
        subbag[index - 1]->data_count += subbag[index]->data_count;

        //subbag[index]가 subbag을 가진 경우
        if (!subbag[index]->is_leaf()) {
            // subbag[index]의 subbag을 subbag[index -1]로 이동
            for (size_t i = 0; i < subbag[index]->child_count; i++) {
                subbag[index - 1]->subbag[subbag[index - 1]->child_count + i] = subbag[index]->subbag[i];
            }
            subbag[index - 1]->child_count += subbag[index]->child_count;
        }

        //data의 subbag을 index부터 한칸 앞으로 이동
        for (size_t i = index; i < child_count - 1; i++) {
            subbag[i] = subbag[i + 1];
        }
        child_count--; 

    }
    // subbag[i]가 MINIMUM - 1, subbag[index + 1]이 존재하며 data == MINIMUM인 경우
    else if ((index < child_count - 1) && (subbag[index + 1]->data_count == MINIMUM)) {
        // data[index], subbag[index], subbag[index + 1]을 subbag[index]에 합친다.
        // data를 subbag[index - 1] 이동
        subbag[index]->data[subbag[index]->data_count] = data[index];
        for (size_t i = index; i < data_count - 1; i++) {   // 데이터 한 칸 이동
            data[i] = data[i + 1];
        }
        data_count--;
        subbag[index]->data_count++;
        // subbag[index + 1]을 subbag[index]로 이동
        for (size_t i = 0; i < subbag[index + 1]->data_count; i++) {
            subbag[index]->data[subbag[index]->data_count + i] = subbag[index + 1]->data[i];
        }
        subbag[index]->data_count += subbag[index + 1]->data_count;

        //subbag[index]가 subbag을 가진 경우
        if (!subbag[index]->is_leaf()) {
            // subbag[index + 1]의 subbag을 subbag[index]로 이동
            for (size_t i = 0; i < subbag[index + 1]->child_count; i++) {
                subbag[index]->subbag[subbag[index]->child_count + i] = subbag[index + 1]->subbag[i];
            }
            subbag[index]->child_count += subbag[index + 1]->child_count;
        }

        //data subbag을 index + 1부터 한칸 앞으로 이동
        for (size_t i = index + 1; i < child_count - 1; i++) {
            subbag[i] = subbag[i + 1];
        }
        child_count--;
    }
    else { // error
        std::cout << "shortage error" << std::endl;
    }
}

template <class Item>
bool bTree<Item>::erase_one(const Item& target) {
    if (!loose_erase(target)) {
        return false;
    }
    // 새로운 root 설정
    if ((this->data_count == 0) && (this->child_count == 1)) {
        *this = *subbag[0];
    }

    return true;
}
#endif