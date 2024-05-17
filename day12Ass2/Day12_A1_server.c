#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main()
{
	int num1,num2,result;
	int serreq_fd,serres_fd;

	serreq_fd = open("/home/hardik/EOS/ASSIGN_12_WR",O_RDONLY);
	if(serreq_fd<0)
	{
		perror("open() failed");
		_exit(1);
	}
	read(serreq_fd,&num1,sizeof(num1));
	read(serreq_fd,&num2,sizeof(num2));
	close(serreq_fd);
	result=num1+num2;
	serres_fd = open("/home/hardik/EOS/ASSIGN_12_RD",O_WRONLY);
	if(serres_fd<0)
	{
		perror("open() failed");
		_exit(1);
	}
	write(serres_fd,&result,sizeof(result));
	close(serres_fd);
	return 0;
}
