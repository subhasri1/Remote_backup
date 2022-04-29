#include "serverheader.h"

  int main()
  {
	    //create socket
	    int sd = socket(AF_INET, SOCK_STREAM, 0);   // domain, Type of connection, protocol
	    if(sd == -1)
	    {
		perror("Error socket create : ");
		exit(1);
	    }
	    
	    //Initiallization of socket
	    struct sockaddr_in sockaddr_serv, sockaddr_cli;
	    sockaddr_serv.sin_family = AF_INET;
	    sockaddr_serv.sin_port=8898; 
	    //sockaddr_serv.sin_port = htons (port);
	    sockaddr_serv.sin_addr.s_addr =inet_addr("127.0.0.1");
	    //int port = atoi(argv[1]); 
    
    
	    //Bind socket with IP address
	    if (bind (sd, (struct sockaddr*)&sockaddr_serv, sizeof (sockaddr_serv))==-1)
	    {
		perror("Error socket bind : ");
		exit(1);
	    }
	    
	    
	    //litnening (waiting) for the client to connect
	    if (listen(sd,5)==-1)
	    {
		perror("Error client listen : ");
		exit(1);
	    } 		
  
	
  while(1)
    {
	      socklen_t cli_len = sizeof(sockaddr_cli);
	      int cd = accept (sd, (struct sockaddr*)&sockaddr_cli, &cli_len);
	      if(cd==-1)
	      {
	      	  perror("Error client accept : ");
	      	  exit(1);
	      }
	      
	      char buf[20];
	      char source_file[20];
	      char target_filename[20];
	      int  n,fd;
	      bzero(buf,sizeof(buf));
	      bzero(source_file,sizeof(source_file));
	      int m=read(cd,&source_file,sizeof(source_file));
	      source_file[m]='\0';
	      cout<<"Source file : "<<source_file<<endl;
	
	      FILE *fp;
	      char lastb[30];
	      long lastbint;
	      struct stat sb;
	      time_t a,b;
	      stat(source_file,&sb);
	      b=time(&a);                         //present time
	      
	      fp=fopen("lastbackuptime","r");
	      fgets(lastb,30,fp);
	      fclose(fp);
	      lastbint = stol(lastb);
	      fp=fopen("lastbackuptime","w");
	      fprintf(fp,"%ld\n",b);
	      fclose(fp);
	      
	      strcpy(target_filename,source_file);
	      
	      if(sb.st_mtime>lastbint)
	      {
		      cout<<"Latest data found.."<<endl;
		      write(cd,"Data writing in file...",23);
		      cout<<"Data writing in file...."<<endl;
		      bzero(source_file,sizeof(source_file));
		      fd=open(target_filename,O_WRONLY|O_CREAT,0660);
		      while ( (n = read(cd, &buf, sizeof(buf))) > 0)
			   {
				write(fd,&buf,sizeof(buf));
				bzero(buf,sizeof(buf));
				n = read(cd,&buf,sizeof(buf));
				strcpy(buf,""); 
			   }
		cout<<"Data written successful"<<endl;
		}
		else
		{
		      cout<<"No backup required "<<endl;
		      write(cd,"Backup not required",18);
		}
        }
    close(sd);
 }

           
