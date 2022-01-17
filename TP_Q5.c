#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> 
#include <time.h>
#include <sys/types.h>

#define BUF_SIZE 100
#define PROMPTSIZE 50
#define MILLION 1000000

const char* welcome = "Bienvenue dans le Shell ENSEA\nPour quitter, tapez 'exit'. \n";
const char* prompt ="enseash %";


void checkStatus(int status, struct timespec * start, struct timespec * stop){
	
	char *prompt_retour=malloc(PROMPTSIZE);
	double duration = (stop->tv_nsec - start->tv_nsec)/MILLION;//declaration de la variable de duree
	
	//code de retour
	if (WIFEXITED(status)){
		sprintf(prompt_retour, "ensea [exit:%d|%.0lf ms] %% ", WEXITSTATUS(status),duration);
	}
	//signal	
	else if (WIFSIGNALED(status)) {
		sprintf(prompt_retour, "ensea [exit:%d|%.0lf ms] %% ", WTERMSIG(status),duration);
	}

	else {
		sprintf(prompt_retour,"ensea %% ");
	}
	
	write(STDOUT_FILENO, prompt_retour, strlen(prompt_retour));
}


int main(void) {
	
	struct timespec tmps_start, tmps_stop;//declaration des variables pour calculer le temps
	int status;
	
	write ( STDOUT_FILENO , welcome, strlen(welcome) );
	write ( STDOUT_FILENO , prompt, strlen(prompt) );
	
	
	while(1){
		char* buf =malloc(BUF_SIZE);
		int valeur =read (STDIN_FILENO, buf, BUF_SIZE);
		buf[valeur-1]=0;	
		
		
		clock_gettime(CLOCK_REALTIME, &tmps_start);//calcul de la valeur start
		
		pid_t pid = fork();
		if( pid != 0){ //pere
						
			wait(&status);
			clock_gettime(CLOCK_REALTIME, &tmps_stop);//calcul de la valeur stop
						
		}
		else {//fils
			status = execlp(buf, buf, (char *)NULL);
			exit (EXIT_FAILURE) ;
		}
		
		checkStatus(status,&tmps_start, &tmps_stop);
		
		if(strncmp(buf,"exit",strlen("exit")) == 0){//exit
			break;
			}		
		 
	}
	
	write(1,"Bye bye...\n",11);
	
	exit(EXIT_SUCCESS);
}

