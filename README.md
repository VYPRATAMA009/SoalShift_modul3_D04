# SoalShift_modul3_D04
## SOAL 1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
	./faktorial 5 3 4
	3! = 6
	4! = 24
	5! = 120
### Jawaban
membuat fungsi faktorial
  ```
  
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
  ```
  Fungsi main nya, di sini membuat tempat input, lalu mensorting nilai inputan dari kecil ke besar, lalu memanggil fungsi faktorial
  ```
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
  
  ```
  
## SOAL 2
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
a.	Terdapat 2 server: server penjual dan server pembeli
b.	1 server hanya bisa terkoneksi dengan 1 client
c.	Server penjual dan server pembeli memiliki stok barang yang selalu sama
d.	Client yang terkoneksi ke server penjual hanya bisa menambah stok
■	Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
e.	Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
■	Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
f.	Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
■	Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
■	Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
g.	Server penjual akan mencetak stok saat ini setiap 5 detik sekali
h.	Menggunakan thread, socket, shared memory
### jawaban
membuatkan server penjual
```
kode
```
membuatkan server pembeli
```
kode
```
membuatkan client pembeli
```
kode
```
membuatkan client penjual
```
kode
```

## SOAL 3
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:
a.	Terdapat 2 karakter Agmal dan Iraj
b.	Kedua karakter memiliki status yang unik
■	Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
■	Iraj memiliki Spirit_Status, di awal program memiliki status 100
■	Terdapat 3 Fitur utama
●	All Status, yaitu menampilkan status kedua sahabat
Ex: Agmal WakeUp_Status = 75 
      Iraj Spirit_Status = 30
●	“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
●	“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
■	Terdapat Kasus yang unik dimana:
●	Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
●	Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
■	Program akan berhenti jika Salah Satu :
●	WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
●	Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)
Syarat Menggunakan Lebih dari 1 Thread

```
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
```

## SOAL 4
### masih belum selesai
### kendala di penghentian program setelah 15 detik, tidak mau lanjut kembali
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 
➔	Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
➔	Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
➔	Ketika Mengekstrak file .zip juga harus secara bersama-sama
➔	Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
➔	Wajib Menggunakan Multithreading
➔	Boleh menggunakan system
```
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t treid3,treid1,treid2; /


void* ambil(){
        system("ps -aux | head -11  > /home/vinsensius009/Documents/FolderProses1/SimpanProses1.txt");
        system("ps -aux | head -11  > /home/vinsensius009/Documents/FolderProses2/SimpanProses2.txt");

}

void* zipkan (){
         system("zip -r /home/vinsensius009/Documents/FolderProses1/KompresProses1 /home/vinsensius009/Documents/FolderProses1/SimpanProses1.txt");
         system("rm /home/vinsensius009/Documents/FolderProses1/SimpanProses1.txt");
 
        system("zip -r /home/vinsensius009/Documents/FolderProses2/KompresProses2 /home/vinsensius009/Documents/FolderProses2/SimpanProses2.txt");
         system("rm /home/vinsensius009/Documents/FolderProses2/SimpanProses2.txt");

}


void* unzipkan1 (){

        system("unzip /home/vinsensius009/Documents/FolderProses1/KompresProses1 -d /home/vinsensius009/Documents/FolderProses1");
        system("unzip /home/vinsensius009/Documents/FolderProses2/KompresProses2 -d /home/vinsensius009/Documents/FolderProses2" );
}


int main(void)
{
//int waktu;
    pthread_create(&(treid1), NULL, ambil, NULL);
    pthread_join(treid1,NULL); 
    pthread_create(&(treid2), NULL, zipkan, NULL);
    pthread_join(treid2,NULL);
    printf("Menunggu 15 detik untuk mengekstrak kembali");
    
//sleep(5);
    printf("tes");
    pthread_create(&(treid3), NULL, unzipkan1, NULL);
    pthread_join(treid3, NULL);
// pthread_create(&(treid1), NULL, unzipkan1, NULL);

    return 0;
}
```
## SOAL 5
### Terdapat kendala,kurang sistem clear
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 
a.	Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
b.	Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
c.	Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
d.	Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.
e.	Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
f.	Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
■	Pembeli (terintegrasi dengan game)
●	Dapat mengecek stok makanan yang ada di toko.
●	Jika stok ada, pembeli dapat membeli makanan.
■	Penjual (terpisah)
●	Bisa mengecek stok makanan yang ada di toko
●	Penjual dapat menambah stok makanan.
	Spesifikasi program:
A.	Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
B.	Program terdiri dari 3 scene yaitu standby, battle, dan shop.
C.	Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

Standby Mode
Health : [health status]
Hunger : [hunger status]
Hygiene : [hygiene status]
Food left : [your food stock]
Bath will be ready in [cooldown]s
Choices
1.	Eat
2.	Bath
3.	Battle
4.	Shop
5.	Exit

D.	Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

Battle Mode
Monster’s Health : [health status]
Enemy’s Health : [enemy health status]
Choices
1.	Attack
2.	Run

E.	Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

		Shop Mode
		Shop food stock : [shop food stock]
		Your food stock : [your food stock]
		Choices
1.	Buy
2.	Back
### jawaban
membuatkan program pengguna
```
```

F.	Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop
Food stock : [shop food stock]
Choices
1.	Restock
2.	Exit

G.	Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))
### jawaban
membuatkan program penjual
```
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
kode
```
