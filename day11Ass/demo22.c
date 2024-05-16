/*#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void sig
int main() {
	    int arr[2],ret;
		char ch = 'A';
		int count = 0;

		ret = pipe(arr);

		if(ret<0) {
				perror("pipe() failed");
				_exit(1);
		}
		while(1) {
				ret = write(arr[1], &ch, 1);
				count++;
				printf("bytes written: %d\n",count);
			}
						

}
*/

/*#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include<stdlib.h>
void handle_sigpipe(int sig) {
  printf("SIGPIPE received. Pipe buffer likely full.\n");
  exit(1);  // Terminate program on SIGPIPE
}

int main() {
  int arr[2], ret;
  char ch = 'A';
  int count = 0;

  ret = pipe(arr);
  if (ret < 0) {
    perror("pipe() failed");
    return 1;
  }

  // Install SIGPIPE handler
  signal(SIGPIPE, handle_sigpipe);

  while (1) {
    ret = write(arr[1], &ch, 1);
    if (ret == -1) {  // Check for write failure (likely full buffer)
      break;  // Exit loop on write error (assuming buffer is full)
    }
    count++;
    printf("bytes written: %d\n", count);
  }

  close(arr[0]);  // Close unused read end
  close(arr[1]);  // Close write end

  return 0;
}
*/

