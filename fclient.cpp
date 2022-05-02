#include "fclient.h"

void sendfromdirectory(char *directory,int sd)
{
	char buf[100];
	struct dirent *dir;
	char path[50]="";  
	strcat(path,"/home/sagar/new/"); 
	char  tempdir[30],targetdir[30];
	strcpy(tempdir,directory);         				 //directory ->  /home/sagar/new/
	char *str=strtok(tempdir,"/");            
	char *tok=str;  
	               
	while(str!=NULL)               				  //home/sagar/new/
	{                                     
	tok=str;
	str=strtok(NULL,"/");        					  // new
	}
	strcat(path,tok);						 // /home/sagar/etc/new   
	strcat(path,"/");						//  /home/sagar/etc/new/
	
	DIR *d=opendir(directory);     				//  /home/sagar/new/
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
			 	strcat(fpath,directory);         			 //  /home/sagar/new/
			 	strcat(fpath,dir->d_name);      			 // /home/sagar/new/file1.txt
			 	cout <<"Files to be backedup : "<<fpath << endl;
			 	
			 	int fd = open(fpath,O_RDONLY);
			 	
				
				send(sd,"filename",9,0);                      		 //handshaking
				recv(sd,msg,sizeof(msg),0);                    	//Recieving confirmation 
				bzero(msg,sizeof(msg));
				
			        send(sd,tok,sizeof(tok),0);              		 //Sending folder name
				recv(sd,msg,sizeof(msg),0);            		 //recieving msg
				
				
				
				
				
				send(sd,dir->d_name,strlen(dir->d_name),0);    	//Send filename
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
