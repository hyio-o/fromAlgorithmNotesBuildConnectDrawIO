#include "../../0-初始化定义/2-链表定义.h"
#include <cstddef>

class solution{
public:


private:
    ListNode *reverseList(ListNode *head) {
        if (head == NULL || head->next == NULL) {
        return head;
        }
        ListNode *rlink_head, *temp;
        rlink_head = reverseList(head->next); // 1 -> 2 -> 3 -> 4 -> 5
        temp = head->next;                    //  2->
        temp->next = head;                    //  1->
        head->next = NULL;                    //
        return rlink_head;
    }
    ListNode *reverseList_twoPoint(ListNode *head) { 
      // 1 -> 2 -> 3 -> 4 -> 5
      // o1
      ListNode *o1, *o2, *n1, *n2;
      o1 = head;
      n1 = NULL;
      while (o1 != NULL) {
        o2 = o1->next; //
      }
    }
};
// 找到链表的中间节点，反转后半段链表