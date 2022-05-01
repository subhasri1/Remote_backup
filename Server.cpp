#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <wait.h>
#include <signal.h>
#include <fcntl.h>
#include <cstring>
        // concurrent server

void transact_with_client(char * backup_dir,int sock);

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
	struct sockaddr_in sock_addr_serv;					// sockaddr_in for IPV4
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
void transact_with_client(char * backup_dir, int sock)
{
	char ch[100], direc[100];
	int fd;
	int n =read(sock,ch,sizeof(ch));                                    // Recieving "filename"
	while(n!=0)
	{
	
		send(sock,"Handshaking Completed",21,0);                     //Send Confirmation
		
		
	//**************************************************************	
		
		bzero(direc,sizeof(direc));
		read(sock,direc,sizeof(direc));                				//Reading folder name
	
		send(sock,"Folder Recieved",15,0);             				//Send Confirmation 
		
		
		if (strcmp(ch,"filename")==0)
		{
			char fn[30];
			
			bzero(fn,sizeof(fn));
			n=read(sock,fn,sizeof(fn));         		    	//fn = file name
			
			
			
			
			
			
			cout << "File Name : " << fn << endl;
			send(sock,"Received",8,0);
			
			
			cout<<"-----------------------------------"<<endl;
			
			string st = (char*)fn;			          // st contains file name
			string ch = (char*)direc;     		   // ch contains Folder name
			string path = (char*)backup_dir;			
			
			string makedir=path+ch;
			
			mkdir(makedir.c_str(),0777);
			st=path+ch+"/"+st;    					
			cout<<"full path of file to be backedup is : "<<st<<endl;			
			bzero(direc,sizeof(direc));
			
			cout<<"-----------------------------------"<<endl;
			
			
			strcpy(fn,st.c_str());
			fd = open(fn,O_CREAT|O_WRONLY,0777);
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
}


	

