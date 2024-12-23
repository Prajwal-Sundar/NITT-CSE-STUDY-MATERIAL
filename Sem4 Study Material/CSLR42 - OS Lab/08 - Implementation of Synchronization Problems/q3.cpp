#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p;
    int status;
    key_t key = ftok("shmfile",65);
    int shmid=shmget(IPC_PRIVATE, sizeof(int),0777|IPC_CREAT);
    p= fork();
    if(p == 0)
    {
        int *n = (int *)shmat(shmid,0,0);
        printf("Enter the  number :\n");
        scanf("%d",n);
        shmdt(n);
    }
    if(p>0)
    {
        wait(&status);
        int *m = (int *)shmat(shmid,0,0);
        if(*m % 2 == 0)
        {
            printf("Even\n");
        }
        else
        {
            printf("Odd\n");
        }
        shmdt((void *)m);
        shmctl(shmid,IPC_RMID,NULL);
    }
}