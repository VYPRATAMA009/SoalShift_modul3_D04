#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

char str[300];
pthread_t treid1, treid3;

void* ambil(){
        system("ps -aux | head -11  > /home/vinsensius009/Documents/FolderProses1/SimpanProses1.txt");
        system("ps -aux | head -11  > /home/vinsensius009/Documents/FolderProses2/SimpanProses2.txt");

//}

//void* zipkan ()
//{     
        strcpy(str, "");
        sprintf(str, "zip -qmj /home/vinsensius009/Documents/FolderProses1/KompresProses1 /home/vinsensius009/Documents/FolderProses1/SimpanProses1.txt");
        system(str); 
        system("rm /home/vinsensius009/Documents/FolderProses1/SimpanProses1.txt");
        (str, "");
        sprintf(str, "zip -qmj /home/vinsensius009/Documents/FolderProses2/KompresProses2 /home/vinsensius009/Documents/FolderProses2/SimpanProses2.txt");
        system(str);         
        system("rm /home/vinsensius009/Documents/FolderProses2/SimpanProses2.txt");

}


void* unzipkan1 (){

        system("unzip /home/vinsensius009/Documents/FolderProses1/KompresProses1 -d /home/vinsensius009/Documents/FolderProses1");
        system("unzip /home/vinsensius009/Documents/FolderProses2/KompresProses2 -d /home/vinsensius009/Documents/FolderProses2" );
}


int main(void){
    pthread_create(&(treid1), NULL, ambil, NULL);
    pthread_join(treid1,NULL); 
    //pthread_create(&(treid2), NULL, zipkan, NULL);
    //pthread_join(treid2,NULL);
    printf("Menunggu 15 detik untuk mengekstrak kembali");
    
    sleep(15);
    printf("proses finish");
    pthread_create(&(treid3), NULL, unzipkan1, NULL);
    pthread_join(treid3, NULL);
// pthread_create(&(treid1), NULL, unzipkan1, NULL);

    return 0;
}

