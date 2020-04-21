#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
using namespace std;


int main(){
 
 char filename[13]="./myfile.txt";
 int fd=open(filename,  O_RD);
 
 if (fd==-1)
 {
   cout<<"File could not open!"<<endl;
   return 1;
 }
 
 char *map= (char*) mmap(NULL, 100, PROT_READ, MAP_SHARED, fd, 0);
 close(fd); //updated
 
 if (map==MAP_FAILED)
 {
   cout<<"File could not be memory mapped!"<<endl;
   return 1;
 }

 for (int i=0; i<10; i++)
 {
   cout<<map[i]<<endl;
 }

 map[0]='B';
 
 munmap(map, 10);


}


