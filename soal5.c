#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

struct s{
	int hunger_status;
	int hygiene_status;
	int damage;
	int health_status;
	int enemy_health;
	int makanan_shop;
	int makanan_monster;
	int cooldown;
};

void *hunger(void *ptr){
	struct s *monster = (struct s*)ptr;
	int i;
	for(i = 0; i < monster->hunger_status; i++){
		printf("Hunger: ");
		printf("%d\n", monster->hunger_status);
		monster->hunger_status -= 5;
		fflush(stdout);
		sleep(10);
	//	system("clear");
	}
}

void *beriMakan(void *ptr){
	struct s *monster = (struct s*)ptr;
	printf("Beri makan monstermu:\n");
	if(monster->makanan_monster < 0){
		printf("Makanan yang tersedia tidak cukup. Belilah\n");
	}
	else{
		monster->makanan_monster -= 1;
		monster->hunger_status += 15;
		if(monster->hunger_status > 200){
			monster->hunger_status = 200;
		}
	}
}

void *hygiene(void *ptr){
	struct s *monster = (struct s*)ptr;
	int i;
	for(i = 0; i< monster->hygiene_status; i++){
	printf("Hygiene: ");
	printf("%d\n", monster->hygiene_status);
	monster->hygiene_status -= 10;
	fflush(stdout);
	sleep(30);
	//system("clear");
	}
	
}

void *bathCooldown(void *ptr){
	struct s *monster = (struct s*)ptr;
	int i;
	//printf("Bath will be ready in ");
	for(i=1;i<=20;i++){
		printf("Bath will be ready in ");
		printf("%d", monster->cooldown);
		printf("s\n");
		monster->cooldown -= 1;
		fflush(stdout);
		sleep(1);
	//	system("clear");
	}
}

void *bath(void *ptr){
	struct s *monster = (struct s*)ptr;
	monster->hygiene_status += 30;
}

void *health(void *ptr){
	struct s *monster = (struct s*)ptr;
	int i;
	for(i = 0; i < monster->health_status; i++){
	printf("Health: ");
	printf("%d\n", monster->health_status);
	monster->health_status += 5;
	fflush(stdout);
	sleep(10);
	//system("clear");
	}
}

void *beli_makanan(void *ptr){
	struct s *monster = (struct s*)ptr;
	int b;
	printf("Masukkan jumlah makanan yang ingin dibeli: \n");
	scanf("%d", &b);
	if((monster->makanan_shop - b) < 0){
		printf("Transaksi gagal\n");
	}
	else{
		monster->makanan_shop -= b;
		monster->makanan_monster += b;
	}
}

void *attack(void *ptr){
	struct s *monster = (struct s*)ptr;
	monster->enemy_health -= monster->damage;
	sleep(10);
	monster->health_status -= monster->damage;
}

void *standby(void *ptr){
	struct s *monster = (struct s*)ptr;
	int i;	
	printf("StandBy Mode\n");
	//system("clear");
	for(i = 1; i <= 500; i++){
		printf("Health: ");
		printf("%d", monster->health_status);
		printf("\n");
		monster->health_status += 5;
		fflush(stdout);
		sleep(10);
		
	}

	for(i = 1; i <= monster->hunger_status; i++){
		printf("Hunger: ");
		printf("%d", monster->hunger_status);
		printf("\n");
		monster->hunger_status -= 5;
		fflush(stdout);
		sleep(10);
		system("clear");
	}

	for(i = 1; i <=  monster->hygiene_status; i++){
	printf("Hygiene: ");
	printf("%d", monster->hygiene_status);
	printf("\n");
	monster->hygiene_status -= 10;
	fflush(stdout);
	sleep(30);
	system("clear");
	}
		
	printf("Food left: %d\n", monster->makanan_monster);
	
	for(i=1;i<=20;i++){
		printf("Bath will be ready in ");
		printf("%d", monster->cooldown);
		printf("s\n");
		monster->cooldown -= 1;
		fflush(stdout);
		sleep(1);
		system("clear");
	}
}

