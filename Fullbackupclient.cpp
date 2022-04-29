#include <iostream>
using namespace std;
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include<errno.h>
char filename[20];

void sendfromdirectory(char *directory,int sd)   				// directory = source , sd =socket
{
        
        //string indir[]={};
        int i=0 ,n;
        char buf[220];
	DIR* dir=opendir(directory);
	if(dir==NULL)
	{
	exit(1);
	}
	struct dirent* entity;
	entity=readdir(dir);
	while(entity!=NULL)
	{
	if(strcmp(entity->d_name,".")==0)
	continue;
	
  	else
	if(entity->d_type==DT_DIR)
	{
	cout<<"Sub Directory :"<<entity->d_name<<endl;
	}
	
	else
	{
	cout<<"Normal files : "<<entity->d_name<<endl;
	strcpy(filename,entity->d_name);  
	int fd=open(filename,O_RDONLY);       						// Opening file in directry	       
	send(sd,filename,20,0);							// Second Sending file name			
	while ( (n=read(fd,buf,sizeof(buf)))>0)
    {  write(sd,buf,strlen(buf));
       bzero(buf, sizeof(buf));
    }
	}
	entity=readdir(dir);
	}
			
	close(sd);
}



int main(int argc , char *argv[])
{
        char dest[80];
	int sd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in sockaddr_serv;
	sockaddr_serv.sin_family=AF_INET;
	sockaddr_serv.sin_port=8988;
	sockaddr_serv.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(sd,(struct sockaddr *)&sockaddr_serv,sizeof(sockaddr_serv));
	socklen_t len = sizeof(sockaddr_serv);
	if (connect(sd,(struct sockaddr *)&sockaddr_serv,len)==-1)
	{
		perror("connect error");
		exit(1);
	}
cout<<"Connecting -------"<<endl;

	if (strcmp(argv[1],"-f")==0) 								// Checking argument
	{
	for(int arg=2;arg<argc;arg++)								//Checking for mulitbackup
	{
	strcpy(dest,argv[arg]);
	int fd=open(argv[arg],O_RDONLY);
	cout<<"Path sending to server : "<<dest<<endl;
	send(sd,dest,strlen(dest),0); 								// 1st send to send folder name
	sendfromdirectory(argv[arg],sd);
	}
		}
	
	close(sd);
}
	
