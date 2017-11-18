#include <Wire.h>
#include "RTClib.h"

#define RL1 10  // relay 1 will be on PIN 10
#define LED1 11
#define SW1 2
#define SW2 3

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

boolean demand = HIGH;
boolean chstate = LOW;



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
// initialize digital pins RL1 LED1 SW1 SW2 and set RL1 to off.
  pinMode(RL1, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  digitalWrite(RL1, demand);
}

void loop(){
  // Main loop for controller:
 
  if (digitalRead(SW1) == HIGH)
  {
    if (demand == LOW){
        demand = HIGH;
         delay(250);
         chstate = HIGH;
      }
     else if (demand == HIGH){
        demand = LOW;
         delay(250);
         chstate = HIGH;
     }
   }

   if (chstate == HIGH){
    digitalWrite(RL1, demand);
    showDate(demand);
    delay(3000);
    chstate = LOW;
    
   }

 }

void showDate(boolean state) {
  DateTime now = rtc.now();

  if (state==LOW){
      
     Serial.print("Heating Switched ON!  " );
    }
  else if ( state==HIGH) {
    Serial.print("Heating Switched OFF!  " );
  }
  
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    print2digits(now.hour());
    Serial.print(':');
   print2digits(now.minute());
    Serial.print(':');
   print2digits(now.second());
   
    Serial.println();

}

 void print2digits(int number) {
  if (number < 10) {
    Serial.print("0"); // print a 0 before if the number is < than 10
  }
  Serial.print(number);
}
