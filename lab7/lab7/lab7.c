/* Author(s): Zack Waller Section 2
 *
 * This is a lab7.c the csc60mshell
 * This program serves as a skeleton for starting for lab 6.
 * Student is required to use this program to build a mini shell
 * using the specification as documented in direction.
 * Date: Fall 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;

#define MAXLINE 80
#define MAXARGS 20
#define MAX_PATH_LENGTH 50
#define TRUE 1

/* function prototypes */
 void process_input(int argc, char **argv); 
int parseline(char *cmdline, char **argv);
 void handle_redir(int count, char *argv[]); 

/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */
int main(void)
{
    char cmdline[MAXLINE];
    char *argv[MAXARGS];
    int argc;
    int status;
    pid_t pid;
    
    /* Loop forever to wait and process commands */
    while (TRUE) {
        /* Print your shell name: csc60mshell (m for mini shell) */
        printf("CSC60MSH> ");
        
        /* Read the command line */
        fgets(cmdline, MAXLINE, stdin);
        
        /* Call parseline to build argc/argv: their limits declared above */
        argc = parseline(cmdline, argv);
        
        
        /* If user hits enter key without a command, continue to loop again at the beginning */
        /*  Hint: if argc is zero, no command declared */
        /*  Hint: look up for the keyword "continue" in C */
        
        if ( argc == 0)
        {
            continue;
        }
        
        /*Handle build-in command: exit, pwd, or cd  */
        if (strcmp(argv[0],"exit")==0)
        {
            printf("EXIT SHELL\n");
            break;
        }
        else if(strcmp(argv[0],"pwd")==0)
        {
            char *path;
            char buffer[MAX_PATH_LENGTH];
            path = getcwd(buffer,MAX_PATH_LENGTH);
            if (path!=NULL)
            {
                printf("%s\n", path);
            }
            else
            {
                printf("PWD failed\n");
            }
            
        }
        else if(strcmp(argv[0],"cd")==0)
        {
            char *dir;
            if (argc == 1)
            {
                dir = getenv("HOME");
            }
            else
            {
                dir = argv[1];
            }
            if(chdir(dir)!=0)
            {
                printf("Error changing directory!\n");
            }
            
        }
        else//	/* Else, fork off a process */
        {
            pid = fork();
            switch(pid)
            {
                case -1:
                    perror("Shell Program fork error");
                    exit(1);
                case 0:
                    /* I am child process. I will execute the command, call: execvp */
                    process_input(argc, argv);
                    break;
                default:
                    /* I am parent process */
                    if (wait(&status) == -1)//&status
                        perror("Shell Program error");
                    else
                        printf("Child returned status: %d\n",status);
                    break;
            } /* end of the switch */
        }
    } /* end of the while */
} /* end of main */



/* ----------------------------------------------------------------- */
/*                  parseline                                        */
/* ----------------------------------------------------------------- */
/* parse input line into argc/argv format */

int parseline(char *cmdline, char **argv)
{
    int count = 0;
    char *separator = " \n\t";
    
    argv[count] = strtok(cmdline, separator);
    while ((argv[count] != NULL) && (count+1 < MAXARGS)) {
        argv[++count] = strtok((char *) 0, separator);
    }
    return count;
}
/* ----------------------------------------------------------------- */
/*                  process_input                                    */
/* ----------------------------------------------------------------- */
void process_input(int argc, char **argv) {
    /* Step 1: Call handle_redir to deal with operators:            */
    /* < , or  >, or both                                           */
	handle_redir(argc, argv);
    /* Step 2: perform system call execvp to execute command        */
    /* Hint: Please be sure to review execvp.c sample program       */


	
     if (execvp(argv[0],argv) == -1) {                                        
		perror("Shell Program");                                    
		_exit(-1);                                                  
     }
     else
     {
		_exit(0);
     }
}
/* ----------------------------------------------------------------- */
void handle_redir(int count, char *argv[])
{ /* 
     //we are gonna dup2 here
     if (strcmp(argv[0],'<') == 0 || strcmp(argv[0],'>') == 0)
     {
	//err here
     }
     
     int outcount = 0;
     int incount = 0;
   for (int i =0; i < count; i++)
     {
		 if (strcmp(argv[0], '<') == 0)
		 {

		 }
		 else if(strcmp(argv[0], '>') == 0)
		 {

		 }
     }
	 */
	 
	 int i;
	 for (i=0; i < count; i++)
	 {
		 if (strcmp(argv[i], "<") == 0)
		 {
			 //argv[i - 1];
			 int fileId;

			 fileId = open(argv[fd_out + 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR, S_IWUSR);

			 if (fileId < 0)
			 {
				 printf("error creating x.lis\n");
				 exit(EXIT_FAILURE);
			 }
			 dup2(fileId, 0);      /* copy fileID to stdin */
			 close(fileId);
			 argv[i] = NULL;
		 }
		 else if (strcmp(argv[i], ">") == 0)
		 {
			 int fileId;
			 fileId = creat(argv[i + 1], 0640);
			 
			 if (fileId < 0)
			 {
				 printf("error creating x.lis\n");
				 exit(EXIT_FAILURE);
			 }
			 dup2(fileId, 1);      /* copy fileID to stdout */
			 close(fileId);
			 argv[i] = NULL;

		 }
	 }

}
/* ----------------------------------------------------------------- */
/* ----------------------------------------------------------------- */
