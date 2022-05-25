/* NOTE: In this short sketch I am trying to determine how to
 *  cycle through an array using buttons and store values
 * 
 */


#include "Wire.h"
int switchPin = 11;
int enterPin = 12;
int hour[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
              13 , 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
              
int minute[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
                14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 
                26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 
                38,39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 
                50, 51, 52, 53, 54, 55, 56, 57, 58, 59};
int hourAl;
int minAl;
int index; 
int counter = 0;

void hourC(){
  if(digitalRead(switchPin) == LOW){
    counter++;
    Serial.println(counter);
  }
  if(counter >= 24){
    counter = 0;
  }
  
}

bool counting = true;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(enterPin, INPUT_PULLUP);
  Serial.print("Begin");
  delay(1000);


   /* while(counting){
    hourC();
    if(digitalRead(enterPin) == LOW){
      hourAl = counter;
      counting = false;
    }
  }
  Serial.print(hourAl );*/

  for(index = 0; index < 25; index++)
  {
    //while(counting){
      
    
    if(digitalRead(switchPin == LOW)){
      Serial.println(hour[index]);
    }
    else if(digitalRead(enterPin == LOW)){
      hourAl = hour[index];
    //}
    }
    else if
    
  }

 
}

void loop() {
  // put your main code here, to run repeatedly:
  /*for(index = 0; index < 25; index++);
  {
    if(digitalRead(switchPin == LOW)){
      Serial.println(index);
    }
    else
    {
      Serial.println();
    }
    if(digitalRead(enterPin == LOW)){
      hourAl = index;
    }
    delay(1000);
  }*/

  
  
}