void main()
{
        key_t key = 1234;
        int *makanan_toko;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        makanan_toko = shmat(shmid, NULL, 0);

	pthread_t thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8;
	int iret1, iret2, iret3, iret4, iret5, iret6, iret7, iret8;

	struct s monster;
	monster.hunger_status = 200;
	monster.hygiene_status = 100;
	monster.health_status = 300;
	monster.enemy_health = 100;
	monster.damage = 20;
	monster.makanan_monster = 0;
	monster.makanan_shop = *makanan_toko;
	monster.cooldown = 20;

	char nama[50];
	printf("Masukkan nama monstermu:\n");
	scanf("%[^\n]", nama);
	int input;
	int standBy_signal = 1;
	while(1){
		printf("%s\n", nama);
		if(standBy_signal == 5){
			printf("Kalah\n");
			exit(EXIT_SUCCESS);
		}
		if(standBy_signal == 1){
			system("clear");
			printf("Standby Mode\n");
			if(monster.hunger_status <= 0 || monster.hygiene_status <= 0){
				standBy_signal = 5;
			}
			//printf("Health: ");
			iret1 = pthread_create( &thread1, NULL, health, (void*)&monster); //membuat thread pertama
    			if(iret1) //jika eror
    			{
        			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        			exit(EXIT_FAILURE);
    			}
			//pthread_join(thread1, NULL);
			//printf("Hunger: ");
			iret2 = pthread_create( &thread2, NULL, hunger, (void*)&monster); //membuat thread pertama
    			if(iret2) //jika eror
    			{
        			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        			exit(EXIT_FAILURE);
    			}
			//pthread_join(thread2, NULL);
			//printf("Hygiene: ");
			iret3 = pthread_create( &thread3, NULL, hygiene, (void*)&monster); //membuat thread pertama
    			if(iret3) //jika eror
    			{
        			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        			exit(EXIT_FAILURE);
    			}
			//pthread_join(thread3, NULL);
			printf("Food left: %d\n", monster.makanan_monster);
			//printf("Bath will be ready in ");
			iret4 = pthread_create( &thread4, NULL, bathCooldown, (void*)&monster); //membuat thread pertama
    			if(iret4) //jika eror
			{
        			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        			exit(EXIT_FAILURE);
    			}
			//pthread_join(thread4, NULL);
			pthread_join(thread1, NULL);
			pthread_join(thread2, NULL);
			pthread_join(thread3, NULL);
			pthread_join(thread4, NULL);

			printf("Choices\n");
			printf("1. Eat\n");
			printf("2. Bath\n");
			printf("3. Battle\n");
			printf("4. Shop\n");
			printf("5. Exit\n");

			scanf("%d", &input);
			if(input == 1){
				iret5 = pthread_create( &thread5, NULL, beriMakan, (void*)&monster); //membuat thread pertama
    				if(iret5) //jika eror
    				{
        				fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        				exit(EXIT_FAILURE);
    				}
				pthread_join(thread5, NULL);
			}
			else if(input == 2){
				if(monster.cooldown == 0){
					iret6 = pthread_create( &thread6, NULL, bath, (void*)&monster); //membuat thread pertama
    					if(iret6) //jika eror
    					{
        					fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        					exit(EXIT_FAILURE);
    					}
					pthread_join(thread6, NULL);
					monster.cooldown = 20;
				}
				else{
					printf("Masih cooldown\n");
				}
			}
			else if(input == 3){
				standBy_signal = 0;
			}
			else if(input == 4){
				standBy_signal = 2;
			}
			else if(input == 5){
				exit(EXIT_SUCCESS);
			}
		}
		else if(standBy_signal == 0){
			int input2, enemy=100;
			printf("Battle Mode\n");
			printf("Monster's Health: %d\n", monster.health_status);
			printf("Enemy's Health: %d\n", monster.enemy_health);
			printf("Choices\n");
			printf("1. Attack\n");
			printf("2. Run\n");
			scanf("%d", &input2);
			if(monster.enemy_health <= 0){
				printf("Menang\n");
				standBy_signal = 1;
			}
			if(monster.health_status <=0){
				standBy_signal = 5;
			}
			if(input2 == 1){
				iret7 = pthread_create( &thread7, NULL, attack, (void*)&monster); //membuat thread pertama
    				if(iret7) //jika eror
    				{
        				fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        				exit(EXIT_FAILURE);
    				}
				pthread_join(thread7, NULL);
			}
			else if(input2 == 2){
				standBy_signal = 1;
			}
		}
		else if(standBy_signal == 3){
			int input3;
			printf("Shop Mode\n");
			printf("Shop food stock: %d\n", *makanan_toko);
			printf("Your food stock: %d\n", monster.makanan_monster);
			printf("Choices\n");
			printf("1. Buy\n");
			printf("2. Back\n");
			
			scanf("%d", &input3);
			if(input3 == 1){
				iret8 = pthread_create( &thread8, NULL, beli_makanan, (void*)&monster); //membuat thread pertama
    				if(iret8) //jika eror
    				{
        				fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        				exit(EXIT_FAILURE);
    				}
				pthread_join(thread8, NULL);
				*makanan_toko = monster.makanan_shop;
			}
			else if(input3 == 2){
				standBy_signal = 1;
			}
		}

	}
}
