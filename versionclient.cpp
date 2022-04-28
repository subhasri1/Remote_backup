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
	//strcat(path,"/home/osboxes/masterbackup/");  
	strcat(path,"/home/raajpatel/Masterbackup/");  
	char  tempdir[30],targetdir[30];
	strcpy(tempdir,directory);          //directory ->  /home/raajpatel/Desktop/Testdit/
	char *str=strtok(tempdir,"/");            
	char *tok=str;
	while(str!=NULL)                 //home/raajpatel/Desktop/Testdit/
	{                                     
	tok=str;
	cout << "tok " << tok << endl;
	str=strtok(NULL,"/");          // Testdir
	}
	strcat(path,tok);		// /home/raajpatel/Masterbackup/Testdir
	mkdir(path,0660);              
	cout << path << endl;		
	//chdir(path);
	strcat(path,"/");		//  /home/raajpatel/Masterbackup/Testdir/
	DIR *d=opendir(directory);     //  /home/raajpatel/Desktop/Testdit/
	if (d)
	{
		char msg[10];
		while((dir=readdir(d))!=NULL)
		{       
			cout<<"directort test" << dir->d_name << endl;         //file3
			   
			if ( (strcmp(dir->d_name,".")==0) || (strcmp(dir->d_name,"..")==0))
			 {	
			 	cout <<". or .." << endl;           
			  }
			 else
			 {
			 	char fpath[50]="";
			 	strcat(fpath,path);         //  /home/raajpatel/Masterbackup/Testdir/
			 	strcat(fpath,dir->d_name);   // /home/raajpatel/Masterbackup/Testdir/file3
			 	cout <<"fpath "<<fpath << endl;
			 	int fd = open(fpath,O_RDONLY);
			 	perror("open file error");
				cout << fd << endl;
				send(sd,"filename",9,0);
				recv(sd,msg,sizeof(msg),0);
				send(sd,dir->d_name,strlen(dir->d_name),0);
				recv(sd,msg,sizeof(msg),0);
				 int n = read(fd,buf,sizeof(buf));
				 while(n!=0)
				 {
				 	cout << buf << endl;
				 	send(sd,buf,n,0);
				 	recv(sd,msg,sizeof(msg),0);
				 	bzero(buf,sizeof(buf));
				 	n = read(fd,buf,sizeof(buf));
				 	buf[n]='\0';
				 }
				 send(sd,"end",3,0);
				recv(sd,msg,sizeof(msg),0);
				 close(fd);
			}
		}
	}
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
		perror("connect error");
		exit(1);
	}


	if (strcmp(argv[1],"-f")==0)
	{
		for(int i=1;i<=argc-2;i++)
		{
			sendfromdirectory(argv[2],sd);
		}
		/*
		char buf[100];
		DIR *d;
		struct dirent *dir;
		d=opendir(argv[2]);
		
		if (d)
		{
			/*readdir(d);
			cout << dir->d_name << endl;
			readdir(d);
			cout << dir->d_name << endl;
			char msg[10];
			while((dir=readdir(d))!=NULL)
			{
				cout << dir->d_name << endl;
				//int n=send(sd,dir->d_name,strlen(dir->d_name),0);
				//cout << n << endl;
				//recv(sd,msg,sizeof(msg),0);
				if ( (strcmp(dir->d_name,".")==0) || (strcmp(dir->d_name,"..")==0))
				 {	cout <<". or .." << endl;           
				 
				 }
				 else
				 {
				 	int fd = open(dir->d_name,O_RDONLY);
					cout << fd << endl;
					send(sd,"filename",9,0);
					recv(sd,msg,sizeof(msg),0);
					send(sd,dir->d_name,strlen(dir->d_name),0);
					recv(sd,msg,sizeof(msg),0);
					 int n = read(fd,buf,sizeof(buf));
					 while(n!=0)
					 {
					 	cout << buf << endl;
					 	send(sd,buf,n,0);
					 	recv(sd,msg,sizeof(msg),0);
					 	bzero(buf,sizeof(buf));
					 	n = read(fd,buf,sizeof(buf));
					 	buf[n]='\0';
					 }
					 send(sd,"end",3,0);
					recv(sd,msg,sizeof(msg),0);
					 close(fd);
				}
			}
		}
		*/
	}
	close(sd);
}
	
