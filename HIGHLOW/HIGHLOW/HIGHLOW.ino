#include <Arduino.h>


char user_input;
int x;
int y;
int z = 1000;
int state;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("ENTER h# for digiral write high");
  Serial.println("ENTER l# for digiral write low");
  Serial.println("ENTER r# to read");
  Serial.println("ENTER 1 to write all high ");
  Serial.println("ENTER 0 to write all low ");


  int a;
  for(a = 0; a < 52; a++){
       pinMode(a, OUTPUT);
  }
  int b;
   for(b = 0; b < 52; b++){
      digitalWrite(b, LOW);
      }
 }

void loop() {

  while (Serial.available()) {
    user_input = Serial.read(); //Read user input and trigger appropriate function


    if (user_input == '0') //f100 for forward 100
    {
      int a;
    for(a=0;a < 52;a++){
       pinMode(a, OUTPUT);
      }
      int b;
      for(b=0;b < 52;b++){
       digitalWrite(b, LOW);
      }
    }

    if (user_input == '1') //f100 for forward 100
    {
      int a;
    for(a=0;a < 52;a++){
       pinMode(a, OUTPUT);
      }
      int b;
      for(b=0;b < 52;b++){
       digitalWrite(b, HIGH);
      }
    }
    
    
    if (user_input == 'h')
    {
    int input = Serial.parseInt();
    Serial.print(input);
    Serial.println(" HIGH");
    pinMode(input, OUTPUT);
    digitalWrite(input, HIGH);
    
    }

    else if (user_input == 'l') 
    {
    int input = Serial.parseInt();
    Serial.print(input);
    Serial.println(" LOW");
    pinMode(input, OUTPUT);
    digitalWrite(input, LOW);
    
    }

     else if (user_input == 'r') 
    {
    int input = Serial.parseInt();
    pinMode(input, INPUT);
    digitalRead(input);
    Serial.print(input);
    }

    
    else
    {
      Serial.println("Invalid option entered.");
    }

  }
}

