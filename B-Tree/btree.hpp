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
        // �����Ͱ� ���� subbag�� ������ true(1)
        return ((data_count == 0) && (child_count == 0));
    }
    bool insert(const Item& entry);
    bool erase_one(const Item& target);
    size_t count(const Item& target);

    void show_contents(size_t d);   // bTree ��� ���

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
bTree<Item>::bTree() { // �����Ϳ� subbag�� ���� bTree ����
    data_count = 0;
    child_count = 0;
}

// ��ü bTree ����
template <class Item>
bTree<Item>::~bTree() {
    if (is_leaf()) { //data, child ����
        data_count = 0;
        child_count = 0;
    }
    else { // subbag ����
        for (size_t i = 0; i < child_count; i++) {
            subbag[i]->clear();
        }
    }
}

// subbag ��� ����
template <class Item>
void bTree<Item>::clear() { // subbag ����
    for (size_t i = 0; i < child_count; ++i) {
        delete subbag[i];
    }
    child_count = 0;
    data_count = 0;
}


// target ���� subbag���� target �� + data���� target��
template <class Item>
size_t bTree<Item>::count(const Item& target) {
    size_t count = 0;
    if (is_leaf()) { // subbag�� ������ data�� Ȯ��
        for (size_t i = 0; i < data_count; i++) {
            if (target == data[i]) {
                count++;
            }
        }
    }
    else { // subbag �����ϸ� subbag Ȯ�� -> data Ȯ��
        for (size_t i = 0; i < data_count; i++) {
            count += subbag[i]->count(target);
            if (data[i] == target) {
                count++;
            }
        }
        // ���� ������ subbag Ȯ��
        count += subbag[child_count - 1]->count(target);
    }

    return count;
}

