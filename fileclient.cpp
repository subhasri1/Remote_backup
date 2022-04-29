#include "clientheader.h"

int fd;
char filename[20];
void transact_with_serv(int sock);

   int main(int argc, char *argv[ ])
   {
	   //create socket
	   struct sockaddr_in  serv;
	   int sd = socket (AF_INET, SOCK_STREAM, 0);
	   //port = atoi(argv[2]);  
	   
	   
	   //initiallize of socket                    
	   struct sockaddr_in  sockaddr_serv;
	   memset( & sockaddr_serv, 0, sizeof( struct sockaddr_in ) );
	   sockaddr_serv.sin_family = AF_INET;
	   sockaddr_serv.sin_port = 8898;
	   sockaddr_serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	   //sockaddr_serv.sin_port = htons (port);


	   strcpy(filename,argv[1]);
	   fd=open(filename,O_RDONLY);
	   
	   //Connect with server
	   connect (sd, (struct sockaddr*)& sockaddr_serv, sizeof( sockaddr_serv));
	  
	    
	   transact_with_serv(sd);
	   close(sd);
   }
 void transact_with_serv(int sock)
 {
	    char buf[220];
	    char msg[50];
	    int  n;
	    cout<<"filename "<<filename<<endl;
	    int m= write(sock,&filename,sizeof(filename));
	    bzero(msg,sizeof(msg));
	    read(sock,msg,sizeof(msg));
	    cout<<msg<<endl;
	    if(m==-1)
	    {
	    	perror("Error filename write : ");
	    	exit(1);
	    }
	    bzero(buf, sizeof(buf));
	    while ( (n=read(fd,buf,sizeof(buf)))>0)
	    {  
	       write(sock,&buf,sizeof(buf));
	       bzero(buf, sizeof(buf));
	       n=read(fd,&buf,sizeof(buf));

	    }
 }

