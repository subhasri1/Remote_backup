   #include "fserver.h"
   
   
  void transact_with_client(char * backup_dir, int sock)
{
	char ch[100], direc[100];
	int fd;
	int n =read(sock,ch,sizeof(ch));                                 			   // Recieving "filename"
	while(n!=0)
	{
	
		send(sock,"Handshaking Completed",21,0);                  			   //Send Confirmation
		
		
	//**************************************************************	
		
		bzero(direc,sizeof(direc));
		read(sock,direc,sizeof(direc));                				//Reading folder name
	
		send(sock,"Folder Recieved",15,0);             				//Send Confirmation 
		
		
		if (strcmp(ch,"filename")==0)
		{
			char fn[30];
			
			bzero(fn,sizeof(fn));
			n=read(sock,fn,sizeof(fn));         				    	//fn = file name
			
			
			
			
			
			
			cout << "File Name : " << fn << endl;
			send(sock,"Received",8,0);
			
			
			cout<<"-----------------------------------"<<endl;
			
			string st = (char*)fn;			          			// st contains file name
			string ch = (char*)direc;     		   				// ch contains Folder name
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

