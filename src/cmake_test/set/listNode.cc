#include <iostream>
 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
int main() {
    std::cout << "set 1"<<std::endl;
    ListNode* node =new ListNode(3%10);
    ListNode* ptr=new ListNode(2);
    ptr->next=node;
    ptr=node;
    std::cout<<ptr->val<<" "<<ptr->next<<std::endl;
    return 0;
}