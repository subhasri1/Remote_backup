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

void sendfromdirectory(char *directory,int sd)
{
	char buf[100];
	struct dirent *dir;
	char path[50]="";  
	strcat(path,"/home/sagar/etc/"); 
	char  tempdir[30],targetdir[30];
	strcpy(tempdir,directory);         			 //directory ->  /home/raajpatel/Music/
	char *str=strtok(tempdir,"/");            
	char *tok=str;  
	               
	while(str!=NULL)               			  //home/raajpatel/Music/
	{                                     
	tok=str;
	str=strtok(NULL,"/");        				  // Music
	}
	strcat(path,tok);					 // /home/raajpatel/masterbackup/Music/     
	strcat(path,"/");						//  /home/raajpatel/Masterbackup/Music/
	
	DIR *d=opendir(directory);     //  /home/raajpatel/Desktop/Testdit/
	if (d)
	{
		char msg[25];
		while((dir=readdir(d))!=NULL)
		{       
			   
			if ( (strcmp(dir->d_name,".")==0) || (strcmp(dir->d_name,"..")==0))
			 {	
			         continue;      
     
			  }
			  
			  
			 else 	 if(dir->d_type==DT_DIR)     				 //Checking for directory
		
				{	
					cout<<"Sub Directory :"<<dir->d_name<<endl;						
				}
					 
			 else
			 {
			 	char fpath[50]="";
			 	strcat(fpath,directory);         		//  /home/raajpatel/Music/
			 	strcat(fpath,dir->d_name);      		 // /home/raajpatel/Music/file3
			 	cout <<"Files to be backedup : "<<fpath << endl;
			 	
			 	int fd = open(fpath,O_RDONLY);
			 	
				
				send(sd,"filename",9,0);                       //handshaking
				recv(sd,msg,sizeof(msg),0);                    //Recieving confirmation 
				bzero(msg,sizeof(msg));
				
			        send(sd,tok,sizeof(tok),0);              	 //Sending folder name
				recv(sd,msg,sizeof(msg),0);            	 //rec msg
				
				
				
				
				
				send(sd,dir->d_name,strlen(dir->d_name),0);    //Send filename
				recv(sd,msg,sizeof(msg),0);
				
				if(fd) 					
				{
				 int n = read(fd,buf,sizeof(buf));
				 while(n!=0)
				 {
				 	
				 	send(sd,buf,n,0);
				 	recv(sd,msg,sizeof(msg),0);
				 	bzero(buf,sizeof(buf));
				 	n = read(fd,buf,sizeof(buf));
				 	buf[n]='\0';
				 }
				 }
				 else
				 {
				 cout<<"Error in opening files : " <<endl;
				 }
				 send(sd,"end",3,0);
				recv(sd,msg,sizeof(msg),0);
				 close(fd);
			}
		}
	}
	else
	cout<<"Error in opening source directory " <<endl;
}

int main(int argc , char *argv[])
{
	int sd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in sockaddr_serv;
	sockaddr_serv.sin_family=AF_INET;
	sockaddr_serv.sin_port=9888;
	sockaddr_serv.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(sd,(struct sockaddr *)&sockaddr_serv,sizeof(sockaddr_serv));

	socklen_t len = sizeof(sockaddr_serv);
	if (connect(sd,(struct sockaddr *)&sockaddr_serv,len)==-1)
	{
		perror("Connect error");
		exit(1);
	}


	if (strcmp(argv[1],"-f")==0)
	{
		for(int i=2;i<argc;i++)
		{
		
		
		cout<<"-----------------------------------"<<endl;
			cout<<"Argument no : "<<i<<" Source Directory    "<<argv[i]<<endl;
			
		cout<<"-----------------------------------"<<endl;
			sendfromdirectory(argv[i],sd);
			
		}
		
	}
	close(sd);
}
	
