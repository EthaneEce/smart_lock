#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include "lib/pthread.h"
#include "python3.7m/Python.h"
#define RED 8
#define GREEN 9


void* check_rfid_is_accepted (void* arg) ;
void* check_freco_is_accepted (void* arg) ;
void* launch_reco_rfid (void* arg) ;
void* launch_reco_face (void* arg) ;
void* launch_reco_ulrasonic (void* arg) ;

int main(int argc, char * argv []){
    printf("[INFO] Démarrage des modules...")
    //Setup pins
    wiringPiSetup();
    pinMode(GREEN, OUTPUT); //Green Led
    pinMode(RED, OUTPUT); //Red Led
    
    pthread_t t2,t1,t3,t4,t5;
    pthread_create(&t2,NULL,check_rfid_is_accepted,NULL);
    pthread_create(&t1,NULL,launch_reco_rfid,NULL);
    pthread_create(&t3,NULL,launch_reco_face,NULL);
    pthread_create(&t4,NULL,check_freco_is_accepted,NULL);
    pthread_create(&t5,NULL,launch_reco_ulrasonic,NULL);
    
    pthread_join(t3,NULL);
    pthread_join(t2,NULL);
    pthread_join(t1,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
   
    return 0;
}

void* check_rfid_is_accepted (void* arg){
    int rfid_reco,precSate;
    FILE* fichier = NULL;
    
    for(;;)
    {
        
        //Read file where is printed if rfid is allowed or not
        fichier = fopen("rfid_is_accepted.txt", "r");
        if (fichier != NULL){
            fscanf(fichier,"%d",&rfid_reco);// On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
            //printf("\nj'ai lu :%d",rfid_reco);
            //
            //printf("\n%d",rfid_reco);
        }
        fclose(fichier);
        
        //Make the door open or not depending of rfid badge
        if(rfid_reco == 1){
            //Badge allowed
            printf("\n[INFO] Allumage de la LED verte");
            digitalWrite(GREEN, HIGH);
            digitalWrite(RED, LOW);
            sleep(3);
            digitalWrite(GREEN, LOW);
            digitalWrite(RED, LOW);
        }    
        else if(rfid_reco == 0){
            printf("\n[INFO] Allumage de la LED rouge");
            //Badge not allowed
            digitalWrite(GREEN, LOW);
            digitalWrite(RED, HIGH);
            sleep(3);
            digitalWrite(GREEN, LOW);
            digitalWrite(RED, LOW);
        
        }
        precSate=rfid_reco;
    }
}

void* launch_reco_face (void* arg){
    system("./features/face_reco");
}

void* launch_reco_ulrasonic (void* arg) {
    sleep(10);
    system("./features/ultrasonic");
}

void* check_freco_is_accepted (void* arg) {
    int face_reco;
    int precState=5;
    FILE* fichier = NULL;
    
    for(;;)
    {
        
        //Read file where is printed if rfid is allowed or not
        fichier = fopen("./features/resReco.txt", "r");
        if (fichier != NULL){
            fscanf(fichier,"%d",&face_reco);// On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
            //printf("\nj'ai lu :%d",face_reco);
            
        }
        fclose(fichier);
        
        //Make the door open or not depending of rfid badge
        if(face_reco == 1){
            //Badge allowed
            printf("\n[INFO] Allumage de la LED verte");
            digitalWrite(GREEN, HIGH);
            digitalWrite(RED, LOW);
            sleep(3);
            digitalWrite(GREEN, LOW);
            digitalWrite(RED, LOW);
        }    
        else if(face_reco == 0){
        printf("\n[INFO] Allumage de la LED verte");
            //Badge not allowed
            digitalWrite(GREEN, LOW);
            digitalWrite(RED, HIGH);
            sleep(3);
            digitalWrite(GREEN, LOW);
            digitalWrite(RED, LOW);
        
        }
        precState=face_reco;
    }
}

void* launch_reco_rfid (void* arg)
{
    FILE* fp;
    
    Py_Initialize();
    fp = fopen("features/read_rfid_uid.py", "r");
    PyRun_SimpleFile(fp,"read_rfid_uid.py");
    
    Py_Finalize();
}
