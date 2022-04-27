#include<iostream>
using namespace std;
int main(int argc,char *argv[])
{
string cmd = argv[1];

if(cmd=="-f")
{
 	cout<<"FULLBACK PROGRAM"<<endl;
 switch (argc)
 {
 case  2 :
 	cout<<"Source Argument missing "<<endl;
 exit(1);
 
 case 3:
 	cout<<"FULL BACKUP for DIRECTORY"<<endl;
 	
 break;
 
  default: 
 	cout<<"FULL BACKUPUP for MULTIPLE DIRECTORY"<<endl;
 
}
}
else

if(cmd=="-v")
{
 cout<<"VERSIONED BACKUP"<<endl;
 switch (argc)
 {
 case  2 :
	 cout<<"Source Argument missing "<<endl;
 	exit(1);
 
 case 3:
 	cout<<"VERSIONED BACKUP for DIRECTORY"<<endl;
 break;
 
  default: 
 	cout<<"VERSIONED BACKUPUP for MULTIPLE DIRECTORY"<<endl;

}
}

else
if(cmd=="-i")
{
 	cout<<"INCREMENTAL BACKUP"<<endl;
 switch (argc)
 {
 case  2 :
 	cout<<"Source Argument missing "<<endl;
 exit(1);
 
 case 3:
 	cout<<"INCREMENTAL BACKUP for DIRECTORY"<<endl;
 break;
 
  default: 
 	cout<<"INCREMENTAL BACKUPUP for MULTIPLE DIRECTORY"<<endl;

}
}
else
if(cmd=="-s")
{
 cout<<"SCHEDULED BACKUP"<<endl;
 switch (argc)
 {
 
case  2 :
 	cout<<"Source missing "<<endl;
 	exit(1);
 
case 3:
 	cout<<"SCHEDULED BACKUP for DIRECTORY"<<endl;
 	break;
 
default: 
 	cout<<"SCHEDULED BACKUPUP for MULTIPLE DIRECTORY"<<endl;

}
}
else
if(cmd=="-j")
{
 	cout<<"JUST IN TIME BACKUP"<<endl;
 
 switch (argc)
 
 {
case  2 :
 	cout<<"Source Argument missing "<<endl;
 	exit(1);
 
case 3:
 	cout<<"JUSTIN BACKUP for DIRECTORY"<<endl;
 	break;
 
default: 
 	cout<<"JUSTIN BACKUPUP for MULTIPLE DIRECTORY"<<endl;
 
}
}
}
