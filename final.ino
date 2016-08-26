#include <Ultrasonic.h>
int data1 = 0, data2 = 0;
Ultrasonic ultrasonic1(2,3); 
Ultrasonic ultrasonic2(4,5); 
char msg = ' ';
void setup() {

  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT); 
 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT);
  
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}
void avant(){
  digitalWrite(8, HIGH); 
  digitalWrite(9, LOW);  
  analogWrite(10, 125); 
  digitalWrite(6,  HIGH); 
  digitalWrite(7, LOW);  
  analogWrite(11, 125); 

}
void arriere(){
  digitalWrite(9, HIGH); 
  digitalWrite(8, LOW);  
  analogWrite(10, 255); 
  digitalWrite(7, HIGH); 
  digitalWrite(6, LOW); 
  analogWrite(11, 255);  

}
void gauche(){
  digitalWrite(9, HIGH); 
  digitalWrite(8, LOW);  
  analogWrite(11, 255); 
  digitalWrite(6, LOW); 
  digitalWrite(7, LOW);
}
void droite(){
  digitalWrite(6, HIGH); 
  digitalWrite(7, LOW);  
  analogWrite(10, 255); 
  digitalWrite(9, LOW); 
  digitalWrite(8, LOW);  
}
void echange(){
  digitalWrite(9, HIGH); 
  digitalWrite(8, LOW);  
  analogWrite(10, 255); 
  digitalWrite(6, HIGH); 
  digitalWrite(7, LOW);  
  analogWrite(11, 255); 
}
void arret(){
  digitalWrite(6, LOW); 
  digitalWrite(7, LOW);  
  digitalWrite(9, LOW); 
  digitalWrite(8, LOW);  
}

void loop(){
while (Serial.available()>0){ 
  msg=Serial.read();
}

if (msg == 'D'){

  data1 = ultrasonic1.Ranging(CM); 
  Serial.flush();
  delay(100);
  
  data2 = ultrasonic2.Ranging(CM);
  Serial.flush();
  //delay(1000);  

    if (data1 >= 50 && data2 >= 50) {
      Serial.println("avant");
      Serial.flush();
      avant();
    }
    else if (data1 < 50 && data2 >= 50){
      Serial.println("droite");
      Serial.flush();
      droite();
    }
    else if (data1 >= 50 && data2 < 50){
      Serial.println("gauche");
      Serial.flush();
      gauche();
    }
    else if (data1 < 50 && data2 < 50){
      Serial.println("echange");
      arriere();
      delay(2000);
      echange();
      delay(3000); 
      Serial.flush();     
    }     
    else {
      arret();
    }
    
  
}
else if (msg == 'S'){
  arret();
  Serial.println("Stop");
}
else{
  arret();
  Serial.println("not read it");
}

}

