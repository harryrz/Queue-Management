#include "RegisterList.h"

#include <iostream>

#include "Register.h"
using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() {
  // Delete all registers in the list
  while(head!=nullptr){
    Register* pr = head;
    head = head->get_next();
    delete pr;
  }
}

Register* RegisterList::get_head() { return head; }

int RegisterList::get_size() { 
  // return number of registers 
  return size;
}


Register* RegisterList::get_min_items_register() {
  // loop all registers to find the register with least number of items
  Register* pr = head;
  Register* min_item_pr = head;
  int min_items = pr->get_queue_list()->get_items();
  /*if(head==nullptr){
    return nullptr;
  } else {
    int itemNumArr[];
    int index = 0;
    while(pr!=nullptr){
      itemNumArr[index] = pr->get_queue_list()->get_items();
      pr = pr->get_next();
      index ++;
    }
    itemNumArr[index] = '\0';
    index = 0;
    int min_index = index;
    while(itemNumArr[index+1] != '\0'){
      if(itemNumArr[index+1] < itemNumArr[index]){
        min_index = index + 1;
      }
      index ++;
    }
    index = 0;
    pr = head;
    while(index <= min_index){
      pr = pr->get_next();
    }
  }
  return pr;*/
  while(pr!= nullptr){
    if((pr->get_queue_list()->get_items()) < min_items){
      min_items = pr->get_queue_list()->get_items();
      min_item_pr = pr;
    }
    pr = pr->get_next();
  }
  return min_item_pr;
}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr
  Register* pr = head;
  if(head == nullptr){
    return nullptr;
  } else {
    while(pr!=nullptr){
      if(pr->get_queue_list()->get_head() == nullptr){
        return pr;
      }
      pr = pr->get_next();
    }
    return nullptr;
  }
}

void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size 
  if(head == nullptr){
    head = newRegister;
  } else {
    Register* prev = head;
    Register* pr = head->get_next();
    while(pr!=nullptr){
      prev = prev->get_next();
      pr = pr->get_next();
    } // until here pr is the next of the last node which points to NULL, prev points to last Node.
    prev->set_next(newRegister);
    size++;
  }
  
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise
  if(head == nullptr){
    return false;
  } else {
    Register* pr = head;
    while(pr != nullptr){
      if(pr->get_ID() == ID){
        return true;
      }
      pr = pr->get_next();
    }
    return false;
  }
}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID
  
  if(head == nullptr){
    return nullptr;
  } else if (head->get_ID()==ID){
    Register* copyhead = head;
    head = head->get_next();
    copyhead->set_next(nullptr);
    size--;
    return copyhead;
  } else { // the leading node doesn't have matching ID
    Register* pr = head->get_next();
    Register* prev = head;
    while(pr!=nullptr){
      if(pr->get_ID()==ID){
        prev->set_next(pr->get_next());
        pr->set_next(nullptr);
        size--;
        return pr;
      }
      pr=pr->get_next();
      prev=prev->get_next();
    }
    return nullptr;
  }
  
  
  
  
  /*else if(head->get_next() == nullptr){
    Register* he = head; // only one node
    if(he->get_ID() == ID){
      head == nullptr;
      return he;
    } else {
      return nullptr;
    }
  } else {
    Register* pr = head->get_next();
    Register* prev = head;
    while(pr!=nullptr){
      if(p)
    }
  }*/
  // return the dequeued register
  // return nullptr if register was not found
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
  // return the register with minimum time of departure of its customer
  // if all registers are free, return nullptr
  if(head == nullptr){
    return nullptr;
  } else {
    Register* pr = head;
    Register* min_depart_time_r = head;
    //double dt_list[size];
    ///int index = 0;
    double min_time = 100000000000000;
    while(pr!=nullptr){
      if (pr->calculateDepartTime() < min_time){
        min_time = pr->calculateDepartTime();
        min_depart_time_r = pr;
      }
      pr = pr->get_next();
    } // we have the min depart time
    return min_depart_time_r;
  }
}



void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
