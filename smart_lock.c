#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include "lib/pthread.h"
#define RED 3
#define GREEN 5

void* launch_reco (void* arg) ;

int main(int argc, char * argv []){
    printf("Hello World!\n");
    static pid_t pid = 0;
    
    //Setup pins
    wiringPiSetup();
    pinMode(GREEN, OUTPUT); //Green Led
    pinMode(RED, OUTPUT); //Red Led
    
    //Declare trhreads
    int i, nbFunc=1;
    pthread_t fils[nbFunc];
    void* fonctions[1] = {check_rfid_is_accepted};
    //Execute threads
    for(i=0; i<nbFunc; i++){
        if(pthread_create(&fils[i], NULL, fonctions[i],NULL))
            perror("pthread_create la fonction");
    }

    char rfid_reco;
    FILE* fichier = NULL;
    for(;;)
    {
        //Read file where is printed if rfid is allowed or not
        fichier = fopen("./features/rfid_is_accepted.txt", "r");
        if (fichier != NULL)
            rfid_reco=fgetc(fichier); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"

        fclose(fichier);
        
        //Make the door open or not depending of rfid badge
        if(rfid_reco == '1'){
            //Badge allowed
            digitalWrite(GREEN, HIGH);
            digitalWrite(RED, LOW);
        }    
        else if(rfid_reco == '0'){
            //Badge not allowed
            digitalWrite(GREEN, LOW);
            digitalWrite(RED, HIGH);
        
        }else{
            printf("Read nothing");
        }
    }
    
    printf ( "Sortie du main \n") ;
    return 0;
}


void* launch_reco (void* arg)
{
    if ((pid = fork()) == 0)
        system("./features/read_rfid_uid.py"); //Run rfid recognition
    pthread_exit (0);
}
