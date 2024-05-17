#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int num1,num2,result;
	int clireq_fd, clires_fd;
	printf("Enter 2 numbers: ");
	scanf("%d %d",&num1,&num2);
	clireq_fd = open("/home/hardik/EOS/ASSIGN_12_WR",O_WRONLY);
	if(clireq_fd<0)
	{
		perror("open() failed");
		_exit(1);
	}
	write(clireq_fd,&num1,sizeof(num1));
	write(clireq_fd,&num2,sizeof(num2));
	close(clireq_fd);

	clires_fd = open("/home/hardik/EOS/ASSIGN_12_RD",O_RDONLY);
	if(clires_fd<0)
	{
		perror("open() failed");
		_exit(1);
	}
	read(clires_fd,&result,sizeof(result));
	close(clires_fd);
	printf("The sum is %d\n",result);
	return 0;	
}
