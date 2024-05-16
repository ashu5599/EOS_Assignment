#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
		int arr1[2],arr2[2], s, ret, num1, num2,res;
		
		ret = pipe(arr1);
		ret = pipe(arr2);

		if(ret<0) {
				perror("pipe() failed");
				_exit(1);
			}	

		ret = fork();
		if(ret == 0) {
				close(arr1[0]);
				close(arr2[1]);
				printf("enter num1: ");
				scanf("%d",&num1);
				printf("enter num2: ");
				scanf("%d",&num2);
				ret = write(arr1[1], &num1, sizeof(num1));
				ret = write(arr1[1], &num2, sizeof(num2));
				
				ret = read(arr2[0], &res, sizeof(res));
				printf("result: %d\n", res);

				close(arr2[0]);
				close(arr1[1]);

			}
			else {
				close(arr1[1]);
				close(arr2[0]);
				
				ret = read(arr1[0], &num1, sizeof(num1));
				ret = read(arr1[0], &num2, sizeof(num2));

				res = num1 + num2;

				ret = write(arr2[1], &res, sizeof(res));

				close(arr2[1]);
				close(arr1[0]);
				waitpid(-1, &s, 0);

		}


	return 0;
}
