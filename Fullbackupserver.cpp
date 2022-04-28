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
#include <sys/stat.h>
#include <wait.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include<cstring>
void makedir(char *directory);
void transact_with_client(int sock);

int main()
{
	int serv_fd = socket(AF_INET,SOCK_STREAM,0);				//socket creation
	if (serv_fd == -1)
	{
		perror("socket creation error");
		exit(1);
	}
	cout<<"Socket is created "<<endl;
	
	
	
	struct sockaddr_in sock_addr_serv;				 //initialize the sockaddr_in structure
	sock_addr_serv.sin_family = AF_INET;
	sock_addr_serv.sin_port = 8988;
	sock_addr_serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	
	//bind the socket with ip address and port
	if (bind(serv_fd,(struct sockaddr *)&sock_addr_serv,sizeof(sock_addr_serv))==-1)
	{
		perror("bind error");
		exit(1);
	}
	cout<<"Binding -----------"<<endl;
	
	
	
	// listening (waiting) for client request
	if (listen(serv_fd,5)==-1)
	{
		perror("Listen error");
		exit(1);
	}
	else cout<<"Listening -----------"<<endl;
	cout << "Server waiting for client to connect"  << endl;
		
		struct sockaddr_in sock_addr_cli;
		socklen_t cli_len = sizeof(sock_addr_cli);
		int client_fd=accept(serv_fd,(struct sockaddr *)&sock_addr_cli,&cli_len);
	 	if (client_fd==-1)
		{
			perror(" accept error");
			exit(1);
		}
		cout<<"Accepting -----------"<<endl;
		transact_with_client(client_fd);
		close(client_fd);
	
	
}

void makedir(char *directory)
{
char buf[100];
	char path[50]=""; 
	strcat(path,"/home/sagar/etc/");  
	char  tempdir[30],targetdir[30];
	strcpy(tempdir,directory);          
	char *str=strtok(tempdir,"/");            
	char *tok=str;
	while(str!=NULL)                
	{                                     
	tok=str;				
	str=strtok(NULL,"/");          
	}
	strcat(path,tok);
		cout<<"PAth is : " <<path<<endl;	
	mkdir(path,0777);              
	strcat(path,"/");

}

void transact_with_client(int sock)
{
     char target_filename[60] , filename[20];
     int  n;
     char buf[25];
     n=recv(sock,buf,25,0); 						// First receieve folder name from client
     buf[n]='\0';
     strcpy(target_filename,buf);
     cout<<"Target Folder name to be created at server   : "<<target_filename<<endl;
     makedir(target_filename); 					//Making Directry in server 
      struct dirent *dir;
     DIR *d=opendir(target_filename);   // Opening directry
     if(d)
     {
     int fd, fr;
     char temp[25];
     fr=recv(sock,temp,strlen(temp),0); // Second receieve for Filename
     temp[fr]='\0';
     strcpy(filename,temp);
     strcat(filename,"/");
     fd=open(filename,O_WRONLY|O_CREAT,0660); // opening filename 
     
     while ( (fr = read(sock, temp, sizeof(temp))) > 0) // Reading file content from Client
	{
	write(fd,temp,fr); 
        strcpy(temp,""); 
        }
     } 
    
    close(sock);
  
  
}

	

