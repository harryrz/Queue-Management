#ifndef QUEUELIST_HPP
#define QUEUELIST_HPP

#include "Customer.h"
#include "QueueList.h"

class QueueList {
 private:
  Customer* head;

 public:
  QueueList();
  QueueList(Customer* customer);
  ~QueueList();

  Customer* get_head();

  int get_items();  // gets the number of items in a queue
  
  void enqueue(
      Customer* customer);  // insert a customer at the tail of the list
  Customer* dequeue();      // remove a customer from the head of the list
  
  bool empty_queue();  // deletes all customers in the queue, return true if it
                       // wasn't empty
  void print();        // prints the customers in a queue
};

#endif /* QUEUELIST_HPP */
