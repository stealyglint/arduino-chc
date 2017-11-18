#define RL1 10  // relay 1 will be on PIN 10
#define LED1 11
#define SW1 2
#define SW2 3

boolean demand = HIGH;
boolean chstate = LOW;

void setup() {
  // put your setup code here, to run once:
// initialize digital pins RL1 LED1 SW1 SW2 and set RL1 to off.
  pinMode(RL1, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  digitalWrite(RL1, demand);
}

void loop() {
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
    
    delay(3000);
    chstate = LOW;
   }
 }
