#include <cstddef>
#include <iostream>
#include <system_error>
using namespace std;

typedef int ELemType;
struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}



void insert(int data) {
    Node* head;
    Node* newNode = new Node();
    newNode->data = data;
    newNode->prev = head;
    newNode->next = head == nullptr ? nullptr : head->next;

    if (head == nullptr) {
        head = newNode;
    } else {
        head->next = newNode;
    }
}

void initializeList(Node** head) {
    *head = createNode(1);
    (*head)->next = (*head);
    (*head)->prev = (*head);
}

// define cyc
typedef struct cycDoubNode {
  ELemType data;
  struct cycDoubNode *next;
  struct cycDoubNode *prior;
  int freq;
} DoubNode, *DoubList, *cycDoubList;

// cycDoubList init
void cycDoubListInit(cycDoubList L) {
  L = (cycDoubNode *)malloc(sizeof(cycDoubNode));
  L->prior = L->next = L; // 单个循环双链表 init
}


// get length
int cycGetlen(cycDoubNode* L){
    int cur_i = 0;
    cycDoubNode *cur = L->next; // 存在值的节点
    while (cur != L) {  // 直到 cur.next = NULL, 但是 cur.data 存在
        cur = cur->next;
        cur_i++;
    }
    return cur_i;
}

// locate
cycDoubList cycDoubLocate(cycDoubList L, ELemType x){
    cycDoubNode *cur = L->next; // find x
    while (cur->data != x && cur->next != L) {
        cur = cur->next;
    }
    if(cur->data == x)  
        return cur;
    else
        return NULL;;
}
// insert cycD
cycDoubList cycDoubListInsert(cycDoubList L, ELemType x, int n){
    if(n<1 || n > cycGetlen(L) + 1) return NULL;
    cycDoubNode *cur = L->next;
    int cur_i = 1;  // 找到第 n-1 个节点，进行插入
    while (cur_i < n) { // 如果 n = 5, cur_i = 4时候跳出while
        cur = cur->next;
        cur_i++;
    }
    cycDoubNode *temp = (cycDoubNode*)malloc(sizeof(cycDoubNode));
    temp->data = x;
    // 接下来 insert temp 进 cur 左右  1 2 3 4 5
    temp->next = cur->next; // cur:4, n=5; temp->5
    temp->next->prior = temp; //  temp <- 5 ;
    cur->next = temp;   // 4->temp
    temp->prior = cur;  // temp->4
    
    return L;
}

DoubList cycInsert_sec(DoubList list, ELemType data, int n){
    if(list==NULL || n <1)  return list;
    DoubNode* cur_node = list;
    int cur_index = 0;
    while (cur_node != list && cur_index < (n-1)) {
      // 此时cur_index还没有轮询到第n个节点，继续后移
      // cur_node != list 还没到最后一个 cur_index < (n-1)
      cur_node = cur_node->next;
      cur_index++;
    }
    // 判断是否移动到最后一个节点 && 未达到 第n个节点 的要求
    if(cur_node->next == list){
        if(cur_index != (n-1))
            return list;
    }
    // 正式开始插入链表节点
    DoubNode *temp = (DoubNode*)malloc(sizeof(DoubNode));
    temp->data = data;

    temp->next = cur_node->next;
    temp->prior = cur_node;
    cur_node->next->prior = temp;
    cur_node->next = temp;
    
    return list;
}

// delete cyc删除第n个结点，且将删除的值通过data传出
ELemType cycDelete_fail(DoubList list, ELemType *data, int n){
  if (list == NULL || n < 1)
    return -1;
  DoubNode *cur_node = list;
  int cur_index = 0;
  while (cur_node != list && cur_index < (n - 1)) {
    // 此时cur_index还没有轮询到第n个节点，继续后移
    // cur_node != list 还没到最后一个 cur_index < (n-1)
    cur_node = cur_node->next;
    cur_index++;
  }
  // 判断是否移动到最后一个节点 && 未达到 第n个节点 的要求
  if (cur_node->next == list) {
    if (cur_index != (n - 1))
      return -1;
  }
  // 正式删除节点 与 输出该节点值 ; 此时 cur_node 为需要删除&输出的节点
  DoubNode *temp = cur_node->next;
  temp->prior->next = cur_node->next;
}

ELemType cycDelete(DoubNode *L, int n, ELemType *data){
    DoubNode *pre = L;
    int pre_i = 0;
    while(pre_i < n){
        pre = pre->next;
        pre_i++;
        if(pre==L)  return -1;
    }
}

int main() {
    Node* head = nullptr;
    initializeList(&head);
    cout << "循环双链表已创建" << endl;
    return 0;
}

/*
 * 循环双链表相比普通双链表有以下几个优势：

1. 内存利用率更高：循环双链表不需要像单链表那样在尾部使用哨兵节点来检测链表是否结束，因此可以节省哨兵节点的内存开销。
2. 插入和删除操作更高效：在循环双链表中，头节点的前一个节点是尾节点，尾节点的下一个节点是头节点，形成一个闭环。因此，在插入和删除节点时，只需修改相邻节点的指针即可，无需像普通双链表那样需要遍历链表来找到插入或删除的位置。这使得循环双链表的插入和删除操作更加高效。
3. 适合环形数据结构：循环双链表适用于需要循环遍历的数据结构，例如在图形数据结构中，可以使用循环双链表来表示环形的边。在普通双链表中，如果需要实现环形结构，则需要手动设置环形条件并处理环形的遍历，而循环双链表则自动支持环形结构。
4. 无需特殊处理尾节点：在普通双链表中，尾节点的指针需要特殊处理，因为它的下一个节点是头节点。而在循环双链表中，尾节点的指针和其他节点的指针一样，指向下一个节点即可，无需特殊处理尾节点。

综上所述，循环双链表相比普通双链表具有更高的内存利用率、更高效的插入和删除操作、更适合环形数据结构以及无需特殊处理尾节点的优势。
 * */

//
// Created by 陈至宇 on 2023/10/28.
//

#ifndef ALGORITHMNOTESBUILDING_1_循环双链表定义_H
#define ALGORITHMNOTESBUILDING_1_循环双链表定义_H

#endif //ALGORITHMNOTESBUILDING_1_循环双链表定义_H
