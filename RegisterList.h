#ifndef REGISTERLIST_HPP
#define REGISTERLIST_HPP

#include "Register.h"

class RegisterList {
 private:
  Register* head; // first register 
  int size; // number of registers

 public:
  RegisterList();
  ~RegisterList();
  Register* get_head();
  int get_size();
  Register* get_min_items_register(); // get the register with min items 
  Register* get_free_register(); // return the register with no customers
  Register* calculateMinDepartTimeRegister(double expTimeElapsed);


  bool foundRegister(int ID);
  void enqueue(Register* newRegister);  // place a register at the end of the queue
  Register* dequeue(int ID);            // change the size
  void print();
};

#endif /* REGISTERLIST_HPP */
