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



