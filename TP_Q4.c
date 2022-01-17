#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> 
#include <time.h>
#include <sys/types.h>

#define BUF_SIZE 100
#define READSIZE 50
#define PROMPTSIZE 50

const char* welcome = "Bienvenue dans le Shell ENSEA\nPour quitter, tapez 'exit'. \n";
const char* prompt ="enseash %";


void checkStatus(int status){
	char *prompt_retour=malloc(PROMPTSIZE);
	
	//code de retour
	if (WIFEXITED(status)){
		sprintf(prompt_retour, "ensea [exit:%d] %% ", WEXITSTATUS(status));
	}
	//signal	
	else if (WIFSIGNALED(status)) {
		sprintf(prompt_retour, "ensea [sign:%d] %% ", WTERMSIG(status));
	}

	else {
		sprintf(prompt_retour,"ensea %% ");
	}
	
	write(STDOUT_FILENO, prompt_retour, strlen(prompt_retour));
}

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
			status = execlp(buf, buf, (char *)NULL);
			exit (-1) ;
		}
		
		if(strncmp(buf,"exit",strlen("exit")) == 0){//exit
			break;
			}
			
		checkStatus(status); 
	}
	
	write(1,"Bye bye...\n",11);
	
	exit(EXIT_SUCCESS);
}



