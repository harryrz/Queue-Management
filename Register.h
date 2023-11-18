// Created by Salma Emara on 2023-06-02.
#ifndef Register_h
#define Register_h

#include <iostream>

#include "QueueList.h"

class Register {
 private:
  int ID;
  double secPerItem;
  double overheadPerCustomer;
  double availableTime;
  QueueList* queue;
  Register* next;

 public:
  Register(int ID, double secPerItem, double overheadPerCustomer, double entryTime);
  ~Register();

  int get_ID();
  double get_secPerItem();
  double get_overheadPerCustomer();
  double get_availableTime();
  Register* get_next();
  QueueList* get_queue_list();

  void set_availableTime(double availableSince);
  void set_next(Register* next);


  double calculateDepartTime(); // calculate the time at which a customer will be departed
  void departCustomer(QueueList *doneList); // remove a customer from the queue

  void print(); 
};

#endif /* Register_h */
