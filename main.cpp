#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:

// Set mode of the simulation
string getMode();

// Register
void parseRegisterAction(stringstream &lineStream, string mode);
void openRegister(
    stringstream &lineStream,
    string mode);  // register opens (it is upto customers to join)
void closeRegister(stringstream &lineStream,
                   string mode);  // register closes 

// Customer
void addCustomer(stringstream &lineStream,
                 string mode);  // customer wants to join


// Helper functions
bool getInt(stringstream &lineStream, int &iValue);
bool getDouble(stringstream &lineStream, double &dValue);
bool foundMoreArgs(stringstream &lineStream);
bool check_depart_customer(double curTime, double& minTime);
void departingCustomers(double curTime, string mode);
void push_single_queue(string mode);
void print();




// Global variables
RegisterList *registerList; // holding the list of registers
QueueList *doneList; // holding the list of customers served
QueueList *singleQueue; // holding customers in a single virtual queue
double expTimeElapsed; // time elapsed since the beginning of the simulation

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>

int main() {
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0;

  // Set mode by the user
  string mode = getMode();

  string line;
  string command;

  cout << "> ";  // Prompt for input
  getline(cin, line);

  while (!cin.eof()) {
    stringstream lineStream(line);
    lineStream >> command;
    if (command == "register") {
      parseRegisterAction(lineStream, mode);
    } else if (command == "customer") {
      addCustomer(lineStream, mode);
    } else {
      cout << "Invalid operation" << endl;
    }
    cout << "> ";  // Prompt for input
    getline(cin, line);
  }
  // You have to make sure all dynamically allocated memory is freed 
  // before return 0

  //Statistics of the store: (Calculation of wait times using doneList):
  //1. calculating maximum wait time:
  Customer* pc = doneList->get_head();
  double max_wait_time = 0;
  while(pc!=nullptr){
    if((pc->get_departureTime()-pc->get_arrivalTime()) > max_wait_time){
      max_wait_time = pc->get_departureTime()-pc->get_arrivalTime();
    }
    pc = pc->get_next();
  }
  // by here we should have the maximum wait time extracted from the done list
  double total_wait_time = 0;
  int num_of_customers_done = 0;
  pc = doneList->get_head();
  while(pc!=nullptr){
    total_wait_time += (pc->get_departureTime()-pc->get_arrivalTime());
    num_of_customers_done++;
    pc = pc->get_next();
  }
  double avg_wait_time;
  avg_wait_time = total_wait_time / num_of_customers_done;
  //Calculating standard deviation:
  double sd_term = 0;
  pc = doneList->get_head();
  while(pc!=nullptr){
    sd_term += (pow(((pc->get_departureTime()-pc->get_arrivalTime()) - avg_wait_time), 2)) / num_of_customers_done;
    pc = pc->get_next();
  }
  double std_dev;
  std_dev = pow(sd_term, 0.5);
  

  cout << "Finished at time " << expTimeElapsed << endl;
  cout << "Statistics:" << endl;
  cout << "Maximum wait time: " << max_wait_time << endl;
  cout << "Average wait time: " << avg_wait_time << endl;
  cout << "Standard Deviation of wait time: " << std_dev << endl;
  delete registerList;
  delete doneList;
  delete singleQueue;

  return 0;
}

string getMode() {
  string mode;
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
          "\"multiple\" to "
          "simulate multiple queues: \n> ";
  getline(cin, mode);

  if (mode == "single") {
    cout << "Simulating a single queue ..." << endl;
  } else if (mode == "multiple") {
    cout << "Simulating multiple queues ..." << endl;
  }

  return mode;
}

void addCustomer(stringstream &lineStream, string mode) {
  int items;
  double timeElapsed;
  if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments." << endl;
    return;
  }
  // Depending on the mode of the simulation (single or multiple),
  // add the customer to the single queue or to the register with
  // fewest items
  expTimeElapsed += timeElapsed;
  departingCustomers(expTimeElapsed, mode);
  Register* free_r = registerList->get_free_register();
  Customer* newcustomer = new Customer(expTimeElapsed, items);

  if(mode == "single"){
    if(free_r != nullptr){ // there is a free register to put customers
      free_r->get_queue_list()->enqueue(newcustomer);
      cout << "A customer entered" << endl;
      cout << "Queued a customer with free register " << free_r->get_ID() << endl;
      //print();
    } else {
      singleQueue->enqueue(newcustomer);
      cout << "A customer entered" << endl;
      cout << "No free registers" << endl;
      //print();
    }
  } else if (mode == "multiple") {
    cout << "A customer entered" << endl;
    cout << "Queued a customer with quickest register " << registerList->get_min_items_register()->get_ID() << endl;
    registerList->get_min_items_register()->get_queue_list()->enqueue(newcustomer);
    //print();
  }



/*if(free_r != nullptr){ // there is a free register to put customers
    free_r->get_queue_list()->enqueue(newcustomer);
    cout << "A customer entered" << endl;
    cout << "Queued a customer with free register " << free_r->get_ID() << endl;
    //print();
  } else {
    if(mode == "single"){
    singleQueue->enqueue(newcustomer);
    cout << "A customer entered" << endl;
    cout << "No free registers" << endl;
    //print();
  } else if (mode == "multiple"){
    cout << "Queued a customer with quickest register " << registerList->get_min_items_register()->get_ID() << endl;
    registerList->get_min_items_register()->get_queue_list()->enqueue(newcustomer);
  }
  }*/
  
  
}

