#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
 
#define TRUE 1
 
#define TRIG 4
#define ECHO 26
#define PORT 4444


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
         delay(100);
    };
  
 
    return 0;
}