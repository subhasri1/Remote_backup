#include "serverheader.h"

int main(int argc, char * argv[])
{

	//log file 
	ofstream fout;
	fout.open("server.log", ios::app);
	fout<<"[INFO] : Socket Create"<<endl;
	
	//socket creation
	int serv_fd = socket(AF_INET,SOCK_STREAM,0);
	if (serv_fd == -1)
	{
		fout<<"[ERROR] : Socket Create"<<endl;
		perror("Error socket create : ");
		exit(1);
	}
	
	
	fout<<"[INFO] : Sockaddr_in Initialization "<<endl;
	//initialize the sockaddr_in structure
	struct sockaddr_in sock_addr_serv;					// sockaddr_in for IPV4
	sock_addr_serv.sin_family = AF_INET;
	sock_addr_serv.sin_port = 9888;
	sock_addr_serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	
	fout<<"[INFO] : Binding Socket with IP "<<endl;
	//bind the socket with ip address and port
	if (bind(serv_fd,(struct sockaddr *)&sock_addr_serv,sizeof(sock_addr_serv))==-1)
	{
		fout<<"[ERROR] : Binding Socket with IP "<<endl;
		perror("Error binding : ");
		exit(1);
	}
	
	
	fout<<"[INFO] : Server Waiting For client "<<endl;
	// listening (waiting) for client request
	if (listen(serv_fd,5)==-1)
	{
		fout<<"[ERROR] : Server Waiting For client "<<endl;
		perror("Error listen/waiting : ");
		exit(1);
	}
	
	
	
		cout << "Server waiting for client to connect"  << endl;
		
		
		fout<<"[INFO] : Accept Client Request "<<endl;
		//accepting client request
		struct sockaddr_in sock_addr_cli;
		socklen_t cli_len = sizeof(sock_addr_cli);
		int client_fd=accept(serv_fd,(struct sockaddr *)&sock_addr_cli,&cli_len);
	 	if (client_fd==-1)
		{
			fout<<"[ERROR] : Accept Client Request "<<endl;
			perror(" Error Accept Client Request : ");
			exit(1);
		}
		
		fout<<"[INFO] : Calling Transact_with_client function "<<endl;
	while (1)
	{
		
		transact_with_client(argv[1],client_fd);
	}
		fout.close();

}
