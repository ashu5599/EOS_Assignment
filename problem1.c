#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

void signaltoprocess(pid_t pid, int sig_num){
	int res=kill(pid, sig_num);
 	if(res==0){
     	printf("process killed sucessfully!");
 	}
	else{
	perror("process is not killed sucesfully!");
	}

}	

int main(){

	int sig;
    pid_t pid;

	printf("enter the proceess id:\n");
	scanf("%d", &pid);
	
	printf("enter the signal number:\n");
	scanf("%d", &sig);
	
	signaltoprocess(pid, sig);
	return 0;
}
