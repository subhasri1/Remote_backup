#include "fclient.h"

int main(int argc , char *argv[])
{
	int sd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in sockaddr_serv;
	sockaddr_serv.sin_family=AF_INET;
	sockaddr_serv.sin_port=9800;
	sockaddr_serv.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(sd,(struct sockaddr *)&sockaddr_serv,sizeof(sockaddr_serv));

	socklen_t len = sizeof(sockaddr_serv);
	if (connect(sd,(struct sockaddr *)&sockaddr_serv,len)==-1)
	{
		perror("Connect error");
		exit(1);
	}


	if (strcmp(argv[1],"-f")==0)                                                     //Checking command line have "-f" or not
	{
		for(int i=2;i<argc;i++)                                                  //Checking number of source directrory
		{
		
		
		cout<<"-----------------------------------"<<endl;
			cout<<"Argument no : "<<i<<" Source Directory    "<<argv[i]<<endl;
			
		cout<<"-----------------------------------"<<endl;
			sendfromdirectory(argv[i],sd);
			
		}
		
	}
	close(sd);
}
	
