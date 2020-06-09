#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int result_file = open(argv[1],O_CREAT|O_WRONLY, 0600);	
	int skip_counter = 0;
	while(true){
		char str[1024];
		int bytes_count = read(0, str, 1024);
		for (int i = 0; i < bytes_count; i++){
			if(str[i] == '\0'){
				skip_counter ++;	
			}else{
				if(skip_counter != 0){
					lseek(result_file, skip_counter, SEEK_CUR);
					skip_counter = 0;
				}
				write(result_file,&str[i],1);
			}	
		}
		if(bytes_count < 1024){
			break;
		}
	}
	close(result_file);
	return 0;
}
