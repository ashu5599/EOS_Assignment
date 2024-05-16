#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int ret1, ret2, err1, err2, s1, s2;
	int arr[2], ret;
	printf("parent started!\n");

	// create pipe
	ret = pipe(arr);
	if(ret < 0) {
		perror("pipe() failed");
		_exit(3);
	}

	// run "who" command
	ret1 = fork();
	if(ret1 == 0) {
		// dup pipe write fd to stdout
		close(arr[0]);
		dup2(arr[1], 1); 
		close(arr[1]);

		err1 = execlp("who", "who", NULL);
		if(err1 < 0) {
			perror("exec() failed to execute who cmd");
			_exit(1);
		}
	}

	// run "wc" command
	ret2 = fork();
	if(ret2 == 0) {
		// dup pipe read fd to stdin
		close(arr[1]);
		dup2(arr[0], 0);
		close(arr[0]);


		err2 = execlp("wc", "wc", NULL);
		if(err2 < 0) {
			perror("exec() failed to execute wc cmd");
			_exit(2);
		}
	}

	// close pipe both ends in parent (no write no read)
	close(arr[1]);
	close(arr[0]);
	waitpid(ret1, &s1, 0);
	waitpid(ret2, &s2, 0);
	printf("parent completed!\n");
	return 0;
}

