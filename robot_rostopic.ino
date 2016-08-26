#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Byte.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Char.h>
#include <Ultrasonic.h>

ros::NodeHandle nh;
int data1 = 0, data2 = 0;
//byte etat = ' ';
boolean fonctionne = false;

void messageCb (const std_msgs::Empty& toggle_msg){
  if (!fonctionne){
    fonctionne = true;
  }
  else{
    fonctionne = false;
    arret();
    pub(0);
  }
}
ros::Subscriber<std_msgs::Empty> sub("demmare", messageCb);


std_msgs::Char str_msg;
ros::Publisher chatter("etat", &str_msg);

Ultrasonic ultrasonic1(2,3); 
Ultrasonic ultrasonic2(4,5); 

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

nh.initNode();
nh.advertise(chatter);
nh.subscribe(sub);
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
void pub(byte etat){
  str_msg.data = etat;
  chatter.publish( &str_msg);
  nh.spinOnce();
  delay(500);
}
void loop() {

if (fonctionne){

  data1 = ultrasonic1.Ranging(CM); 
  Serial.flush();
  delay(100);
  
  data2 = ultrasonic2.Ranging(CM);
  Serial.flush();


    if (data1 >= 50 && data2 >= 50) {
      pub(1);      
      Serial.println("avant");
      Serial.flush();
      avant();
    }
    else if (data1 < 50 && data2 >= 50){
      pub(2);
      Serial.println("droite");
      Serial.flush();
      droite();
    }
    else if (data1 >= 50 && data2 < 50){
      pub(4);
      Serial.println("gauche");
      Serial.flush();
      gauche();
    }
    else if (data1 < 50 && data2 < 50){
      Serial.println("echange");
      pub(3);
      arriere();
      delay(1000);
      echange();
      delay(1000); 
      Serial.flush();     
    }       
}

else {
      arret();
      pub(0);
    }
}

