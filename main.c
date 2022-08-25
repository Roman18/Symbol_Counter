#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>

#define ALPHA_SIZE 26
#define NUM_SIZE 10
#define LIMIT 1024
 

uint32_t lower_case[ALPHA_SIZE] = {0};
uint32_t upper_case[ALPHA_SIZE] = {0};
uint32_t numeric[NUM_SIZE] = {0};


void usage(int argc, const char *argv){

        if(argc < 2){
               fprintf(stderr, "Usage: %s <filename>\n", argv);
               exit(EXIT_FAILURE);
            }

}

size_t get_size(FILE *f){

        size_t size = 0;
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        return size;
}

void count_charater(uint8_t buff[]){
	
	uint32_t tmp;
	for(int i = 0; buff[i] != '\0'; i++){
                    if(isdigit(buff[i])){
                    	tmp = buff[i] - '0';
                    	numeric[tmp] += 1;  
                    }else if(islower(buff[i])){
                    	tmp = buff[i] - 'a';
                    	lower_case[tmp] += 1;	
                    }else if(isupper(buff[i])){
                    	tmp = buff[i] - 'A';
                    	upper_case[tmp] += 1;	
                    }  
	}
}

void show_res(){

	for(int i = 0; i < 26; ++i){
		if (i>=NUM_SIZE){
		
			printf("        \t\t%c -> %3u\t\t%c -> %3u\n", i+'A', upper_case[i], i+'a', lower_case[i]);
		}else{
                	printf("%c -> %3u\t\t%c -> %3u\t\t%c -> %3u\n", i+'0', numeric[i], i+'A', upper_case[i], i+'a', lower_case[i]);
                }
            }

}


int main(int argc, char *argv[]){
	
	
	
        usage(argc, argv[0]);
	
	time_t t = time(NULL);
        uint8_t buff[LIMIT];
        
        FILE *f = fopen(argv[1], "r");

        if(f == NULL){
                fprintf(stderr, "Could not open the file: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
        printf("%s\n", ctime(&t));
        printf("Name: %s\nSize of file: %ld bytes\n\n",argv[1], get_size(f));
        
        while(!feof(f)){
              fread(buff, LIMIT, 1, f);
              count_charater(buff);
        }
        
        show_res();
        
        return EXIT_SUCCESS;

    }