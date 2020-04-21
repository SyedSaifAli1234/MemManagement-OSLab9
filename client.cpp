#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
using namespace std;




int main()
{
 
 char filename[13]="./myfile.txt";

 int fd=open(filename,  O_RDWR);

 if (fd==-1)
 {
   cout<<"File could not open!"<<endl;
   return 1;
 }

 char *map= (char*) mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
 close(fd); //updated

 if (map==MAP_FAILED)
 {
   cout<<"File could not be memory mapped!"<<endl;
   return 1;
 }

 while (map[0]=='A');
 cout<<"Data changed by server to: "<<map[0]<<endl;

 munmap(map, 10);

}


