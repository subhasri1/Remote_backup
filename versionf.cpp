//#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>
#include<sys/sysmacros.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <iostream>
using namespace std;
int socket_desc ,client_sock, client_size, choice;

void write_file(int socket_desc)
{
	int n;
	FILE *fc;
	char *filename = "recv.txt";
	char buffer[1024];

	fc = fopen(filename, "w");
	while(1)
	{
		n= recv(socket_desc, buffer, 1024, 0);
        	if(n<=0){
			break;
			return;
	}
		fprintf(fc, "%s", buffer);
         	bzero(buffer, 1024);
	}
	return;
}

int Incre_backup()
{
	FILE *fp;
	char lastb[30];
	long lastbint;
	struct stat sb;
	time_t a,b;
	stat("folder12.txt",&sb);
	b= time(&a);

	fp = fopen("lastbackuptime","r");
	fgets(lastb,30,fp);
	fclose(fp);
        lastbint=atol(lastb);

	fp = fopen("lastbackuptime","w");
	fprintf(fp,"%ld\n",b);
	fclose(fp);

	cout<<" time is :%ld\n"<<sb.st_mtime;
	cout<<" Modified Time :%ld\n"<<b;

	if(sb.st_mtime>lastbint)
	{
		cout<<" Backup Required"<<endl;
		
//		printf(">> Data Written In The File Successfully....\n");
		write_file(client_sock);
	}
	else{
		cout<<" NO BACKUP IS REQUIRED"<<endl;
	}
	return 0;
}

 int main()
{

	int socket_desc ,client_sock, client_size, choice;
	struct sockaddr_in server_addr, client_addr;
	char server_msg[1024], client_msg[1024];
        char buffer[1024];

	memset(server_msg, '\0', sizeof(server_msg));
	memset(client_msg, '\0', sizeof(client_msg));


 	socket_desc = socket(AF_INET, SOCK_STREAM,0);
        if(socket_desc ==-1)
	{
		perror("failed in socket\n");
		exit(1);
	}
	cout<<">> Socket is created successfully"<<endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8011);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
        if(listen(socket_desc,5) != 0)
	{
		perror(" failed in listen\n");
		exit(1);
	}
	cout<<">> Listening...."<<endl;

	client_size = sizeof(client_addr);
        client_sock = accept(socket_desc,(struct sockaddr*)&client_addr, &client_size);
yeah:
	

	cout<<"\n 1.Full backup\n 2.Incremental Backup\n 3.Justintime Backup\n 4.Exit\n";
	cout<<"Enter the choice : ";
	scanf("%d"&choice);
	printf("\n");
	switch(choice)
	{
		case 1: write_file(client_sock);
	                cout<<">> Data written in the file successfully.."<<endl;
			break;
		case 2: Incre_backup();
                  	cout<<">> Data written in the file successfully.."<<endl;
			break;
		case 3: write_file(client_sock);
                  	cout<<">> Data written in the file successfully.."<<endl;
			break;
		case 4: goto exit;
		        	
              default :	cout<<">> INVALID CHOICE"<<endl;
	}
	goto yeah;
exit:
	cout<<">> Connection is Close Now"<<endl;

	return 0;
}
