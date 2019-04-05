#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *tambahMakanan(void *ptr);

void *tambahMakanan(void *ptr){
	int *a, b;
	a = (int *)ptr;
	printf("Masukkan jumlah makanan: \n");
	scanf("%d", &b);
	*a += b;
	printf("Berhasil\n");
}

void main(){
        key_t key = 1234;
        int *makanan_toko;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        makanan_toko = shmat(shmid, NULL, 0);

	pthread_t thread1, thread2, thread3;//inisialisasi awal
	int iret1, iret2, iret3, a=0;
	makanan_toko = &a;

	int input;
	while(1){
		printf("\n");
		printf("Shop\n");
		printf("Food stock: %d\n", *makanan_toko);
		printf("1. Restock\n");
		printf("2. Exit\n");

		scanf("%d", &input);
		//getchar();
		
		if(input == 1){
			iret1 = pthread_create( &thread1, NULL, tambahMakanan, (void*)makanan_toko); //membuat thread pertama
		    	if(iret1) //jika eror
    			{
        			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        			exit(EXIT_FAILURE);
    			}
			pthread_join(thread1, NULL);

		}
		if(input == 2){
			exit(EXIT_SUCCESS);
		}
	}
}
