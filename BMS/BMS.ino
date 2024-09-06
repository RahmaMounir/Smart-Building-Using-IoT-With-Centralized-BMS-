//nRF24L01 communication 2 ways Arduino A

//e#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(53, 9); // CE, CSN

//const byte   addresses [][6] = {"00002", "00003","00004"};  //Setting the two addresses. One for   transmitting and one for receiving
const uint64_t pipe[4]={0x121212121ALL,0x121212121CLL,0x121212121DLL,0x121212121BLL};//BMS write, HVAC, Security

#define Fire 4
#define HVAC 8

float temp;

//int RF_ID =0  ;


void setup() {
  
 
  pinMode(HVAC, OUTPUT);
  pinMode(Fire, INPUT);
  
  digitalWrite(HVAC,LOW);
  digitalWrite(Fire,LOW);
  
  Serial.begin(9600);
 
  radio.begin();                           //Starting   the radio communication
  radio.openWritingPipe(pipe[0]);     //Setting   the address at which we will send the data
/*radio.openReadingPipe(1, pipe[1]);   //Setting the address at which we will receive the data
  radio.openReadingPipe(2, pipe[2]);
  radio.openReadingPipe(3, pipe[3]);*/  
  radio.setPALevel(RF24_PA_MIN);   //You can set it as minimum or maximum depending on the distance between the transmitter   and receiver. 
  radio.enableDynamicPayloads();
  radio.startListening();                    //This   sets the module as receiver          
  }

  

    
void loop() 
{ 

  
  for(int node=1;node<4;node++)
  
{ 
  radio.openReadingPipe(node, pipe[node]);   //Setting the address at which we will receive the data


  int state=digitalRead(Fire);
  if (state == 1)
  {
    digitalWrite(HVAC,HIGH);
    Serial.println("Fire Detected!!!");
    Serial.println("");
    }
    if (state==0)
    {
      
      digitalWrite(HVAC,LOW);
      Serial.println("No Fire.. Safe :)");
      Serial.println("");
    }


    
  uint8_t someVariable;
  if (radio.available(&someVariable))
  { 
    
      Serial.print("pipe number: ");
      Serial.println(someVariable);
      Serial.println("");
  
      //-- Received data Preparation ----
    byte tagIdArray[32];
    radio.read(&tagIdArray, sizeof(tagIdArray));
    String tagId = String((char*)tagIdArray);
  
    Serial.println(tagId);
    Serial.println("");

    String id=tagId;

    if (someVariable== 1)
    {
      Serial.print("Temperature = ");
      Serial.println(tagId);
      Serial.println("");
      
      }

      if (someVariable== 2)
    {
      
      Serial.println(tagId);
      Serial.println("");
      
      }
 

  }
   
  delay(1000);
}

}

  
  
