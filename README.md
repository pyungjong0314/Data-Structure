# 자료구조
## SET Implementation with Double Linked List
  ### DNode
  - DNode는 Double Linked List 구조를 가지는 클래스입니다.
  - setData, setPreLink, setAfterLink
  - Linked List length(), search(), locate(), insert(), remove(), clear(), copy()

  ### SET
  -  Double Linked List를 사용해 구현한 집합 클래스입니다.
  - Operator: =, +=, ==, !=, +
  - Methods: erase(), count(), grab(), size(), insert(), show_contents(), sort()

## Dequeue Implementation with Double Linked List
  ### Dequeue
  -  Double Linked List를 사용해 구현한 Dequeue(양방향 큐) 클래스입니다.
  -  pop_front(), pop_back(), push_front(), push_back(), operator=, empty(), front(), back(), size()

## B-Tree Implementation
bTree는 B-Tree(균형 이진 탐색 트리)를 기반으로 구현된 템플릿 클래스입니다. 이 클래스는 데이터를 효율적으로 삽입, 삭제, 검색할 수 있는 자료 구조를 제공합니다.
  ### Private Methods
  - bool loose_insert(const Item& entry): 데이터를 임시적으로 삽입합니다.
  - void fix_excess(size_t index): 특정 위치에서 데이터가 초과된 경우 이를 수정합니다.
  - bool loose_erase(const Item& target): 데이터를 임시적으로 삭제합니다. 삭제 후 B-Tree 규칙을 위반할 경우 추가 수정이 필요합니다.
  - void fix_shortage(size_t index): 특정 위치에서 데이터가 부족한 경우 이를 수정합니다.
  - void remove_biggest(Item& removed_entry): 현재 노드에서 가장 큰 데이터를 제거합니다.
  - bool is_leaf(): 현재 노드가 리프 노드인지 확인합니다.
  - 
  ### Public Methods
  - clear(): 트리의 모든 데이터를 제거합니다.
  - bool empty(): 트리가 비어 있는지 확인합니다.
  - bool insert(const Item& entry): 데이터를 삽입합니다.
  - bool erase_one(const Item& target): 특정 데이터를 트리에서 삭제합니다.
  - size_t count(const Item& target): 특정 데이터의 개수를 반환합니다.
  - void show_contents(size_t d): 트리의 내용을 출력합니다.
