#include <iostream>
#include "Node.h"

using namespace std;

Node *merge(Node *first, Node *second) {
    Node *result, *curr;
    if (first == NULL)
        return second;
    if (second ==NULL)
        return first;
    if (first->data_ < second->data_) {
        result = first;
        first = first->next_;
    } else {
        result = second;
        second = second->next_;
    }
    curr = result;

    while (first!=NULL && second!=NULL) {
        if (first->data_ < second->data_) {
            curr->next_ = first;
            first = first->next_;
        } else {
            curr->next_ = second;
            second = second->next_;
        }
        curr = curr->next_;
    }
    if (first == NULL)
        curr->next_ = second;
    else
        curr->next_ = first;
    return result;
}

Node *split(Node *start, int n) {
    Node *result = NULL;
    Node *curr = start;

    for (int i = 0; i < n-1 && curr != NULL; i++)
        curr = curr->next_;
    if (curr != NULL) {
        result = curr->next_;
        curr->next_ = NULL;
    }
    return result;
}

Node *mergesort(Node *start, int chainLength) {
    // cout << "mergesort: start=" << start->data_ << " length=" << chainLength << endl;
    if (chainLength <= 1)
        return start;
    int mid = chainLength / 2;
    Node *second = split(start, mid);
    start = mergesort(start, mid);
    second = mergesort(second, chainLength - mid);
    return merge(start, second);
}

Node *sort(Node* list) {
    int length = 0;
    Node *curr = list;
    while (curr != NULL) {
        length++;
        curr = curr->next_;
    }
    return mergesort(list, length);
}

Node *listIntersection(Node *first, Node *second) {
  // your code here
  first = sort(first);
  second = sort(second);
  Node * result = NULL;
  while (first != NULL && second != NULL) {
      if (first->data_ == second->data_) {
          if (result != NULL && first->data_ == result->data_) {
              first = first->next_;
              second = second->next_;
          } else {
              Node * newNode = new Node();
              newNode->data_ = first->data_;
              newNode->next_ = result;
              result = newNode;
              first = first->next_;
              second = second->next_;
          }
      } else if (first->data_ < second->data_) {
          first = first->next_;
      } else {
          second = second->next_;
      }
  }
  return result;
}

bool listEqual(Node *first, Node *second) {
    Node *curr1 = first;
    Node *curr2 = second;
    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->data_ != curr2->data_)
            return false;
        curr1 = curr1->next_;
        curr2 = curr2->next_;
    }
    if (curr1 != NULL || curr2 != NULL)
        return false;
    return true;
}

Node::Node() {
    numNodes++;
}

Node::Node(Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
