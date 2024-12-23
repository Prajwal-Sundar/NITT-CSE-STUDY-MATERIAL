#include <stdio.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>

using namespace std;

struct stud
{
    int roll;
    char name[100];
    int m1,m2,m3,m4,m5;
};

int main()
{
    int status,shmid;
    shmid = shmget(IPC_PRIVATE,sizeof(struct stud),0644|IPC_CREAT);
    pid_t p;
    p = fork();
    if(p == 0)
    {
        struct stud *s = (struct stud*)shmat(shmid,0,0);
        printf("Enter the name, roll no., and marks in 5 subjexts : \n");
        scanf("%s",(s->name));
        scanf("%d",&(s->roll));
        scanf("%d",&(s->m1));
        scanf("%d",&(s->m2));
        scanf("%d",&(s->m3));
        scanf("%d",&(s->m4));
        scanf("%d",&(s->m5));
        shmdt(s);
    }
    if(p>0)
    {
        wait(&status);
        struct stud *s= (struct stud *)shmat(shmid,0,0);
        printf("The sum of marks in 5 subjs is : %d\n",(s->m1 + s->m2 + s->m3 + s->m4 + s->m5));
        printf("The avg of marks in 5 subjs is : %d\n",(s->m1 + s->m2 + s->m3 + s->m4 + s->m5)/5);
        shmdt(s);
        shmctl(shmid,IPC_RMID,NULL);
    }

}