void parseRegisterAction(stringstream &lineStream, string mode) {
  string operation;
  lineStream >> operation;
  if (operation == "open") {
    openRegister(lineStream, mode);
  } else if (operation == "close") {
    closeRegister(lineStream, mode);
  } else {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream &lineStream, string mode) {
  int ID;
  double secPerItem, setupTime, timeElapsed;
  // convert strings to int and double
  if (!getInt(lineStream, ID) || !getDouble(lineStream, secPerItem) ||
      !getDouble(lineStream, setupTime) ||
      !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Check if the register is already open
  // If it's open, print an error message
  // Otherwise, open the register
  // If we were simulating a single queue, 
  // and there were customers in line, then 
  // assign a customer to the new register
  Register* pr = registerList->get_head();
  while(pr != nullptr){//check if the register is already open
    if(ID == pr->get_ID()){
      cout << "Error:" << " register " << ID << "is already open" << endl;
      return;
    }
    pr = pr->get_next();
  }
  expTimeElapsed += timeElapsed;
  departingCustomers(expTimeElapsed, mode);
  //print();
  Register* new_register = new Register(ID, secPerItem, setupTime, expTimeElapsed);
  registerList->enqueue(new_register);
  cout << "Opened register " << ID << endl; // opened new register and printed out the message
  if(mode == "single"){
    if(singleQueue->get_head() != nullptr){
      cout << "Queued a customer with free register " << registerList->get_free_register()->get_ID() << endl; // there are customers waiting in the single queue
      new_register->get_queue_list()->enqueue(singleQueue->dequeue());
      //print();
      return; // assigns the first customer in the single queue to the queue_list of the register
    }
    return;
  }
}

void closeRegister(stringstream &lineStream, string mode) {
  int ID;
  double timeElapsed;
  // convert string to int
  if (!getInt(lineStream, ID) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }
  // Check if the register is open
  // If it is open dequeue it and free it's memory
  // Otherwise, print an error message
  Register* pr = registerList->get_head();
  while(pr!=nullptr){
    if(ID == pr->get_ID()){
      expTimeElapsed += timeElapsed;
      departingCustomers(expTimeElapsed, mode);
      cout << "Closed register " << ID << endl;
      Register* dequeued_register = registerList->dequeue(ID);
      delete dequeued_register;
      dequeued_register = nullptr;
      //print();
      return;
    }
    pr = pr->get_next();
  }
  cout << "Error: " << "register " << ID << " is not open" << endl;
  return;
}

bool getInt(stringstream &lineStream, int &iValue) {
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream &lineStream, double &dvalue) {
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream &lineStream) {
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  } else {
    return true;
  }
}

bool check_depart_customer(double curTime, double& minTime){ //return true if there is a register with a head customer whose departing time is larger or equally to 0 and smaller or equal to curTime
  Register* pr = registerList->get_head();
  double min_Time = 100000000000000;
  while(pr!=nullptr){
    if((pr->calculateDepartTime() > 0) && (pr->calculateDepartTime() < min_Time)){
      min_Time = pr->calculateDepartTime();
    }
    pr = pr->get_next();
  }
  // we are guaranteed that min_Time is a positive number (empty customer queues ignored)
  if(min_Time <= curTime){
    minTime = min_Time;
    return true;
  }
  return false;
}
void departingCustomers(double curTime, string mode){
  // iterate through the registerList and find the smallest departure time that is smaller than curTime (meaning the head of a certain register is ready to be
  // departed), depart the customer, make the customer following it (if any) head. Iterate through the registerList again, find the smallest departure time and depart customer...

  // curTime is the current time, if the departure time of a customer <= curTime, they are ready to be departed
  double minTime;
  while(check_depart_customer(curTime, minTime)){ // while there are more customers to depart, and minTime is updated
    Register* pr = registerList->get_head();
    while(pr!=nullptr){
      if(pr->calculateDepartTime() == minTime){
        cout <<"Departed a customer at register ID " << pr->get_ID() << " at " << minTime << endl; // depart the customer
        pr->departCustomer(doneList);
        push_single_queue(mode);
      }
      pr = pr->get_next();
    }
  }
  return;
}

void push_single_queue(string mode){
  if(mode == "single"){
    while(registerList->get_free_register()!=nullptr){ // means that there is a register that has no customer
      if(singleQueue->get_head()!=nullptr){
        cout << "Queued a customer with free register " << registerList->get_free_register()->get_ID() << endl; // while there are free registers to append new customers
        registerList->get_free_register()->get_queue_list()->enqueue(singleQueue->dequeue());
      } else {
        return;
      }
    }
  return;
}
}

void print(){
  cout << "Current time is: " << expTimeElapsed << endl;
  cout << "------------------------------------------" << endl;
  cout << "register list: " << endl;
  registerList->print();
  cout << "------------------------------------------" << endl;
  cout << "single queue: " << endl;
  singleQueue->print();
  cout << "------------------------------------------" << endl;
  cout << "done list: " << endl;
  doneList->print();
  cout << "------------------------------------------" << endl;
}