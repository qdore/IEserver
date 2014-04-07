CC=g++ -std=c++11
boostheader=/usr/boost/include
boostlibrary=/usr/boost/libs
install:session.o server.o main.o
	$(CC) main.o server.o session.o -I $(boostheader) -L$(boostlibrary) -lboost_system -o server
main.o:
	$(CC) main.cpp -c -I $(boostheader) -L$(boostlibrary) -lboost_system
server.o:
	$(CC) server.cpp -c -I $(boostheader) -L$(boostlibrary) -lboost_system
session.o:
	$(CC) session.cpp -c -I $(boostheader) -L$(boostlibrary) -lboost_system

clean:
	rm *.o
	rm server
