# Documentation 

Ini adalah dokumentasi tentang bagaimana code ini
<br/>berjalan sesuai yang kita inginkan agar menjadi fitur O-TOILET.
<br>Lalu Dibawah Ini Adalah Tahap Membuat Code Tersebut.

<h1>1. Mendefinisikan Variable Code</h1>

```ino
//pin servo
#define servoPin 33

//pin sensor water
#define signalWater 13

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

```


<h1>2. Membuat Variable Penentu</h1>

```ino

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

```

<h1>


<h1>3. SETUP Pin ESP32 </h1>

```ino
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

```



<h1>4. Memprogram Systemnya Agar Sesuai Kebutuhan Kita </h1>

```ino
void loop() {
  //LED definition programs
  digitalWrite(pinLED, STATUSLED);
  digitalWrite(pinLEDG, STATUSLEDR);
  digitalWrite(pinLEDG, STATUSLEDG);
  digitalWrite(pinLEDB, STATUSLEDB);
  digitalWrite(generatorAir, STATUSGENERATORAIR);
  delay(200);
  
  currentState = digitalRead(pinTOUCHD);
  if(doorOpen == 0 && statusTouchD == LOW && currentState == HIGH) {
    if(STATUSLEDG == HIGH) {
      doorOpen = 1;
      STATUSLEDG = LOW;
      STATUSLEDR = HIGH;
    }
    Serial.println("Door Open");
    myservo.write(180);
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
    myservo.write(180);
    digitalWrite(pinLEDG, STATUSLEDG);
    digitalWrite(pinLEDR, STATUSLEDR);
    delay(2000);
    myservo.write(0);
    statusTouchB = HIGH;
    statusTouchD = LOW;
  }

  delay(500);

  waterLevel = analogRead(signalWater);
  Serial.println(waterLevel);
  if(waterLevel > 1600) {
    Serial.println("Water Level High");
    STATUSGENERATORAIR = LOW;
    digitalWrite(generatorAir, STATUSGENERATORAIR);
    delay(3000);
  }
  if(waterLevel < 1600){
    Serial.println("Water Level LOW");
    STATUSGENERATORAIR = HIGH;
    digitalWrite(generatorAir, STATUSGENERATORAIR);
    delay(3000);
  }

  delay(500);

  drakState = digitalRead(pinDark);
  if(drakState == LOW) {
    Serial.println("Lampu Kamar Mandi Menyala");
    STATUSLED = HIGH;
    digitalWrite(pinLED, STATUSLED);
    delay(800);
  }

  if(drakState == HIGH) {
    Serial.println("Lampu Kamar Mandi Menyala");
    STATUSLED = LOW;
    digitalWrite(pinLED, STATUSLED);
    delay(800);
  }

  Serial.println("");
  delay(500);

}



```
