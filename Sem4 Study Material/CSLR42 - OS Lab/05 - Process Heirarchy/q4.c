#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int isprime(int a)
{
	for(int i=2;i<a;i++)
	{
		if(a%i == 0)	return 0;
	}
	return 1;	
}

int main()
{
	int fd11[2];
	int fd12[2];
	
	int fd21[2];
	int fd22[2]; 

	char input_str[100];
	pid_t p;

	if (pipe(fd11) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}
	if (pipe(fd12) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}

	//scanf("%s", input_str);
	int A[] = {1,2,3,4,5,12,4,234,5,345,37};
	
	p = fork();

	if (p < 0) {
		fprintf(stderr, "fork Failed");
		return 1;
	}

	else if (p > 0) {
		int count;
		
		close(fd11[0]);

		write(fd11[1], input_str, strlen(input_str) + 1);
		close(fd11[1]);

		wait(NULL);

		close(fd12[1]);

		read(fd12[0], &count, sizeof(count));
		//printf("The number of vowels are :  %d\n", count);
		close(fd12[0]);
	}

	else {
		close(fd11[1]); 


		char concat_str[100];
		read(fd11[0], concat_str, 100);

		int k = strlen(concat_str),count =0;
		int i;
		for (i = 0; i < k; i++)
			if(concat_str[i] == 'a'||concat_str[i] =='e'||concat_str[i] =='i'||concat_str[i] =='o'||concat_str[i] =='u')
			{
				count++;
			}
			
		close(fd11[0]);
		close(fd12[0]);

		write(fd12[1], &count, sizeof(count));
		close(fd12[1]);

		exit(0);
	}
	
	printf("Inside child process ");
	for(int i=0;i<11;i++)
	{
		if(isprime(A[i]))
			printf("%d ",A[i]);
	}
	printf("\nInside grandchild : ");
	int sum = 0;
	for(int i=0;i<11;i++)
	{
		if(A[i]%2 != 0)
			sum+=A[i];	
	}
	printf("%d\n",sum);
}

