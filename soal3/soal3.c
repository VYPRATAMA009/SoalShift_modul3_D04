#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h> //library thread

//char *tampung;

void *allStatus(void *ptr1);
void *tambahStatusAgmal(void *ptr1);
void *kurangStatusIraj(void *ptr2);
void *suspendAgmal();
void *suspendIraj();

struct s{
	int wakeUp;
	int spirit;
	int flagA;
	int flagB;
};

void *allStatus(void *ptr1){
	struct s *status = (struct s *)ptr1;
	printf("Agmal WakeUp_Status = %d\n", status->wakeUp);
	printf("Iraj Spirit_Status = %d\n", status->spirit);
}

void *tambahStatusAgmal(void *ptr1){
	struct s *status = (struct s *)ptr1;
	if(status->flagA == 1){
		printf("Fitur Agmal Ayo Bangun disabled 10 s\n");
		sleep(10);
	}
	else{
		status->wakeUp += 15;
	}
}

void *kurangStatusIraj(void *ptr2){
	struct s *status = (struct s *)ptr2;
	if(status->flagB == 1){
		printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
		sleep(10);
	}
	else{
		status->spirit -= 20;
	}
}

void *suspendAgmal(void *ptr){
	struct s *status = (struct s*)ptr;
	status->flagA = 1;
}

void *suspendIraj(void *ptr){
	struct s *status = (struct s*)ptr;
	status->flagB = 1;
}

int main()
{
    	pthread_t thread1, thread2, thread3, thread4, thread5;//inisialisasi awal
    	int  iret1, iret2, iret3, iret4, iret5;
	int counterA = 0, counterB = 0;
	struct s status;
	status.wakeUp = 0;
	status.spirit = 100;
	status.flagA = 0;
	status.flagB = 0;
	
	char kata[50];
	char *menu1 = "All Status";
	char *menu2 = "Agmal Ayo Bangun";
	char *menu3 = "Iraj Ayo Tidur";
 
	while(1){
		printf("\n");
		printf("Menu: \n");
		printf("1. All Status\n");
		printf("2. Agmal Ayo Bangun\n");
		printf("3. Iraj Ayo Tidur\n");
		printf("Ketik katanya:\n");

		scanf("%[^\n]", kata);
		getchar();
		if(status.wakeUp >= 100){
			printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
			break;
		}

		else if(status.spirit <= 0){
			printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
			break;
		}

		if(counterB == 3){
			counterB = 0;
			//printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
			//sleep(10);
			iret4 = pthread_create(&thread4, NULL, suspendIraj, (void *)&status);
			if(iret4){
				fprintf(stderr, "Error - pthread_create() return code: %d\n", iret4);
				exit(EXIT_FAILURE);
			}
			pthread_join(thread4, NULL);
		}

		else if(counterA == 3){
			counterA = 0;
			//printf("Fitur Agmal Ayo Bangun disabled 10 s\n");
			//sleep(10);
			iret5 = pthread_create(&thread5, NULL, suspendAgmal, (void *)&status);
			if(iret5){
				fprintf(stderr, "Error - pthread_create() return code: %d\n", iret5);
				exit(EXIT_FAILURE);
			}
		}

		if(strcmp(kata, menu1) == 0){
			iret1 = pthread_create( &thread1, NULL, allStatus, (void*)&status); //membuat thread pertama
    			if(iret1) //jika eror
    			{
        			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        			exit(EXIT_FAILURE);
    			}
			pthread_join(thread1, NULL);
		}

		else if(strcmp(kata, menu2) == 0){
    			counterB++;
			iret2 = pthread_create( &thread2, NULL, tambahStatusAgmal, (void*)&status);//membuat thread kedua
    			if(iret2)//jika gagal
   			{
        			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
        			exit(EXIT_FAILURE);
    			}
			pthread_join(thread2, NULL);
			status.flagA = 0;
		}

		else if(strcmp(kata, menu3) ==0){		
			counterA++;
			iret3 = pthread_create( &thread3, NULL, kurangStatusIraj, (void*)&status);
			if(iret2)
			{
				fprintf(stderr, "Error - pthread_create() return code: %d\n", iret3);
				exit(EXIT_FAILURE);
			}
			pthread_join(thread3, NULL);
			status.flagB = 0;
		}
	}

    // pthread_join( thread1, NULL);
    // pthread_join( thread2, NULL); 

    exit(EXIT_SUCCESS);
}
