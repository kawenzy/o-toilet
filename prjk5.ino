#include <ESP32Servo.h>

//pin servo
#define servoPin 3

//pin sensor water
#define signalWater 2

//pin generator water
#define generatorAir 23

//pin led penanda
#define pinLED 15
#define pinLEDG 4
#define pinLEDR 2
#define pinLEDB 5

//pin touch sensor
#define pinTOUCHD 12
#define pinTOUCHB 14

//pin dark sensor
#define pinDark 19


//variable penentu
int status = 0;
int doorOpen = 0;
int servoAngle = 0;
int statusTouchD = LOW;
int statusTouchB = HIGH;
int STATUSLED = LOW;
int STATUSLEDB = LOW;
int STATUSLEDG = HIGH;
int STATUSLEDR = LOW;
int STATUSGENERATORAIR = LOW;


//definition
int currentState;
int previousState;
int waterLevel;
int drakState;

Servo myservo;


void setup() {
  Serial.begin(9600);
  Serial.println("hello word");
  //SERVP SETUP
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);
  myservo.write(0);
  //WATER LEVEL SETUP
  pinMode(signalWater, INPUT);
  //GENERATOR AIR SETUP
  pinMode(generatorAir, OUTPUT);
  digitalWrite(generatorAir, STATUSGENERATORAIR);
  //LED SETUP
  pinMode(pinLED, OUTPUT);
  pinMode(pinLEDG, OUTPUT);
  pinMode(pinLEDR, OUTPUT);
  pinMode(pinLEDB, OUTPUT);
  //TOUCH SENSOR SETUP
  pinMode(pinTOUCHD, INPUT);
  pinMode(pinTOUCHB, INPUT);
  //darkSensor setup
  pinMode(pinDark, INPUT);
}

void loop() {
  //LED definition programs
  digitalWrite(pinLED, STATUSLED);
  digitalWrite(pinLEDG, STATUSLEDR);
  digitalWrite(pinLEDG, STATUSLEDG);
  digitalWrite(pinLEDB, STATUSLEDB);
  delay(200);
  
  currentState = digitalRead(pinTOUCHD);
  if(doorOpen == 0 && statusTouchD == LOW && currentState == HIGH) {
    if(STATUSLEDG == HIGH) {
      doorOpen = 1;
      STATUSLEDG = LOW;
      STATUSLEDR = HIGH;
    }
    Serial.println("Door Open");
    myservo.write(90);
    digitalWrite(pinLEDG, STATUSLEDG);
    digitalWrite(pinLEDR, STATUSLEDR);
    delay(2000);
    myservo.write(0);
    statusTouchD = HIGH;
    statusTouchB = LOW;
  }

  delay(500);

  previousState = digitalRead(pinTOUCHB);
  if(doorOpen == 1 && statusTouchB == LOW && previousState == HIGH){
    if(STATUSLEDR == HIGH) {
      doorOpen = 0;
      STATUSLEDR = LOW;
      STATUSLEDG = HIGH;
    }
    Serial.println("Door Close");
    myservo.write(90);
    digitalWrite(pinLEDG, STATUSLEDG);
    digitalWrite(pinLEDR, STATUSLEDR);
    delay(2000);
    myservo.write(0);
    statusTouchB = HIGH;
    statusTouchD = LOW;
  }

  delay(500);

  waterLevel = analogRead(signalWater);
  if(waterLevel < 2300) {
    Serial.println("Water Level High");
    STATUSGENERATORAIR = HIGH;
    digitalWrite(pinGENERATORAIR, STATUSGENERATORAIR);
    delay(3000);
    if(waterLevel > 2300){
      STATUSGENERATORAIR = LOW;
      digitalWrite(pinGENERATORAIR, STATUSGENERATORAIR);
    }
    delay(500);
  }

  delay(500);

  drakState = digitalRead(pinDark);
  if(drakState == LOW) {
    Serial.println("Lampu Kamar Mandi Menyala");
    STATUSLED = HIGH;
    digitalWrite(pinLED, STATUSLED);
    delay(800);
  }

  Serial.println("");
  delay(500);

}

