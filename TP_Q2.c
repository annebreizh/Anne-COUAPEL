#include <fcntl.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h> 
#include "string.h"

#define BUF_SIZE 100

const char* welcome = "Bienvenue dans le Shell ENSEA\n Pour quitter, tapez 'exit'. \n";
const char* prompt ="enseash %";


int main(void) {

	//accueil
	write ( STDOUT_FILENO , welcome, strlen(welcome) );
	write ( STDOUT_FILENO , prompt, strlen(prompt) );
	while(1){
		//executer une simple execution
		char* buf =malloc(BUF_SIZE);
		int valeur =read (STDIN_FILENO, buf, BUF_SIZE);
		buf[valeur-1]=0;

		int pid, status;
		pid = fork();
		if( pid != 0){//pere
			wait(&status);
		}
		else {//fils
			execlp(buf, buf, (char *)NULL);
			exit (-1) ;
		}
		//retour au prompt et attente de la prochaine commande
		write ( STDOUT_FILENO , prompt, strlen(prompt) );

	}
	exit(EXIT_SUCCESS);

}
