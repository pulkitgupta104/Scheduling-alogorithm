#include<pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
int n;
int FCFS[40][5];
int SJF[40][6];
int SRTF[40][7];
void *FCFS1() {
	/*SORTING THE 2D ARRAY*/
	
        int temp,curr_time=0;
	for(int i=0;i<n-1;i++)
		for(int j=i;j<n;j++)
			if(FCFS[i][0]>FCFS[j][0])
			{
				temp=FCFS[i][0];
				FCFS[i][0]=FCFS[j][0];
				FCFS[j][0]=temp;
				temp=FCFS[i][1];
				FCFS[i][1]=FCFS[j][1];
				FCFS[j][1]=temp;
			}
	printf("\n\n\n");	
		
	for(int i=0;i<n;i++)
	{
		if(curr_time<FCFS[i][0])							//ADJUSTING FOR ANY IDEAL TIME
			curr_time=FCFS[i][0];
		FCFS[i][2]=curr_time=curr_time+FCFS[i][1];
		FCFS[i][3]=FCFS[i][2]-FCFS[i][0];
		FCFS[i][4]=FCFS[i][3]-FCFS[i][1];
             //   printf("fcfs iteration%d \n",i);
        }
	return;
}

void *SJF1(){
        int BT_Min,index_Min=0,temp,curr_time=0;
        /*SORTING THE 2D ARRAY*/
	for(int i=0;i<n-1;i++)
		for(int j=i;j<n;j++)
			if(SJF[i][0]>SJF[j][0])
			{
				temp=SJF[i][0];
				SJF[i][0]=SJF[j][0];
				SJF[j][0]=temp;
				temp=SJF[i][1];
				SJF[i][1]=SJF[j][1];
				SJF[j][1]=temp;
			}
	
	for(int i=0;i<n;i++)
	{
		BT_Min=100;						//ASSUMING THAT NO BT WILL BE GREATER THAN 100 
		if(curr_time<SJF[i][0])
			curr_time=SJF[i][0];
		for(int j=0;j<n;j++)
			if( (SJF[j][0]<=curr_time) && (SJF[j][5]!=1) && (BT_Min>SJF[j][1]) )
			{
				index_Min=j;
				BT_Min=SJF[j][1];		
			}
		SJF[index_Min][2] =  curr_time  =   curr_time + SJF[index_Min][1];
		SJF[index_Min][5]=1;
		SJF[index_Min][3]=SJF[index_Min][2]-SJF[index_Min][0];				//CALCULATION OF TAT
		SJF[index_Min][4]=SJF[index_Min][3]-SJF[index_Min][1];				//CALCULATION OF WT
               //  printf("sjf iteration %d \n",i);
        }
     return;
}


void *SRTF1(){
        int BT_Min,index_Min=0,temp,total_time=0,curr_time=0;
        /*SORTING THE 2D ARRAY*/
	for(int i=0;i<n-1;i++)
		for(int j=i;j<n;j++)
			if(SRTF[i][0]>SRTF[j][0])
			{
				temp=SRTF[i][0];
				SRTF[i][0]=SRTF[j][0];
				SRTF[j][0]=temp;
				temp=SRTF[i][1];
				SRTF[i][1]=SRTF[j][1];
				SRTF[j][1]=temp;
			}
	for(int i=0;i<n;i++)
	{
		SRTF[i][6]=SRTF[i][1];
		total_time+=SRTF[i][1];	
	}
	
	if(curr_time<SRTF[0][0])
			curr_time=SRTF[0][0];
		
	for(int i=0;i<total_time;i++)
	{
		BT_Min=100;
		for(int j=0;j<n;j++)
			if( (SRTF[j][0]<=curr_time) && (SRTF[j][5]!=1) && (BT_Min>SRTF[j][6]) )
			{
				index_Min=j;
				BT_Min=SRTF[j][6];		
			}
		SRTF[index_Min][6]--;
		curr_time++;
		if( (SRTF[index_Min][6]) == 0 )
		{
			SRTF[index_Min][5]=1;
			SRTF[index_Min][2]=curr_time;
		}
	}

	for(int i=0;i<n;i++)
	{
		SRTF[i][3]=SRTF[i][2]-SRTF[i][0];				//CALCULATION OF TAT
		SRTF[i][4]=SRTF[i][3]-SRTF[i][1];				//CALCULATION OF WT
	}
}

int main()
{       pthread_t tid1, tid2,tid3;
	printf("Enter the number of process: ");
	scanf("%d",&n);
	
	srand(2);
	printf("Arrival time and burst time of processes is randomly set ");
	for(int i=0;i<n;i++)
		{
                  FCFS[i][0]=rand()%10;
                  SJF[i][0]=FCFS[i][0];
                  SRTF[i][0]=FCFS[i][0];
		  SJF[i][5]=0;
                  SRTF[i][5]=0;
                }
	for(int i=0;i<n;i++)
	{
        
                  FCFS[i][1]=rand()%15;
                  SJF[i][1]=FCFS[i][1];
                  SRTF[i][1]=FCFS[i][1];
        }        
        pthread_create(&tid1, NULL, FCFS1, NULL);
        pthread_create(&tid2, NULL, SJF1, NULL);
        pthread_create(&tid3, NULL, SRTF1, NULL);
        pthread_join(tid2, NULL);
	pthread_join(tid1, NULL);
        pthread_join(tid3, NULL); 
        printf("FCFS Scheduling\n");
	printf("Arrival Time\tBurst Time\tCompletion Time\t\tTurn Around Time\tWaiting time\n");
	for(int i=0;i<n;i++)
		printf("%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",FCFS[i][0],FCFS[i][1],FCFS[i][2],FCFS[i][3],FCFS[i][4]);
	printf("\n\n\n");
        printf("SJF Scheduling\n");
	printf("Arrival Time\tBurst Time\tCompletion Time\t\tTurn Around Time\tWaiting time\n");
	for(int i=0;i<n;i++)
		printf("%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",SJF[i][0],SJF[i][1],SJF[i][2],SJF[i][3],SJF[i][4]);
        
	printf("\n\n\n");
        printf("SRTF Scheduling\n");
	printf("Arrival Time\tBurst Time\tCompletion Time\t\tTurn Around Time\tWaiting time\n");
	for(int i=0;i<n;i++)
		printf("%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",SRTF[i][0],SRTF[i][1],SRTF[i][2],SRTF[i][3],SRTF[i][4]);
        
 }


