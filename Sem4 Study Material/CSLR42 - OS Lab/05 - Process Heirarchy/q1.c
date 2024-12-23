#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
	pid_t ci,pi;
	ci = getpid();
	printf("P1 ID : %d\n",ci);
	for(int i=0;i<2;i++)
	{
		if(fork() == 0)
		{
			ci = getpid();
			pi = getppid();
			printf("P%d ID: %d\t",i+2,ci);
			printf("P%d parent ID : %d\n",i+2,pi);
			if(fork() == 0)
			{
				ci = getpid();
				pi = getppid();
				printf("P%d ID: %d\t",i+4,ci);
				printf("P%d parent ID : %d\n",i+4,pi);
				exit(0);
			}
			exit(0);
		}	
	}
	return 0;
}
