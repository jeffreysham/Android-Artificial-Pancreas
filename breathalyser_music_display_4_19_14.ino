 #include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

#include <LiquidCrystal.h>
#include <SD.h>  
#define SD_ChipSelectPin 53
const int analogPin = 0;    // the pin that the potentiometer is attached to
const int ledCount = 7;    // the number of LEDs in the bar graph
//for the lcd display
LiquidCrystal lcd(7,6,5,4,3,2);
TMRpcm tmrpcm;   // create an object for use in this sketch  
int ledPins[] = {22,24,26,28,30,32,34};  // Here we have the number of LEDs to use in the BarGraph
int ledPin = 38; //led to check if system is on
int number = 0;
void setup() {
  Serial.begin(9600);
  lcd.begin(20,4);
  
  lcd.print("Breathe into the sensor.");
  
  pinMode(ledPin,OUTPUT);
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
  tmrpcm.speakerPin = 11; //11 on Mega, 9 on Uno, Nano, etc
  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  
  tmrpcm.setVolume(7);
}
 
void loop() {
  //This is the code to light up LED's
  lcd.clear();
  lcd.print("Breathe into the sensor.");
  delay(1000);
  int sensorReading = analogRead(analogPin);
  
  int ledLevel = map(sensorReading, 500, 1023, 0, ledCount);
  
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
   
    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH);
    }
 
    else {
      digitalWrite(ledPins[thisLed], LOW);
    }
    digitalWrite(ledPin,HIGH);
    delay(500);
    digitalWrite(ledPin,LOW);
    
  }

    lcd.clear();
    if(ledLevel ==1){
      lcd.print("Feeling it.");
      tmrpcm.play("tone.wav",5);//1 light disable in 4 secs
      delay(4000);
      tmrpcm.disable();
    }
    if(ledLevel ==2){
      lcd.print("Buzzed.");
      tmrpcm.play("tone.wav",11); //2 light disable in 3 secs
      delay(3000);
      tmrpcm.disable();
    }
    if(ledLevel ==3){
      lcd.print("Tipsy.");
      tmrpcm.play("tone.wav",16); //3 light disable in 4 secs
      delay(4000);
      tmrpcm.disable();
    }
    if(ledLevel ==4){
      lcd.print("Sloppy.");
      tmrpcm.play("tone.wav",21); //4 light disable in 4 secs
      delay(4000);
      tmrpcm.disable();
    }
    if(ledLevel ==5){
      lcd.print("Reckless.");
      tmrpcm.play("tone.wav",26); //5 light disable in 4 secs
      delay(4000);
      tmrpcm.disable();
    }
    if(ledLevel ==6){
      lcd.print("Hammered.");
      tmrpcm.play("tone.wav",32); //6 light disable in 7 secs
      delay(7000);
      tmrpcm.disable();
    }
    if(ledLevel ==7){
      lcd.print("Blackout.");
      tmrpcm.play("tone.wav",41); //7 light disable in 11 secs
      delay(11000);
      tmrpcm.disable();
    }
  if (number<ledLevel){
     number = ledLevel;
     lcd.clear();
     lcd.print("New High Score!");
     tmrpcm.play("tone.wav",53); //high score disable in 4 secs
     delay(4000);
     tmrpcm.disable();
  }
  
}
