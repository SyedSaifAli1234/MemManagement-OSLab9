#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
using namespace std;


int main(){

	char filename[13]="./myfile.txt";
	char filename2[14]="./myfile2.txt";
	int fd=open(filename, O_RDONLY);
	int fd2=open(filename2, O_RDWR);

	if (fd==-1){
		cout<<"File could not open!"<<endl;
		return 1;
	}
	if (fd2==-1){
		cout<<"File2 could not open!"<<endl;
		return 1;
	}

	char *map= (char*) mmap(NULL, 100, PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	char *map2= (char*) mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
	close(fd2);

	if (map==MAP_FAILED){
		cout<<"File could not be memory mapped!"<<endl;
		return 1;
	}
	if (map2==MAP_FAILED){
		cout<<"File2 could not be memory mapped!"<<endl;
		return 1;
	}

	for (int i=0; map[i]!='\0'; i++){
		if(map[i] >= 48 && map[i] <= 57){
			cout<<map[i]<<endl;
		}
	}

	FILE *fp;
	fp = fopen("./myfile2.txt", "w+");

	for (int i=0; map[i]!='\0'; i++){
		if(map[i] >= 48 && map[i] <= 57){
			fputc(map[i], fp);
		}
	}
	

	munmap(map, 100);
	munmap(map2, 100);

}


