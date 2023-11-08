#include "../../0-初始化定义/2-链表定义.h"
#include <cstddef>



CLinkList cycList(){
    CNode *Clist = (CLinkList) malloc(sizeof(CNode));
    Clist->next = Clist;
    Clist->data = (int)getchar();
    return Clist;
}

// insert
void insertCYCList(CLinkList index, int data, int n){
    if(index == NULL || n<1)    return;
    CNode *cur_index = index;   // 轮询节点
    int cur_i=0;
    // 走到指针链尾；
    while(cur_index->next != index && cur_i<(n-1)){
        // cur_index 不是最后一个节点， cur
        cur_index = cur_index->next;
        cur_i++;
    }
    // 判断是否到了链尾，但是没有到达n的指定位置
    if(cur_index->next == index && cur_i != (n-1))  return;
    CNode *new_index = (CLinkList)malloc(sizeof(CNode));
    new_index->data = data;
    new_index->next = cur_index->next;  // 继承 cur_index 链尾的节点（默认指向了链表头节点）
    cur_index->next = new_index;        // cur_index->next 更新为指向new_index
    return;
}

// delete 
void deleteCYCList(CLinkList index){
    CLinkList cur_index = index->next;  // 第一个节点
    CLinkList next_index = NULL;
    while (cur_index != index) {
        next_index = cur_index->next;
        free(cur_index);
        cur_index = next_index;
    }
    //index->next = index;
}

/*1、定义一个结点指针cur指向头结点，用来遍历链表；
2、定义一个变量cur_i，用来表示当前结点的序号，初始化为0表示当前指向头结点；
3、将cur指针不断往后移动，直到下个位置就是插入位置n，即当cur_i==(n-1)跳出循环;
4、若结束循环后是最后一个结点(cur->next==list)，但不是插入位置前一结点，说明链表长度不够；
5、否则，说明当前结点cur的下个位置就是插入位置n，分配存储空间给新结点new；
6、把值填进新节点的数据域，用新结点指向当前节点的下个节点；
7、将当前节点指向新节点，完成插入操作。
 */
/*
 * 循环单链表相比普通单链表，在以下操作上更为方便：
循环遍历：循环单链表可以方便地从头节点开始循环遍历整个链表，而普通单链表需要进行特殊处理或者遍历到尾节点才能结束遍历。
插入和删除操作：在循环单链表中，插入和删除节点时，可以避免特殊处理头节点和尾节点的链接关系，因为它们之间已经形成了一个闭环。而在普通单链表中，需要额外处理头节点和尾节点的链接关系。
综上所述，循环单链表在循环遍历和插入/删除操作上比普通单链表更方便。
 * */
struct Node {
    int data;
    Node* next;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}



Node* initializeList() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = head; // 形成循环链表
    return head;
}



//



int main() {
    Node* head = initializeList();
    std::cout << "循环单链表已创建" << std::endl;
    return 0;
}



//
// Created by 陈至宇 on 2023/10/28.
//

#ifndef ALGORITHMNOTESBUILDING_1_循环单链表定义_H
#define ALGORITHMNOTESBUILDING_1_循环单链表定义_H

#endif //ALGORITHMNOTESBUILDING_1_循环单链表定义_H
