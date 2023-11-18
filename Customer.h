#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <iostream>

class Customer {
 private:
  double arrivalTime;  // when did they arrive, i.e. number of seconds from the
                       // beginning of the experiment
  double departureTime;  // when did they leave
  int numOfItems;        // number of items they have to check out
  Customer* next;        // a pointer to the next pointer in line
 public:
  Customer(double arrivalTime, int numOfItems);
  ~Customer();
  double get_arrivalTime();
  double get_departureTime();
  int get_numOfItems();
  Customer* get_next();

  void set_arrivalTime(double arrivalTime);
  void set_departureTime(double departureTime);
  void set_numOfItems(int numOfItems);
  void set_next(Customer* next);

  void print();
};

#endif /* CUSTOMER_HPP */
