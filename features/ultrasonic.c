#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
 
#define TRUE 1
 
#define TRIG 1
#define ECHO 27 
 
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

void writeToReadUlt(char toWrite){
    FILE* fichier = NULL;
    fichier = fopen("./features/readUlt.txt", "w"); 
    if (fichier != NULL)
        {
            fprintf(fichier,toWrite); // On affiche la chaîne
            fclose(fichier);
        }
}
 
int main(void) {
    setup();
    printf("\n[INFO] Module télémètre ultrason initialisé");
    
    while (1)
    {
        int dist=getCM();
        //printf("Distance: %dcm\n", dist);
        if(dist<30){
            printf("[INFO] Lancement de la reconnaissance faciale pour 10s\n");           
            writeToReadUlt("1");
            delay(100);
            writeToReadUlt("0");                
            sleep(15);
        }
        delay(100);
    };
  
 
    return 0;
}
