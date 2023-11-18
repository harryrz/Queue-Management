SRCS = Customer.cpp QueueList.cpp  Register.cpp  RegisterList.cpp main.cpp
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

main:	main.o Customer.o QueueList.o Register.o RegisterList.o
	g++ -std=c++11 $^ -o $@
main.o:	main.cpp
	g++ -std=c++11 -c -g main.cpp Customer.h QueueList.h Register.h RegisterList.h
Customer.o:	Customer.cpp Customer.h
	g++ -std=c++11 -c -g Customer.cpp
QueueList.o:	QueueList.cpp Customer.h Customer.h
	g++ -std=c++11 -c -g QueueList.cpp
Register.o:	Register.cpp Register.h
	g++ -std=c++11 -c -g Register.cpp
RegisterList.o:	RegisterList.cpp Register.h RegisterList.h
	g++ -std=c++11 -c -g RegisterList.cpp
clean:
	rm -f *.o  main core

