#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //library thread

void *faktorial( void *ptr );
//void *input(void *ptr);

int main()
{
    	pthread_t thread1;//inisialisasi awal
    	int  iret1, *a, b[100], i, j, swap, c, batas=0;
	char d;
	i = 0;
    	while(i < 100 && d != '\n'){
		scanf("%d%c", &b[i], &d);
		batas++;
	i++;
	}
	
	for(i = 0; i<batas; i++){
		for(j = i+1; j < batas; j++){
			if(b[i] > b[j]){
				swap = b[i];
				b[i] = b[j];
				b[j] = swap;
			}
		}
	}

	for(i = 0; i < batas; i++){
		c = b[i];
		a = &c;
		iret1 = pthread_create( &thread1, NULL, faktorial, (void*) a); //membuat thread pertama
    		if(iret1) //jika eror
   		{
        		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        		exit(EXIT_FAILURE);
    		}
    		pthread_join(thread1, NULL);
	}
    // pthread_join( thread1, NULL);
    // pthread_join( thread2, NULL); 
    exit(EXIT_SUCCESS);
}

void *faktorial( void *ptr )
{
    int *a, i;
    a = (int *)ptr;
    long long int tampung = 1;	
    for(int i=1;i <= *a;i++){
        tampung *= i;
    }

    printf("%d!= %lld\n", *a, tampung);
}
