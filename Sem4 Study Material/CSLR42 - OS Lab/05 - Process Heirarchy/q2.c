#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
	int cid,pid;
	cid = getpid();
	printf("P1 ID : %d\n",cid);
	for(int i=0;i<2;i++)
	{
		if(fork() == 0)
		{
			cid = getpid();
			pid = getppid();
			printf("P ID: %d\t",cid);
			printf("P parent ID : %d\n",pid);
			if(fork() == 0)
			{
				cid = getpid();
				pid = getppid();
				printf("P ID: %d\t",cid);
				printf("P parent ID : %d\n",pid);
				exit(0);
			}
			else
			{
				if(i == 0)
				{
					if(fork() == 0)
					{	
						cid = getpid();
						pid = getppid();
						printf("P ID: %d\t",cid);
						printf("P parent ID : %d\n",pid);
						exit(0);
					}
					exit(0);
				}	
			}	
			exit(0);
		}	
	}
	return 0;
}
