#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() { head = nullptr; }

QueueList::QueueList(Customer* customer) { head = customer; }

QueueList::~QueueList() {
  while(head!=nullptr){
    Customer* pc = head;
    head = head->get_next();
    delete pc;
  }
}

Customer* QueueList::get_head() { return head; }

void QueueList::enqueue(Customer* customer) {
  // a customer is placed at the end of the queue
  // if the queue is empty, the customer becomes the head
  if(head == nullptr){
    head = customer;
  } else {
    Customer* prev = head;
    Customer* pc = head->get_next();
    while(pc!=nullptr){
      prev = prev->get_next();
      pc = pc->get_next();
    } // until here pc is the next of the last node which points to NULL, prev points to last Node.
    prev->set_next(customer);
  }
}

Customer* QueueList::dequeue() {
  // remove a customer from the head of the queue 
  // and return a pointer to it
  Customer* pc = head;
  if(head == nullptr){
    return nullptr;
  } else {
    head = head->get_next();
    pc->set_next(nullptr);
    return pc;
  }
}

int QueueList::get_items() {
  // count total number of items each customer in the queue has
  Customer* pc = head;
  int total = 0;
  if(pc==nullptr){
    return 0;
  } else{
    while(pc!=nullptr){
      total += pc->get_numOfItems();
      pc = pc->get_next();
    }
  }
  return total;
}

bool QueueList::empty_queue() {
  // if the queue is empty, return false
  // if the queue is not empty, delete all customers
  // and return true
  if(head == nullptr){
    return false;
  } else {
    delete head;
    return true;
  }
  
}

void QueueList::print() {
  // print customers in a queue
  Customer* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
