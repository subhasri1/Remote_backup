all:client server
client:fclientmain.cpp fclient.o
	g++ -o client  fclientmain.cpp fclient.o
fclient.o:fclient.cpp  fclient.h
	g++ -c fclient.cpp
server:fservermain.cpp fserver.o
	g++ -o server fservermain.cpp fserver.o
fserver.o:fserver.cpp fserver.h
	g++ -c fserver.cpp

