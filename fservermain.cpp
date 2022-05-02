#include "fserver.h"

int main(int argc, char * argv[])
{
	//socket creation
	int serv_fd = socket(AF_INET,SOCK_STREAM,0);
	if (serv_fd == -1)
	{
		perror("socket creation error");
		exit(1);
	}
	
	
	//initialize the sockaddr_in structure
	struct sockaddr_in sock_addr_serv;							// sockaddr_in for IPV4
	sock_addr_serv.sin_family = AF_INET;
	sock_addr_serv.sin_port = 9800;
	sock_addr_serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	
	
	//bind the socket with ip address and port
	if (bind(serv_fd,(struct sockaddr *)&sock_addr_serv,sizeof(sock_addr_serv))==-1)
	{
		perror("bind error");
		exit(1);
	}
	
	
	
	// listening (waiting) for client request
	if (listen(serv_fd,5)==-1)
	{
		perror("listen error");
		exit(1);
	}
	
	
	
		cout << "Server waiting for client to connect"  << endl;
		
		
		
		//accepting client request
		struct sockaddr_in sock_addr_cli;
		socklen_t cli_len = sizeof(sock_addr_cli);
		int client_fd=accept(serv_fd,(struct sockaddr *)&sock_addr_cli,&cli_len);
	 	if (client_fd==-1)
		{
			perror(" accept error");
			exit(1);
		}
		
		
	while (1)
	{
		transact_with_client(argv[1],client_fd);
	}	

}
