#include <pthread.h>
#include <stdio.h>
typedef unsigned long count_t;

// Counters for big threads
count_t big_ccount;
count_t big_wcount;
count_t big_lcount;

// Counters for med threads
count_t med_ccount;
count_t med_wcount;
count_t med_lcount;
/*
// Counters for big threads
count_t big_ccount;
count_t big_wcount;
count_t big_lcount;
*/

// Counters for main threads
count_t t_ccount;
count_t t_wcount;
count_t t_lcount;


void *big_t(void *big_t_ptr)
{
	char *b_ptr = (char *)big_t_ptr;
	int k=0;
	int error=0;
	
		while(k<30)
		{
		
			if(isalpha(b_ptr[k])){
				printf("\n\t\t\tBIG:IS ALPHA[%d] %c||Char counter %6lu",k,b_ptr[k],(big_ccount+1));
				big_ccount++;
			}
			else if(b_ptr[k]=='\n')
			{
				printf("\n\t\t\tBIG:IS NEWLINE[%d] %c||Lines counter %6lu",k,b_ptr[k],(big_lcount+1));
				big_lcount++;
			}
			else if(b_ptr[k]== ' ')
			{
				printf("\n\t\t\tBIG:IS SPACE[%d] %c||Word counter %6lu",k,b_ptr[k],(big_wcount+1));
				big_wcount++;
			}
			else
{				error++;
				printf("\n\t\t\tBIG:ERROR Character [%d]: %c||Error counter %d",k,b_ptr[k],error);
}
		fflush(stdout);
		usleep(400*1000);
		k++;
		}

		printf("\n\n===========Character Count %6lu\n\n===========Word Count %6lu\n\n===========Line Count %6lu",big_ccount,big_wcount,big_lcount);
/*			printf("\n\t+++++Sub Thread:  %c", b_ptr[i++]);
			fflush(stdout);
			usleep(400*1000);
*/
		
	return NULL;
}


void *med_t(void *med_t_ptr)
{
	char *m_ptr = (char *)med_t_ptr;
	int k=0;
	int error=0;
	
		while(k<20)
		{
		
			if(isalpha(m_ptr[k])){
				printf("\n\t\t\t\t\t\tMED:IS ALPHA[%d] %c ||Char counter %6lu",k,m_ptr[k],(med_ccount+1));
				med_ccount++;
			}
			else if(m_ptr[k]=='\n'){
				printf("\n\t\t\t\t\t\tMED:IS NEWLINE[%d] %c ||Line counter %6lu",k,m_ptr[k],
(med_lcount+1));
				med_lcount++;
			}
			else if(m_ptr[k]== ' '){
				printf("\n\t\t\t\t\t\tMED:IS SPACE[%d] %c ||Word counter %6lu",k,m_ptr[k],
(med_wcount+1));
				med_wcount++;
			}
			else{
				error++;
				printf("\n\t\t\t\t\t\tMED:ERROR Character [%d]: %c",k,m_ptr[k]);
			}
		fflush(stdout);
		usleep(400*1000);
		k++;
		}

printf("\n\n=====MEDIUM======Character Count %6lu\n\n===========Word Count %6lu\n\n===========Line Count %6lu",med_ccount,med_wcount,med_lcount);
/*			printf("\n\t+++++Sub Thread:  %c", b_ptr[i++]);
			fflush(stdout);
			usleep(400*1000);
*/
		
	return NULL;
}




int main()
{

FILE *f;
  char buffer[11];
  char bbuffer[30],mbuffer[20];
  pthread_t b_thread,m_thread;
  if (f = fopen("fred.txt", "rt"))
  {
	printf("The file contents are:");
while (!feof(f))
{
	counter=fread(buffer, 1, 11, f);
	if (counter==11)
	{
		if(30==fread(bbuffer, 1, 30, f))
		{
	
			if(pthread_create(&b_thread, NULL, big_t,  (void *) bbuffer)) {
				fprintf(stderr, "Error creating thread\n");
				return 1;
			}
			else
			{
			printf("\n\n\n\n\t=========================Large Thread Created Successfully================================\n\n");				
			}
		}
	
		if(20==fread(mbuffer, 1, 20, f))
		{
	
			if(pthread_create(&m_thread, NULL, med_t,  (void *) mbuffer)) {
				fprintf(stderr, "Error creating thread\n");
				return 1;
			}
			else
			{
			printf("\n\n\n\n\t========================= Medium Thread Created Successfully================================\n\n");				
			}
		}
		

		int i=0;
		
		while(i<11)
		{

			if(isalpha(buffer[i])){
				printf("\nMAIN THREAD:IS ALPHA[%d] %c||Char counter %6lu",i,buffer[i],(t_ccount+1));
				t_ccount++;
			}
			else if(buffer[i]=='\n')
			{
				printf("\nMAIN THREAD: IS NEWLINE[%d] %c||Line counter %6lu",i,buffer[i],(t_lcount+1));
				t_lcount++;
			}
			else if(buffer[i]== ' ')
			{
				printf("\nMAIN THREAD: IS SPACE[%d] %c||Word counter %6lu",i,buffer[i],(t_wcount+1));
				t_wcount++;
			}
			else
{				printf("\nMAIN THREAD: ERROR Character [%d]: %c",i,buffer[i]);
}
		fflush(stdout);
		usleep(400*1000);
		i++;
		}
printf("\n\nMAIN THREAD:===========Character Count %6lu\n\n===========Word Count %6lu\n\n===========Line Count %6lu",t_ccount,t_wcount,t_lcount);

	/*	
			printf("\n+++++Main Thread [%d]:  %c",i, buffer[i]);
			fflush(stdout);
		usleep(400*1000);	
		i++;
		}
		*/
		
	if(pthread_join(m_thread, NULL)) {
		fprintf(stderr, "Error joining Medium thread \n");
		return 2;
	}
	else
	{
		t_ccount+=med_ccount;
		t_wcount+=med_wcount;
		t_lcount+=med_lcount;
 		printf("\n\n\t\t=====After Medium Thread=============\nTotal Character Counter: %6lu Total Word Count: %6lu Total Lines:%6lu",t_ccount,t_wcount,t_lcount);
	}

	if(pthread_join(b_thread, NULL)) {
		fprintf(stderr, "Error joining Large thread\n");
		return 2;
	}
	else{
		t_ccount+=big_ccount;
		t_wcount+=big_wcount;
		t_lcount+=big_lcount;
 		printf("\n\n\t\t=======After Large Thread===========\nTotal Character Counter: %6lu Total Word Count: %6lu Total Lines:%6lu",t_ccount,t_wcount,t_lcount);
		}
	}

printf("\n\n\t\n??????????????????????TOTAL:===========\nTotal Character Counter: %6lu Total Word Count: %6lu Total Lines:%6lu",t_ccount,t_wcount,t_lcount);

}
	fclose(f);

return 0;

}
