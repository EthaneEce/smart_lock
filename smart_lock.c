#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include "lib/pthread.h"
#include "python3.7m/Python.h"
#define RED 8
#define GREEN 9


void* check_rfid_is_accepted (void* arg) ;
void* launch_reco (void* arg) ;
static pid_t pid = 0;


int main(int argc, char * argv []){
    
    
    //Setup pins
    wiringPiSetup();
    pinMode(GREEN, OUTPUT); //Green Led
    pinMode(RED, OUTPUT); //Red Led
    
    
    pthread_t t2,t1;
    pthread_create(&t2,NULL,check_rfid_is_accepted,NULL);
    pthread_create(&t1,NULL,launch_reco,NULL);
    
    pthread_join(t2,NULL);
    pthread_join(t1,NULL);

    
    printf ( "Sortie du main \n") ;
    return 0;
}

void* check_rfid_is_accepted (void* arg){
    int rfid_reco;
    FILE* fichier = NULL;
    printf("dans check");
    
    for(;;)
    {
        
        //Read file where is printed if rfid is allowed or not
        fichier = fopen("rfid_is_accepted.txt", "r");
        if (fichier != NULL){
            fscanf(fichier,"%d",&rfid_reco);// On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
            //printf("\nj'ai lu :%d",rfid_reco);
            printf("\n%d",rfid_reco);
        }
        fclose(fichier);
        
        //Make the door open or not depending of rfid badge
        if(rfid_reco == 1){
            //Badge allowed
            printf("Read 1");
            digitalWrite(GREEN, HIGH);
            digitalWrite(RED, LOW);
        }    
        else if(rfid_reco == 0){
        
            //Badge not allowed
            digitalWrite(GREEN, LOW);
            digitalWrite(RED, HIGH);
        
        }else{
            printf("Read nothing");
            digitalWrite(GREEN, LOW);
            digitalWrite(RED, LOW);
        }
    }
}



void* launch_reco (void* arg)
{
    FILE* fp;
    
    Py_Initialize();
    fp = fopen("features/read_rfid_uid.py", "r");
    PyRun_SimpleFile(fp,"read_rfid_uid.py");
    
    Py_Finalize();
}
