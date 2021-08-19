// Nice way to traverse a linked list,
// makes it easier to implement methods like deleteIthNode(i),
// as was done in assignment 2 and Lab 3 of CSCI 255.
// I never thought a "pointer to a pointer" would have ever
// made my code simpler to read and reason about but here we are.

struct node {
  int   info = 0;
  node* next = nullptr;
  node(int el=0, node* n = nullptr) :
    info(el),
    next(n)
  {}
};

int main() {
  // Build the linked list
  node *head, *tail;
  head              = new node(1);
  head->next        = new node(2);
  head->next->next  = new node(3);
  tail = head->next->next;

  // Traverse linked list with a pointer (ndptr) and 
  //    a pointer to a pointer (preptr) to change the value of
  //    the next pointer on the preceding node, allowing preptr
  //    to be initialized as a to the head pointer.
  node*  ndptr  = head; // node pointer, current node of interest
  node** preptr = &head;
  while (ndptr != nullptr) {
    preptr = &ndptr->next;
    ndptr  = ndptr->next;
  }
  // preptr now points to next (address) on the last node in the list.
  // We want to change the value of n3.next to be the address of
  // the first node (head).
  *preptr = head;
  // should set next on tail node to point to the first node

  return 0;
}