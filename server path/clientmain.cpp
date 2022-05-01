#include "clientheader.h" 

int main(int argc , char *argv[])
{	

	ofstream fout;
	fout.open("client.log", ios::app);
	
	fout<<"[INFO] : Socket Create"<<endl;
	
	//create Socket
	int sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd==-1)
	{
		fout<<"[ERROR] : Socket Create "<<endl;
		perror("Error Create Socket ");
		exit(1);
	}
	
	
	//Initialization
	fout<<"[INFO] : Sockaddr_in Initialization "<<endl;
	struct sockaddr_in sockaddr_serv;
	sockaddr_serv.sin_family=AF_INET;
	sockaddr_serv.sin_port=9888;
	sockaddr_serv.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	//Connecting with Server
	socklen_t len = sizeof(sockaddr_serv);
	if (connect(sd,(struct sockaddr *)&sockaddr_serv,len)==-1)
	{	
		fout<<"[ERROR] : Connect to server "<<endl;
		perror("Error connect to Server : ");
		exit(1);
	}


	if (strcmp(argv[1],"-f")==0)
	{
		for(int i=2;i<argc;i++)
		{
		
		
		cout<<"-----------------------------------"<<endl;
			cout<<"Argument no : "<<i<<" Source Directory    "<<argv[i]<<endl;
			
		cout<<"-----------------------------------"<<endl;
		fout<<"[INFO] : Calling Function : sendfromdirectory "<<endl;
			sendfromdirectory(argv[i],sd);
			
		}
		
	}
	fout.close();
	close(sd);
	
}
