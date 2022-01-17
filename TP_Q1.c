
#include <fcntl.h>
#include <stdlib.h> 
#include <unistd.h> //Utiliser read et write et non printf
#include "string.h"
#include <sys/wait.h>

const char* welcome = "Bienvenue dans le Shell ENSEA\nPour quitter, tapez 'exit'. \n";
const char* prompt ="enseash %";

int main(void) {
	
	write ( STDOUT_FILENO , welcome, strlen(welcome) );
	write ( STDOUT_FILENO , prompt, strlen(prompt) );
	while(1){
	}
	exit(EXIT_SUCCESS);
}

