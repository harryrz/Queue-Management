#include "Customer.h"
#include <iostream>

using namespace std;

Customer::Customer(double arrival, int items) {
  arrivalTime = arrival;
  departureTime = -1;
  numOfItems = items;
  next = nullptr;
}

Customer::~Customer() {
}

double Customer::get_arrivalTime() { return arrivalTime; }

double Customer::get_departureTime() { return departureTime; }

int Customer::get_numOfItems() { return numOfItems; }

Customer* Customer::get_next() { return next; }

void Customer::set_arrivalTime(double arrival) { arrivalTime = arrival; }

void Customer::set_departureTime(double departure) {
  departureTime = departure;
}

void Customer::set_numOfItems(int items) { numOfItems = items; }

void Customer::set_next(Customer* nextCustomer) { next = nextCustomer; }

void Customer::print() {
  cout << "Arrival time: " << arrivalTime << std::endl;
  if (departureTime != -1) {
    cout << "Departure time: " << departureTime << std::endl;
  } else {
    cout << "Departure time: "
         << "N/A" << std::endl;
  }
  cout << "Number of items: " << numOfItems << std::endl;
}
