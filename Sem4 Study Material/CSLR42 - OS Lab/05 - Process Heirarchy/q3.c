#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int fd1[2];
	int fd2[2]; 

	char input_str[100];
	pid_t p;

	if (pipe(fd1) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}
	if (pipe(fd2) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}

	scanf("%s", input_str);
	p = fork();

	if (p < 0) {
		fprintf(stderr, "fork Failed");
		return 1;
	}

	else if (p > 0) {
		int count;
		
		close(fd1[0]);

		write(fd1[1], input_str, strlen(input_str) + 1);
		close(fd1[1]);

		wait(NULL);

		close(fd2[1]);

		read(fd2[0], &count, sizeof(count));
		printf("The number of vowels are :  %d\n", count);
		close(fd2[0]);
	}

	else {
		close(fd1[1]); 


		char concat_str[100];
		read(fd1[0], concat_str, 100);

		int k = strlen(concat_str),count =0;
		int i;
		for (i = 0; i < k; i++)
			if(concat_str[i] == 'a'||concat_str[i] =='e'||concat_str[i] =='i'||concat_str[i] =='o'||concat_str[i] =='u')
			{
				count++;
			}
			
		close(fd1[0]);
		close(fd2[0]);

		write(fd2[1], &count, sizeof(count));
		close(fd2[1]);

		exit(0);
	}
}

