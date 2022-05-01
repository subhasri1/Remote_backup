all:client server
server:Server.cpp
	g++ -o server Server.cpp
client: Client.cpp
	g++ -o client Client.cpp
