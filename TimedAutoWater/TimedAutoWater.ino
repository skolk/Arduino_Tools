/* These variables store the flash pattern
and the current state of the LED
 https://learn.adafruit.com/multi-tasking-the-arduino-part-1/now-for-two-at-once

positions: 
Freq: 
0: prime (ON) 
1 (250): 12hr //.6v
2 (500): 1day // 2.5
3 (750) :  3Days 4.4
4:(1000): 7Days 5

Amp: 
0: (OFF) 
1: 250
2: 500
3: 750
4: 1000 (1L) 


*/

#define TARGET_MCU ATTINY
//int ledPin =  0;      // test board
//
int ledPin =  2;      // ATTiny
//int ledPin =  13; // ATMega
int ledState = HIGH; // ledState used to set the LED
int freqREAD = A3; // (pin 2, U pattern) 
int ampREAD = A2; // (pin 3) 
#define Sprintln(a) (// ////Serial.println(a))

unsigned long lastRefreshTime = 0UL;
unsigned long previousMillis = 0UL;        // will store last time LED was updated
unsigned long OnTime = 0UL;           // milliseconds of on-time
unsigned long OffTime = 0UL; //        milliseconds of off-time
unsigned long oneSecond = 1000UL;
unsigned long oneHour = 3600000UL ; //60UL * 60UL * 1000UL;
unsigned long oneDay = 86400000UL; //24UL * 60UL * 60UL * 1000UL;



void setup()
{
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(freqREAD, INPUT);
  pinMode(ampREAD, INPUT);
  ledState = HIGH;
  digitalWrite(ledPin, ledState);
  OnTime = 0UL;
  OffTime = 2000UL;
  ////Serial.begin(9600);
  delay(3000);
}

void loop()
{
  UpdateEveryXms(500);
  TimedBlink1();
  TimedBlink2();
   ////Serial.println(" ------------------------------- ");
}

void TimedBlink1() {
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();
  ////Serial.println(" T1 currentMillis - previousMillis");
  ////Serial.println((currentMillis));
  ////Serial.println((previousMillis));
  ////Serial.println((currentMillis - previousMillis));
  ////Serial.println((OnTime));
  ////Serial.println("  ");
  
  if ((ledState == LOW) && ((currentMillis - previousMillis) >= OnTime))
  {
    ledState = HIGH;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
    ////Serial.println("                                                off");
  }
}
  
void TimedBlink2() {
  unsigned long currentMillis = millis();
  #if TARGET_MCU != ATTINY
  //Serial.println(" T2 currentMillis - previousMillis");
  //Serial.println((currentMillis));
  //Serial.println((previousMillis));
  //Serial.println((currentMillis - previousMillis));
  //Serial.println((OffTime));
  //Serial.println("  ");
  //Serial.println("  ");
  #endif

  if ((ledState == HIGH) && ((currentMillis - previousMillis) >= OffTime))
  {
    ledState = LOW;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(ledPin, ledState);    // Update the actual LED
    ////Serial.println("                                                  on");
  }
}

void UpdateEveryXms( unsigned long REFRESH_INTERVAL){
  unsigned long currentMills = millis();
  if ((currentMills - lastRefreshTime) >= REFRESH_INTERVAL) {
    lastRefreshTime = REFRESH_INTERVAL;
    UpdateFreqAmp();
    ////Serial.println("                 update");
  }
}

void UpdateFreqAmp() {
  OffTime = analogRead(freqREAD);
  ////Serial.println("* OffTime : ");
  ////Serial.println(OffTime);
  
  OnTime = analogRead(ampREAD);
   ////Serial.println("* OnTime : ");
  ////Serial.println(OnTime);
  ////Serial.println();
  
  if (OffTime < 70) {
    OffTime = 1UL;
    ////Serial.println("OFcase1");
  }
  else if ((350 > OffTime) && (OffTime  >= 70)) {
    //OffTime = 1000;
    OffTime = oneHour * 12UL;
    ////Serial.println("OFcase2");
  }
  else if ((600 > OffTime) && (OffTime >= 350)) {
    OffTime = oneDay;
     //OffTime = 5000;
     ////Serial.println("OFcase3");
  }
  else if ((800 > OffTime) && (OffTime >= 600)) {
    OffTime = oneDay * 3UL;
    ////Serial.println("OFcase4");
  }
   else if (OffTime >= 800) {
    OffTime = oneDay * 7UL;
    ////Serial.println("OFcase5");
  }
  ////Serial.println(OffTime);
  
   OnTime = OnTime * 100UL;
   ////Serial.println("OTcase1");
   ////Serial.println(OnTime);
}

