#include <iostream>
#include "Node.h"
using namespace std;

void printList(Node *head) {
  if (head == NULL) {
    cout << "Empty list" << endl;
    return;
  }

  Node *temp = head;
  int count = 0;
  while(temp != NULL) {
    cout << "Node " << count << ": " << temp ->data_ << endl;
    count++;
    temp = temp->next_;
  }
}

Node *makeList(int n) {
    Node *result = NULL;
    for (int i = 0; i< n; i++) {
        Node *node = new Node();
        node->data_ = i;
        node->next_ = result;
        result = node;
    }
    return result;
}

int main() {
  // Example #1
  Node n_0, n_1, n_2, n_22, n_3, n_4;
  n_0.data_ = 5;
  n_1.data_ = 1;
  n_2.data_ = 2;
  n_22.data_ = 2;
  n_3.data_ = 3;
  n_4.data_ = 4;

  n_0.next_ = &n_1;
  n_1.next_ = &n_2;
  n_2.next_ = NULL;

  n_22.next_ = &n_3;
  n_3.next_ = &n_4;
  n_4.next_ = NULL;

  // cout<<"First List:"<<endl;
  // printList(&n_0);
  // // printList(sort(&n_0));
  // // printList(merge(&n_22, &n_1));
  // cout<<"Second List:"<<endl;
  // printList(&n_22);
  //
  // Node *union1 = listIntersection(&n_0, &n_22);
  // cout<<"Intersection:"<<endl;
  // printList(union1);
  // cout<<endl;


  // Example #2
  Node p00, p01, p02, p03, p10, p11, p12, p13;

  // List 1: 0 2 2 2
  p00.data_ = 0; p00.next_ = &p01;
  p01.data_ = 2; p01.next_ = &p02;
  p02.data_ = 2; p02.next_ = &p03;
  p03.data_ = 2; p03.next_ = NULL;

  // List 2: 0 0 0 4
  p10.data_ = 0; p10.next_ = &p11;
  p11.data_ = 0; p11.next_ = &p12;
  p12.data_ = 0; p12.next_ = &p13;
  p13.data_ = 4; p13.next_ = NULL;

  // cout<<"First List:"<<endl;
  // printList(&p00);
  // cout<<"Second List:"<<endl;
  // printList(&p10);
  //
  // Node *union2 = listIntersection(&p00, &p10);
  // cout<<"Intersection:"<<endl;
  // printList(union2);
  // cout<<endl;

    Node *list = makeList(2000000);
    Node *list1 = makeList(2000000);
    Node *list2 = makeList(4000000);
    // cout<<"First List:"<<endl;
    // printList(list1);
    // cout<<endl<<"Intersection:"<<endl;
    // printList(list2);
    Node *intersection = listIntersection(list1, list2);
    // cout<<endl<<"Second List:"<<endl;
    // printList(intersection);
    // printList(list1);
    if (!listEqual(sort(list), sort(intersection))){
        cout << "TEST FAILED" << endl;
    } else {
        cout << "SUCCESS" << endl;
    }

  return 0;
}
