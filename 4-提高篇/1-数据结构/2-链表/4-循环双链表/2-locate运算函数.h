#include "./1-循环双链表定义.h"
#include <cstddef>

// locate 带表头节点 双链表h ，每个节点4个数据成员：
// prior 指向前驱结点、 next 后继结点、data 数据成员 、访问频度 freq （初始值都为0）
// 每当双链表进行一次 locate(h, x)运算，元素值为x的freq++
// 并且让链表节点保持访问 频度递减 顺序排列，访问频繁的靠近表头

DoubList ListInit(){
    DoubList list = (DoubList)malloc(sizeof(DoubNode));
    list->prior = NULL;
    list->next = NULL;
    list->data = 0;
    list->freq = 0;
    return list;
}

int locate(DoubNode *h, ELemType x)
{
    DoubNode *pre = h->next;
    DoubNode *temp;
    // 1. 找到data域值为 x 的节点， 并用pre表示
    while (pre!=NULL && pre->data!=x) { 
        pre = pre->next;
    }
    // 2. 判断找到了没，找到了就 1-频度，2-插入排序
    if(pre == NULL) return 0;
    else{
        pre->freq++;    // 1-频度 自增
        temp = pre->prior;  // 2-设置pre的左边节点好插入排序
        // 2-插入排序 “temp != h” 是双链表头节点则不进入while
        // freq 大的排在前面
        while (temp != h && temp->freq < pre->freq) {
          // 交换 temp 和 pre 的位置

          // 第一步 1 2 3 4，1 <- 3; // 第二步 1 2 3 4, 1 -> 3;
          pre->prior = temp->prior; // 此时 pre->prior == 1
          pre->prior->next = pre;

          // 第三步 1 2 3 4, 2 -> 4;
          temp->next = pre->next;
          // 第四步
          if (temp->next != NULL){ // 如果 4 不是空值，
            //1 2 3 4, 4 -> 2;
            temp->next->prior = pre;
          } // 如果 4 是空值， 那么下面
          // 1 3 2 4
          pre->next = temp;
          temp->prior = pre;
          // 向前（插入排序） 
          temp = pre->prior;
        }
    }
    return 1;    
}