#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> 
#include <time.h>

#define BUF_SIZE 100

const char* welcome = "Bienvenue dans le Shell ENSEA\n Pour quitter, tapez 'exit'. \n";
const char* prompt ="enseash %";


int main(void) {
	
	write ( STDOUT_FILENO , welcome, strlen(welcome) );
	write ( STDOUT_FILENO , prompt, strlen(prompt) );
	while(1){
		char* buf =malloc(BUF_SIZE);
		int valeur =read (STDIN_FILENO, buf, BUF_SIZE);
		buf[valeur-1]=0;

		int pid, status;
		pid = fork();
		if( pid != 0){ //pere
			wait(&status);
		}
		else {//fils
			execlp(buf, buf, (char *)NULL);
			exit (-1) ;
		}
		
		if(strncmp(buf,"exit",strlen("exit")) == 0){//exit
			break;
			}

		write ( STDOUT_FILENO , prompt, strlen(prompt) );

	}
	
	write(1,"Bye bye...\n",11);
	
	exit(EXIT_SUCCESS);
}