template <class Item>
void bTree<Item>::show_contents(size_t d) {
    // Backward In - Order Traversal ���
    // subbag�� ������ ���� ū �����ͺ��� ���
    // subbag�� root �Ʒ��� ǥ���ϱ� ���ؼ� ���� d�� ����Ͽ� ����
    if (data_count == 0) {
        std::cout << "EMPTY" << std::endl;
    }
    else {
        // leaf subtree�̸� ������ �� ���
        if (is_leaf()) {
            for (size_t i = data_count; i > 0; i--) {
                std::cout << std::setw(4 * d) << data[i - 1] << std::endl;
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else { // subbag�� ������ ���� ū subbag���� ���
            for (size_t i = data_count; i > 0; i--) {
                // subbag ��� -> ������ ��� �ݺ�
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
    // �����ͺ��� ū index ã�� (�����Ͱ� ���Ե� ����)
    size_t index = 0;
    while ((index < data_count) && (data[index] < entry)) {
        index++;
    }
    // leaf bTree�� ������ ����
    if (is_leaf()) {
        // �����Ͱ� ���Ե� ������ ����� ���ؼ� 1ĭ �ڷ� �̵�
        for (size_t i = data_count; i > index; i--) {
            data[i] = data[i - 1];
        }
        // ������ ����
        data[index] = entry;
        data_count++;
        return true;
    }
    else {
        // subbag�� ������ entry�� �� subbag[index] �̵�
        subbag[index]->loose_insert(entry);
        if (subbag[index]->data_count > MAXIMUM) {
            fix_excess(index);
        }
        return true;
    }
}

template <class Item>
void bTree<Item>::fix_excess(size_t index) {
    // parent ������ ����(subbag[index] ��� ������)
    for (size_t i = data_count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = subbag[index]->data[MINIMUM];
    data_count++;

    // parent subbag 2���� ����
    // subbag �����ϱ� ���� ��ĭ �̵�
    for (size_t i = child_count; i > index; i--) {
        subbag[i] = subbag[i - 1];
    }

    // ���ο� subbag ����
    bTree<Item>* new_subbag = new bTree();
    // subbag�� ������ ���� �Ҵ�
    for (size_t i = 0; i < MINIMUM; i++) {
        new_subbag->data[i] = subbag[index]->data[MINIMUM + 1 + i];
    }
    // data_count ����
    new_subbag->data_count = MINIMUM;
    subbag[index]->data_count = MINIMUM;


    //subbag[index]->subbag ���� �Ҵ�
    // child_count ����
    if (!subbag[index]->is_leaf()) {
        for (size_t i = 0; i < MINIMUM + 1; i++) {
            new_subbag->subbag[i] = subbag[index]->subbag[MINIMUM + 1 + i];
        }
        new_subbag->child_count = MINIMUM + 1;
        subbag[index]->child_count = MINIMUM + 1;
    }

    // subbag ����
    subbag[index + 1] = new_subbag;
    child_count++;
}

template <class Item>
bool bTree<Item>::insert(const Item& entry) {
    loose_insert(entry);

    // root �����Ͱ� �� ���� ���
    if (data_count > MAXIMUM) {
        // ���ο� ��Ʈ ����
        bTree<Item>* new_root = new bTree();
        // ���ο� subbag ����
        bTree<Item>* new_subbag = new bTree();
        for (size_t i = 0; i < data_count; i++) {
            new_subbag->data[i] = data[i];
            new_subbag->subbag[i] = subbag[i];
        }
        new_subbag->subbag[child_count - 1] = subbag[child_count - 1];
        new_subbag->data_count = data_count;
        new_subbag->child_count = child_count;

        // ���� �ڽ� ����
        new_root->subbag[0] = new_subbag;
        new_root->child_count = 1;

        new_root->fix_excess(0);
        // ���ο� tree�� root
        *this = *new_root;
    }

    return true;
}



template <class Item>
bool bTree<Item>::loose_erase(const Item& target) {
    size_t index = 0;
    // target���� ũ�ų� ���� ù��° �ε���
    while ((index < data_count) && (data[index] < target)) {
        index++;
    }
    // subbag ���� target�� ������ ����
    if (is_leaf() && (data[index] != target)) {
        return false;
    }
    // subbag ���� target�� ������ ���� 
    else if (is_leaf() && (data[index] == target)) {
        for (size_t i = index; i < data_count - 1; i++) {
            data[i] = data[i + 1];
        }
        data_count--;
        return true;
    }
    // subbag�� �����ϰ� target�� ������ subbag[index] ����
    else if(!is_leaf() && (data[index] != target)) {
        bool b =subbag[index]->loose_erase(target);
        if (!b) { // subbag�� target�� �������� �ʴ´ٸ� ����
            return false;
        }
        // subbag[index] target�� �����ϰ� MINIMUM ��Ģ�� �������� �ʴ´�
        if (subbag[index]->data_count < MINIMUM) {
            fix_shortage(index);
        }
        return true;
    }
    // subbag�� �����ϰ� target�� ������
    else { // subbag[index]���� ���� ū �����͸� target ����Ͽ� ����
        subbag[index]->remove_biggest(data[index]);
        if (subbag[index]->data_count < MINIMUM) {
            fix_shortage(index);
        }
        return true;
    }
}

template <class Item>
void bTree<Item>::remove_biggest(Item& removed_entry) {
    if (is_leaf()) { // subbag�� ����
        // ���� ū �����͸� removed_entry�� �����ϰ� ����
        removed_entry = data[data_count - 1];
        data_count--;
    }
    else { //subbag�� ������ ���� ū subbag���� �̵�
        subbag[child_count - 1]->remove_biggest(removed_entry);
        // subbag�� �����Ͱ� MINIMUM���� ������
        if (subbag[child_count - 1]->data_count < MINIMUM) {
            fix_shortage(child_count - 1);
        }
    }
}

template <class Item>
// subbag[index]�� �����Ͱ� ������ ���
void bTree<Item>::fix_shortage(size_t index) {
    // subbag[index]�� MINIMUN-1, subbag[index-1]�� �����ϸ� data > MINIMUM�� ���
    if ((index > 0)&&(subbag[index - 1]->data_count > MINIMUM)) {
        // subbag[index]�� �θ��� �ٷ� ���� �����͸� �޴´�.
        for (size_t i = subbag[index]->data_count; i > 0; i--) {
            // subbag[index]�� ������ �� ĭ �̵�
            subbag[index]->data[i] = subbag[index]->data[i - 1];
        }
        subbag[index]->data[0] = data[index - 1];
        subbag[index]->data_count++;
        // subbag[index - 1]�� ū �����͸� �θ𿡰� �ش�.
        data[index - 1] = subbag[index - 1]->data[subbag[index - 1]->data_count - 1];
        subbag[index - 1]->data_count--;

        
        // subbag[index]�� subbag�� ������ �ִٸ� �̵�
        if (!subbag[index]->is_leaf()) {
            // subbag[index]�� subbag�� �� ĭ �̵�
            for (size_t i = subbag[index]->child_count; i > 0; i--) {
                subbag[index]->subbag[i] = subbag[index]->subbag[i - 1];
            }
            subbag[index]->subbag[0] = subbag[index - 1]->subbag[subbag[index - 1]->child_count - 1];
            subbag[index]->child_count++;
            subbag[index - 1]->child_count--;
        }
    }
    // subbag[index]�� MINIMUN-1, subbag[index+1]�� �����ϸ� data > MINIMUM�� ���
    else if ((index < child_count - 1) && (subbag[index + 1]->data_count > MINIMUM)) {
        // subbag[index]�� �θ��� ���� ���� �����͸� �޴´�.
        subbag[index]->data[subbag[index]->data_count] = data[index];
        subbag[index]->data_count++;
        // �θ��� �����Ϳ��� subbag[index+1] ���� ���� ���� �ش�
        data[index] = subbag[index + 1]->data[0];
        // subbag[index+1] �� ĭ �̵�
        for (size_t i = 0; i < subbag[index + 1]->data_count - 1; i++) {
            subbag[index + 1]->data[i] = subbag[index + 1]->data[i + 1];
        }
        subbag[index + 1]->data_count--;
        
        
        // subbag[index]�� subbag�� ������ �ִٸ� �̵�
        if (!subbag[index]->is_leaf()) {

            // subbag[index+1] ���� ���� subbag�� subbag[index]�� ���� ū subbag���� �̵�
            subbag[index]->subbag[subbag[index]->child_count] = subbag[index + 1]->subbag[0];
            //subbag[index + 1] �� ĭ �̵�
            for (size_t i = 0; i < subbag[index + 1]->child_count - 1; i++) {
                subbag[index + 1]->subbag[i] = subbag[index + 1]->subbag[i + 1];
            }
            subbag[index]->child_count++;
            subbag[index + 1]->child_count--;
        }
    }

    // subbag[i]�� MINIMUM - 1, subbag[index - 1]�� �����ϸ� data == MINIMUM�� ���
    else if ((index > 0) && (subbag[index - 1]->data_count == MINIMUM)) {
        // data[index - 1], subbag[index], subbag[index -1]�� subbag[index-1]�� ��ģ��.
        // data�� subbag[index - 1] �̵�
        subbag[index - 1]->data[subbag[index - 1]->data_count] = data[index - 1];
        for (size_t i = index; i < data_count; i++) { // ������ ��ĭ �̵�
            data[i - 1] = data[i];
        }
        data_count--;
        subbag[index - 1]->data_count++;
        // subbag[index]�� subbag[index - 1]�̵�
        for (size_t i = 0; i < subbag[index]->data_count; i++) {
            subbag[index - 1]->data[subbag[index - 1]->data_count + i] = subbag[index]->data[i];
        }
        subbag[index - 1]->data_count += subbag[index]->data_count;

        //subbag[index]�� subbag�� ���� ���
        if (!subbag[index]->is_leaf()) {
            // subbag[index]�� subbag�� subbag[index -1]�� �̵�
            for (size_t i = 0; i < subbag[index]->child_count; i++) {
                subbag[index - 1]->subbag[subbag[index - 1]->child_count + i] = subbag[index]->subbag[i];
            }
            subbag[index - 1]->child_count += subbag[index]->child_count;
        }

        //data�� subbag�� index���� ��ĭ ������ �̵�
        for (size_t i = index; i < child_count - 1; i++) {
            subbag[i] = subbag[i + 1];
        }
        child_count--; 

    }
    // subbag[i]�� MINIMUM - 1, subbag[index + 1]�� �����ϸ� data == MINIMUM�� ���
    else if ((index < child_count - 1) && (subbag[index + 1]->data_count == MINIMUM)) {
        // data[index], subbag[index], subbag[index + 1]�� subbag[index]�� ��ģ��.
        // data�� subbag[index - 1] �̵�
        subbag[index]->data[subbag[index]->data_count] = data[index];
        for (size_t i = index; i < data_count - 1; i++) {   // ������ �� ĭ �̵�
            data[i] = data[i + 1];
        }
        data_count--;
        subbag[index]->data_count++;
        // subbag[index + 1]�� subbag[index]�� �̵�
        for (size_t i = 0; i < subbag[index + 1]->data_count; i++) {
            subbag[index]->data[subbag[index]->data_count + i] = subbag[index + 1]->data[i];
        }
        subbag[index]->data_count += subbag[index + 1]->data_count;

        //subbag[index]�� subbag�� ���� ���
        if (!subbag[index]->is_leaf()) {
            // subbag[index + 1]�� subbag�� subbag[index]�� �̵�
            for (size_t i = 0; i < subbag[index + 1]->child_count; i++) {
                subbag[index]->subbag[subbag[index]->child_count + i] = subbag[index + 1]->subbag[i];
            }
            subbag[index]->child_count += subbag[index + 1]->child_count;
        }

        //data subbag�� index + 1���� ��ĭ ������ �̵�
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
    // ���ο� root ����
    if ((this->data_count == 0) && (this->child_count == 1)) {
        *this = *subbag[0];
    }

    return true;
}
#endif