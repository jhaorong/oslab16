#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
void *process_1();
void *process_2();
int freeframe[16];
char PM[15][3];
void initPM();
int Duplicate_detect(int,int);
int head = 0;
int main()
{
    //printf("hello world\n");
    initPM();
    pthread_t p1,p2;
    pthread_create(&p1,NULL,process_1,NULL);
    pthread_create(&p2,NULL,process_2,NULL);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    printf("physical memory is:\n");
    printf("frame\toffset\tdata\n");
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<2;j++)
        {
            printf("%d\t%d\t%c\n",i,j,PM[i][j]);
        }
    }
    int flag=0;
    printf("free-frame table is:\n");
    for(int i=head;i<16;i++)
    {
        printf("%d ",freeframe[i]);
    }
    printf("\n");
    return 0;
}
void initPM()
{
    //printf("hello\n");
    srand(time(NULL));
    int random;
    //printf("hello\n");
    for(int i=0;i<16;i++)
    {
        random = rand()%16 ;
        if(Duplicate_detect(random,i) == 1)
        {
            i--;
        }
        else
        {
            freeframe[i] = random;
        //printf("i = %d freeframe = %d\n",i,freeframe[i]);
        }
    }
    //printf("hello\n");
}
void *process_1()
{
    char LM[3][100];
    strcpy(LM[0],"ab");
    strcpy(LM[1],"ef");
    strcpy(LM[2],"cd");
    int PT[3];
    for(int i=0;i<3;i++)
    {
        PT[i] = freeframe[head];
        strcpy(PM[freeframe[head++]],LM[i]);
    }
    printf("process1's Logical memory:\n");
    printf("page\tdata\n");
    for(int i=0;i<3;i++)
    {
        printf("%d\t%s\n",i,LM[i]);
    }
    printf("process1's page table:\n");
    printf("page\tdata\n");
    for(int i=0;i<3;i++)
    {
        printf("%d\t%d\n",i,PT[i]);
    }
}
void *process_2()
{
    char LM[3][100];
    strcpy(LM[0],"rx");
    strcpy(LM[1],"yy");
    strcpy(LM[2],"zz");
    int PT[3];
    for(int i=0;i<3;i++)
    {
        PT[i] = freeframe[head];
        strcpy(PM[freeframe[head++]],LM[i]);
    }
    printf("process2's Logical memory:\n");
    printf("page\tdata\n");
    for(int i=0;i<3;i++)
    {
        printf("%d\t%s\n",i,LM[i]);
    }
    printf("process2's page table:\n");
    printf("page\tdata\n");
    for(int i=0;i<3;i++)
    {
        printf("%d\t%d\n",i,PT[i]);
    }
}
int Duplicate_detect(int rand,int len)
{
    for(int i=0;i<len;i++)
    {
        if(freeframe[i] == rand)
        {
            return 1;
        }
    }
    return 0;
}



