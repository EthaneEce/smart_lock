#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
 
#define TRUE 1
 
#define TRIG 1
#define ECHO 27
#define PORT 4444

static pid_t pid = 0;
char chaine[1000] = "";

void startReco(void) {
    if ((pid = fork()) == 0) {

        system("./recognize");
    }
}

void stopReco(void) {
    system("killall -2 recognize");
    sleep(2);
    
    FILE* fichier = NULL;
    fichier = fopen("resReco.txt", "r");
    bzero(chaine,strlen(chaine));// Chaîne vide de taille TAILLE_MAX
    if (fichier != NULL)
    {
        fgets(chaine, 1000, fichier); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
        printf("\n%s", chaine); // On affiche la chaîne
 
        fclose(fichier);
    }

    
}

 
 
 
 
void setup() {
        wiringPiSetup();
        pinMode(TRIG, OUTPUT);
        pinMode(ECHO, INPUT);
 
        //TRIG pin must start LOW
        digitalWrite(TRIG, LOW);
        delay(30);
}
 
int getCM() {
        //Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);
 
        //Wait for echo start
        while(digitalRead(ECHO) == LOW);
 
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO) == HIGH);
        long travelTime = micros() - startTime;
 
        //Get distance in cm
        int distance = travelTime / 58;
 
        return distance;
}
 
int main(void) {
    setup();
    
    
    
    
    while (1)
    {
        int dist=getCM();
        printf("Distance: %dcm\n", dist);
        if(dist<50){
                printf("Started reco for 20s");
                FILE* fichier = NULL;
                fichier = fopen("./features/readUlt.txt", "w");
                if (fichier != NULL)
                {

                    fprintf(fichier,"1"); // On affiche la chaîne
 
                    fclose(fichier);
                }

                delay(100);

                
                fichier = fopen("./features/readUlt.txt", "w");
                if (fichier != NULL)
                {

                    fprintf(fichier,"0"); // On affiche la chaîne
 
                    fclose(fichier);
                }
                
                sleep(15);
                
                

        }
         delay(100);
    };
  
 
    return 0;
}
