int LAMP =  8 ; //pir lamp
int LAMP2 =  7 ;// choose the pin for the RELAY
int PIR= 4  ;
//int PIR1= 10; 
int trigPin = 9;
int echoPin = 10;  // choose the input pin (for PIR sensor)                 
void setup()
{    
Serial.begin(9600);
  pinMode(LAMP, OUTPUT); 
  pinMode(LAMP2, OUTPUT);// declare SSlamp as output
  pinMode(PIR,INPUT); 
  //pinMode(PIR1,INPUT);// declare sensor as input   
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);    
}
                                                                                                                       
void loop() 


{
  long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/8)/58.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(10);
 
// if((distance<=10)) 
  //{
    //digitalWrite(led, HIGH);
//}
   //else if(distance>10)
 //{
   //  digitalWrite(led, LOW);
   //}

  
  
    int value_ldr = analogRead(A0); // read LDR value
  int value_pir = digitalRead(PIR); 
 //int value_pir1 = digitalRead(PIR1); 
//88// read input value
  Serial.println("LDR value");
  Serial.println(value_ldr);
  delay(1000);
  Serial.println("PIR value");
  Serial.println(value_pir);
   //Serial.println("PIR1 value");
  //Serial.println(value_pir1);



  if((300>value_ldr) && (distance<=10))
 {
       digitalWrite(LAMP,HIGH);  // Turn ON the light
      delay(500);
       
}
else {
  
       digitalWrite(LAMP,LOW); // Turn OFF the light
       
}
 if ( value_pir==HIGH) 
 {
       digitalWrite(LAMP2,HIGH);  // Turn ON the light
      delay(500);
       
}
else {
  
       digitalWrite(LAMP2,LOW); // Turn OFF the light
       
}


 }
