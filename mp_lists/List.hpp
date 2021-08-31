/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
 template <typename T>
 typename List<T>::ListIterator List<T>::begin() const {
   // @TODO: graded in MP3.1
   return List<T>::ListIterator(head_);
 }

 /**
  * Returns a ListIterator one past the end of the List.
  */
 template <typename T>
 typename List<T>::ListIterator List<T>::end() const {
   // @TODO: graded in MP3.1
   return List<T>::ListIterator(NULL);
 }


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * current = head_;
    while (current != NULL && current->next != NULL) {
      current = current->next;
      delete current->prev;
    }
    if (current != NULL)
      delete current;
    length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if (!this->empty()) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  head_ = newNode;


  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
    newNode -> prev = tail_;
    newNode -> next = NULL;

    if (!this->empty()) {
      tail_ -> next = newNode;
    }
    if (head_ == NULL) {
      head_ = newNode;
    }
    tail_ = newNode;

    length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* temp = head_;
  ListNode* next;
  ListNode* last = NULL;
  if (temp == NULL || temp->next == NULL || temp->next->next == NULL) {
    return;
  }
  while(temp != NULL && temp->next != NULL && temp->next->next!=NULL) {
    if (temp == head_) {
      head_ = temp->next;
    } else {
      last->next = temp->next;   //5 temp->next  1 temp->prev
    }
    temp->next->prev = last;
    next = temp->next->next->next;     //next 4
    temp->next->next->next = temp;    //3 -> 1
    temp->prev = temp->next->next;    //3 <- 1
    temp->next = NULL;                // 1->Null
    last = temp;
    temp = next;   // temp = 4
  }
  if (temp != NULL) {
    temp->prev = last;
    last->next = temp;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  ListNode *curr = startPoint;
  ListNode *temp;

  if (startPoint == NULL || endPoint == NULL)
        return;
  while (curr != endPoint) {
      temp = curr->next;
      curr->next = curr->prev;
      curr->prev = temp;
      curr = temp;
  }
  temp = endPoint->next;
  endPoint->next = endPoint->prev;
  endPoint->prev = startPoint->next;
  if (startPoint->next != NULL)
    startPoint->next->next = endPoint;
  startPoint->next = temp;
  if (temp != NULL)
    temp->prev = startPoint;
  temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode * start = head_;
  ListNode * end = start;
  while (start != NULL) {
      end = start;
      for (int i=1; i<n && end != NULL; i++) {
          end = end->next;
      }
      if (end == NULL) {
          reverse(start, tail_);
          if (head_ == tail_) {
            head_ = start;
        }
          break;
      } else {
          reverse(start, end);
          if (head_ == end)
            head_ = start;
          start = end ->next;
      }
  }
    if (end != NULL)
        tail_ = end;
  // reverse(start, tail_);
  // if (head_ == tail_)
  //   head_ = start;
  int i = 1;
  ListNode * temp = head_;
  while (temp != tail_) {
      i++;
      temp = temp->next;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
    ListNode * head;
    ListNode * curr;
    ListNode * curr1;
    ListNode * curr2;

    if (first == NULL)
        return second;
    if (second == NULL)
        return first;
    if(first->data < second->data){
        head = first;
        curr1 = first->next;
        curr2 = second;
    } else {
        head = second;
        curr1 = first;
        curr2 = second->next;
    }
    curr = head;

    while (curr1!=NULL && curr2!=NULL) {
        if (curr1->data < curr2->data) {
            curr->next = curr1;
            curr1->prev = curr;
            curr = curr1;
            curr1 = curr1->next;
        } else {
            curr->next = curr2;
            curr2->prev = curr;
            curr = curr2;
            curr2 = curr2->next;
        }
    }

    if (curr1 == NULL) {
        curr->next = curr2;
        if (curr2!=NULL) {
            curr2->prev = curr;
        }
    } else {
        curr->next = curr1;
        curr1->prev = curr;
    }

  return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength <= 1)
    return start;
  int mid = chainLength / 2;
  ListNode * secondList = split(start, mid);
  start = mergesort(start, mid);
  secondList = mergesort(secondList, chainLength - mid);
  return merge(start, secondList);
}
