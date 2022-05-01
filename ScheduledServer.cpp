#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <wait.h>
#include <signal.h>
#include <fcntl.h>
// concurrent server

void transact_with_client(int sock);

int main()
{
	//socket creation
	int serv_fd = socket(AF_INET,SOCK_STREAM,0);
	if (serv_fd == -1)
	{
		perror("socket creation error");
		exit(1);
	}
	//initialize the sockaddr_in structure
	struct sockaddr_in sock_addr_serv;// sockaddr_in for IPV4
	sock_addr_serv.sin_family = AF_INET;
	sock_addr_serv.sin_port = 9888;
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
	
		cout << "server waiting for client to connect"  << endl;
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
		transact_with_client(client_fd);
		//close(client_fd);
	}	
	//close socket
	/*if (close(serv_fd)==-1)
	{
		perror("socket close error");
		exit(1);
	}*/
}
void transact_with_client(int sock)
{
	char ch[100];
	int fd;
	int n =read(sock,ch,sizeof(ch));
	while(n!=0)
	{
		send(sock,"received",8,0);
		if (strcmp(ch,"filename")==0)
		{
			char fn[30];
			n=read(sock,fn,sizeof(fn));
			cout << "fn " << fn << endl;
			send(sock,"received",8,0);
			fd = open(fn,O_CREAT|O_WRONLY,0660);
			bzero(fn,sizeof(fn));
		}
		else if (strcmp(ch,"end")==0)
		{
			close(fd);
		}
		else
		{
			write(fd,ch,n);	
			bzero(ch,sizeof(ch));
		}
		n =read(sock,ch,sizeof(ch));
	}
	/*ch[n]='\0';
	int fd;
	puts(ch);
	cout << n << endl;
	send(sock,"received",8,0);
	
	if (strcmp(ch,"filename")==0)
	{
		cout << "wihtin if " << endl;
		char fn[30];
		n=read(sock,fn,sizeof(fn));
		send(sock,"received",8,0);
		fn[n]='\0';
		cout << fn << endl;
		fd = open(fn,O_CREAT|O_WRONLY,0660);
	}
	else
	{
		cout << " ESESSDEE; " << endl;
		n=read(sock,buf,sizeof(buf));
		send(sock,"received",8,0);
		cout << buf << endl;
		write(fd,buf,n);	
		bzero(buf,sizeof(buf));
	}
	bzero(ch,sizeof(ch));*/
	//close(fd);
	
}


	

