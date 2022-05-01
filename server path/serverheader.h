#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <wait.h>
#include <signal.h>
#include <fcntl.h>
#include <cstring>
#include <fstream>
void transact_with_client(char * backup_dir,int sock);
