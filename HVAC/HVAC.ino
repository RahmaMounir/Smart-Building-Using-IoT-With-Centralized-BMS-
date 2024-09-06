//DHT&FAN RECEIVE ---- HVAC-----

//#include <SoftwareSerial.h>
#include "DHT.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//SoftwareSerial nodemcu(5,6);

#define DHTPIN 4           // Arduino pin connected to relay which connected to DHT sensor
#define DHTTYPE DHT22
#define BMS 8
 
int RELAY1 = 5;  //fan1
int RELAY2= 6;  //fan2
int fan3 = 3 ; //fan 3
 


const int TEMP_THRESHOLD_UPPER = 26; // upper threshold of temperature, change to your desire value
const int TEMP_THRESHOLD_LOWER = 20; // lower threshold of temperature, change to your desire value

//nRF Variables ----------------------


RF24 radio(10,9); // CE, CSN

//const byte  [][6] = {"00001 ,00005 "};
const uint64_t pipe[2]={0x121212121CLL,0x1212121214LL};

//DHT ------------------------

DHT dht(DHTPIN, DHTTYPE);
float hum;  //Stores humidity value
float temp; //Stores temperature value
float temperature;    // temperature in Celsius
String tempdata="";
//FIRE-----------------------


void setup() {
  
  Serial.begin(9600);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(BMS, INPUT);
  
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(fan3, HIGH);
  
 

  dht.begin();        // initialize the sensor

  radio.begin();
  radio.openReadingPipe(1, pipe[1]);
  radio.openWritingPipe(pipe[0]);
  radio.setPALevel(RF24_PA_MIN);
  
  radio.enableDynamicPayloads();

  radio.stopListening();
  
 
}

void loop() {

   int state=digitalRead(BMS);

  if(state==1)
  {
    digitalWrite(RELAY1, HIGH); //FAN off
    digitalWrite(RELAY2, HIGH);
    Serial.println("Fans OFF");

  }
  else
  {
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    tempdata=temp;
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %");
    Serial.println("");
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    Serial.println("");
    delay(1000); //Delay 2 sec.


   
    byte tempdataArray[32];
    tempdata.getBytes(tempdataArray,32);    

    
      while(1){
    radio.write(&tempdataArray, sizeof(tempdataArray));
    
   delay(3000);
   break;
      }
    digitalWrite(RELAY1, LOW);
  
     if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    Serial.println("");
    delay(500);
  } 
    else {
           if(temp > TEMP_THRESHOLD_UPPER ){
           Serial.println("The fan is turned on");
           Serial.println("");
           digitalWrite(RELAY2, LOW); // turn on
     
          } 
          else if(temp < TEMP_THRESHOLD_LOWER){
                Serial.println("The fan is turned off");
                Serial.println("");
                digitalWrite(RELAY2, HIGH); // turn off
          }
  }
      
  }
    

   // read temperature in Celsius
   
   
}
   
