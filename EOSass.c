#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
int ret1, ret2,ret3,ret4,i,s;
ret1=fork();
if(ret1==0)
{for (i=1;i<=5;i++)
{
printf("I'm class1\n");
}
ret2=fork();
if(ret2==0)
{
for(i=1;i<=5;i++)
{
printf("I'm child2\n");
}
ret3=fork();
if(ret3==0)
{
for (i=1; i<=5;i++)
{
printf("I'm child3\n");
}
ret4=fork();
if(ret4==0)
{
for(i=1;i<=5;i++)
{
printf("I'm child4\n");
}
_exit(0);
}
waitpid(ret4 ,&s ,0);
_exit(0);
}
waitpid(ret3,&s,0);
_exit(0);
}
waitpid(ret2,&s,0);
_exit(0);
}
return 0;
}

