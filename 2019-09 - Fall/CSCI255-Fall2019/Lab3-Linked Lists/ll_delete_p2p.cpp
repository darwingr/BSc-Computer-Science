/* ll_delete_p2p.cpp
 * -----------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Thursday, March 12, 2020
 *
 * Purpose: 
 * Visualize on: http://www.pythontutor.com/cpp.html#
 */
struct node {
  int   info = 0;
  node* next = nullptr;
  node(int el=0, node* n = nullptr) :
    info(el),
    next(n)
  {}
};

// Delete the first node from a chain of nodes,
// returning a pointer to the rest of the list.
node* decapitate(node* sublist_head) {
  if (sublist_head == nullptr) return nullptr;
  node* neck = sublist_head->next;
  sublist_head->next = nullptr; // protect the body
  delete sublist_head;
  return neck;
}

int main() {
  // Build the linked list
  node *head, *tail;
  head              = new node(0);
  head->next        = new node(1);
  head->next->next  = new node(2);
  tail = head->next->next;

  const int i = 0; // works for 0,1,2,3,...

  node** link_ptr = &head;
  node*  alt_tail   = nullptr;


  for (int k=0; *link_ptr != nullptr; k++) {
    // base case: 1 element, both head and tail
    //      is it the i'th element though?
    if (k == i) {
      if (*link_ptr == tail) tail = alt_tail;
      *link_ptr = decapitate(*link_ptr); // change underlying value
    } else {
      alt_tail = *link_ptr;
      link_ptr = &(*link_ptr)->next; // move the link pointer to next link
    }
  }
  return 0;
}
