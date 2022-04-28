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
 cout<<"Source and Destination Argument missing "<<endl;
 exit(1);
 
 case 3 :
 cout<<"Destinataion Arguments missing "<<endl;
 exit(1);
 
 case 4:
 cout<<"FULL BACKUP for DIRECTORY"<<endl;
 break;
 
 case 5:
 cout<<"FULL BACKUPUP for MULTIPLE DIRECTORY"<<endl;
 break;
 
 default: 
 cout<<"INVAILD INPUTS";
}
}
else

if(cmd=="-v")
{
 cout<<"VERSIONED BACKUP"<<endl;
 switch (argc)
 {
 case  2 :
 cout<<"Source and Destination Argument missing "<<endl;
 exit(1);
 
 case 3 :
 cout<<"Destinataion Arguments missing "<<endl;
 exit(1);
 
 case 4:
 cout<<"VERSIONED BACKUP for DIRECTORY"<<endl;
 break;
 
 case 5:
 cout<<"VERSIONED BACKUPUP for MULTIPLE DIRECTORY"<<endl;
 break;
 
 default: 
 cout<<"INVAILD INPUTS";
}
}
else
if(cmd=="-i")
{
 cout<<"INCREMENTAL BACKUP"<<endl;
 switch (argc)
 {
 case  2 :
 cout<<"Source and Destination Argument missing "<<endl;
 exit(1);
 
 case 3 :
 cout<<"Destinataion Arguments missing "<<endl;
 exit(1);
 
 case 4:
 cout<<"INCREMENTAL BACKUP for DIRECTORY"<<endl;
 break;
 
 case 5:
 cout<<"INCREMENTAL BACKUPUP for MULTIPLE DIRECTORY"<<endl;
 break;
 
 default: 
 cout<<"INVAILD INPUTS";
}
}
else
if(cmd=="-s")
{
 cout<<"SCHEDULED BACKUP"<<endl;
 switch (argc)
 {
 case  2 :
 cout<<"Source and Destination Argument missing "<<endl;
 exit(1);
 
 case 3 :
 cout<<"Destinataion Arguments missing "<<endl;
 exit(1);
 
 case 4:
 cout<<"SCHEDULED BACKUP from a SPECIFIC folder  (by reading the conf file)"<<endl;
 break;
 
 case 5:
 cout<<"SCHEDULED BACKUP from a MULTIPLE folder  (by reading the conf file)"<<endl;
 break;
 
 default: 
 cout<<"INVAILD INPUTS";
}
}
else
if(cmd=="-j")
{
 cout<<"JUST IN TIME BACKUP"<<endl;
 switch (argc)
 {
 case  2 :
 cout<<"Source and Destination Argument missing "<<endl;
 exit(1);
 
 case 3 :
 cout<<"Destinataion Arguments missing "<<endl;
 exit(1);
 
 case 4:
 cout<<"JUST IN TIME BACKUP from a SPECIFIC folder "<<endl;
 break;
 
 case 5:
 cout<<"JUST IN TIME BACKUP from a MULTIPLE folder "<<endl;
 break;
 
 default: 
 cout<<"INVAILD INPUTS";
}
}
}

