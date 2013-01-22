/*
Author: Himanshu Shah
Program to calculate word count for a single file using Pthreads.

-Counts characters including spaces and period.
-Number of Lines equals the number of period.
-Words are counted using spaces and period.

Date:Jan-16-2013
*/


#include <pthread.h>
#include <stdio.h>
typedef unsigned long count_t;
typedef enum {false=0, true=1} bool;
void *thread_function(void *);
void *excess_thread_function(void *);

// TOTAL COUNTERS
count_t total_ccount;
count_t total_wcount;
count_t total_lcount;
count_t total_error;

//Number of threads
int NUM_THREADS=3;

// Counters for threads
struct thread_data_structure{
   int  thread_id;
   count_t ccount;
   count_t wcount;
   count_t lcount;
   count_t error;
   char buffer[30];
};

//Main Function
int main()
{
	struct thread_data_structure thread_data[NUM_THREADS];
	FILE *f;
	int excess;
	pthread_t thread[NUM_THREADS],excess_thread;
  if (f = fopen("iliad.mb.txt", "rt"))
  {		
			int i;
			while (!feof(f))
			{
				bool flag=false;
				i=0;
				int round=0;
				for(flag=false; i<NUM_THREADS;i++,round++)
				{
					excess=(fread(thread_data[i].buffer, 1, 30, f));
					thread_data[i].thread_id=i;
					if(excess==30){
						pthread_create(&thread[i], NULL, thread_function, (void *) &thread_data[i]); 
					}		//Create Threads
 					else{	
//Invoke function that serially calculates the remaining arguments: buffer[i] and excess
						thread_data[i].error=excess;
						pthread_create(&excess_thread,NULL, excess_thread_function, (void*) &thread_data[i]);
						flag=true;
						break;
					}
				}
// Join Threads to the main thread and perform the addition operation
				for(i=0; i<round;i++)
				{
					if(pthread_join(thread[i], NULL)){
					fprintf(stderr, "Error joining thread[%d] \n",i);}
					else{
						total_ccount+=thread_data[i].ccount;
						total_wcount+=thread_data[i].wcount;
						total_lcount+=thread_data[i].lcount;
						total_error+=thread_data[i].error;
					//	total_wcount+=(total_lcount/2)-1;
//			 		printf("\n\n\t\t=====TOTAL AFTER JOINING THREAD[%d]=============\nTotal Character Counter: %6lu Total Word Count: %6lu Total Lines:%6lu",i,total_ccount,total_wcount,total_lcount);
       					}
				}
					if(flag){	/*Joining the Last thread- The Excess Thread*/
				  if(pthread_join(excess_thread, NULL)){
					fprintf(stderr, "Error joining Excess thread \n");
}
					else{        
						total_ccount+=thread_data[i].ccount;
						total_wcount+=thread_data[i].wcount;
						total_lcount+=thread_data[i].lcount;
						total_error+=thread_data[i].error;
						
//			 		printf("\n\n\t\t=====TOTAL AFTER JOINING EXCESS THREAD[%d]=============\nTotal Character Counter: %6lu Total Word Count: %6lu Total Lines:%6lu",i,total_ccount,total_wcount,total_lcount);

							}
					}
			}
    }
//total_wcount+=total_lcount;

printf("\n\n\t\n==============:TOTAL:===========\n\tTotal Character Counter: %6lu \n\t Total Word Count: %6lu \n\t Total Lines:%6lu \n\t Total Special Characters: %6lu\n",total_ccount,total_wcount,total_lcount,total_error);
fclose(f);

}

//Function for Threads- USE: Process the 30 character large chunk of data and fill the Ccount,Wcount and Lcount.
void *thread_function(void *threadarg)
{

   struct thread_data_structure *my_data;
   my_data = (struct thread_data_structure *) threadarg;
	my_data->ccount=0;
	my_data->wcount=0;
	my_data->lcount=0;
	my_data->error=0;
//	printf("\n=========================================================================================\nThread String Array[%d]:%s",my_data->thread_id,my_data->buffer);
   int k=0;
   		while(k<30)
		{
		
			if(isalpha(my_data->buffer[k])|| my_data->buffer[k]== '.'){
//				printf("\nTHREAD [%d] :IS ALPHA[%d] %c ||Char counter %6lu",my_data->thread_id,k,my_data->buffer[k],(my_data->ccount+1));
				my_data->ccount++;
			}
			else if(my_data->buffer[k]=='\n')
			{
			my_data->wcount++;
//			printf("\nTHREAD [%d] :IS NEWLINE[%d] %c||Lines counter %6lu",my_data->thread_id,k,my_data->buffer[k],(my_data->lcount+1));
				my_data->lcount++;
				my_data->ccount++;
			}
			else if(my_data->buffer[k]== ' ')
			{
//				printf("\nTHREAD [%d] :IS SPACE[%d]  %c||Word counter %6lu",my_data->thread_id,k,my_data->buffer[k],(my_data->wcount+1));
				my_data->ccount++;
				if(isalpha(my_data->buffer[k+1]))
				my_data->wcount++;
			}
			else
			{
				my_data->error++;
				my_data->ccount++;
				if(isalpha(my_data->buffer[k+1]))
				my_data->wcount++;
//				printf("\nTHREAD [%d] :ERROR Character [%d]: %c||Error counter %6lu",my_data->thread_id,k,my_data->buffer[k],my_data->error);
			}

			
		fflush(stdout);
//		usleep(100*1000);
		k++;
		}
}

//Function for Excess characters- USE: Process the excess characters and fill the Ccount,Wcount and Lcount.
void *excess_thread_function(void *threadarg)
{
   struct thread_data_structure *my_data;
   my_data = (struct thread_data_structure *) threadarg;
   int excess= my_data->error;
	my_data->ccount=0;
	my_data->wcount=0;
	my_data->lcount=0;
	my_data->error=0;
   int k=0;

//	printf("\n=========================================================================================\nThread String Array[%d]:%s",my_data->thread_id,my_data->buffer);


   		while(k<excess)
		{
		
			if(isalpha(my_data->buffer[k] || my_data->buffer[k]== '.')){
//				printf("\nTHREAD [%d] :IS ALPHA[%d] %c||Char counter %6lu",my_data->thread_id,k,my_data->buffer[k],(my_data->ccount+1));
				my_data->ccount++;
			}
			else if(my_data->buffer[k]=='\n')
			{
				my_data->wcount++;
//				printf("\nTHREAD [%d] :IS NEWLINE[%d] %c||Lines counter %6lu",my_data->thread_id,k,my_data->buffer[k],(my_data->lcount+1));
				my_data->lcount++;
				my_data->ccount++;
			}
			else if(my_data->buffer[k]== ' ')
			{
//				printf("\nTHREAD [%d] :IS SPACE[%d] %c||Word counter %6lu",my_data->thread_id,k,my_data->buffer[k],(my_data->wcount+1));
				my_data->ccount++;
//				if(isalpha(my_data->buffer[k+1]))
				my_data->wcount++;
			}
			else
			{
				my_data->error++;
//				printf("\nTHREAD [%d] :ERROR Character [%d]: %c||Error counter %6lu",my_data->thread_id,k,my_data->buffer[k],my_data->error);
				my_data->ccount++;
				if(isalpha(my_data->buffer[k+1]))
				my_data->wcount++;
				
			}
		fflush(stdout);
//		usleep(100*1000);
		k++;
		}
}






