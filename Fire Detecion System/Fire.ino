//FIRE SYSTEM (send data)

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define Flame_sensor 3 //Flame sensor
#define pump 7 // Water pump
#define BMS 4 // Fire to BMS  

int Flame_detected;

RF24 radio(10, 9); // CE, CSN

//const byte address [][6] = {"00001","00004"};
const uint64_t pipe[2]={0x121212121BLL,0x1212121213LL};

void setup() {

  Serial.begin(9600);
  
  pinMode(Flame_sensor, INPUT);
  pinMode(pump, OUTPUT);
  pinMode(BMS, OUTPUT);

  
  radio.begin();
  radio.openWritingPipe(pipe[0]);
  radio.openReadingPipe(1,pipe[1]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}


void loop() {

  Flame_detected = digitalRead(Flame_sensor);
  
  
  Serial.print("Flame_detected=");
  Serial.print(Flame_detected);
  Serial.println(""); 

// Pump Action
 if (Flame_detected == 1)
  {
    Serial.println("Pump ON");
     Serial.println("");
    digitalWrite(pump,HIGH);
    digitalWrite(BMS,HIGH);

  }
  else 
  {
    Serial.println("Pump OFF");
    Serial.println("");
    digitalWrite(pump,LOW);
    digitalWrite(BMS,LOW);
    
  }

}
