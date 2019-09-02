#include <LiquidCrystal.h>

#include <Servo.h>

#include <SoftwareSerial.h>

SoftwareSerial BT(7,8);
int buzz=A0;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
Servo servo;
int ang;
//OTHERS
unsigned long H=0;
unsigned long L=0;
unsigned long r=0;


int data;
int moto1=2;
int moto2=3;
int moto3=4;
int moto4=5;
int en=6;
int x=255;


unsigned long a;
unsigned long b;
int c=1;
int trigPin = 10;
int echoPin = 11;
int duration;
int distance;


int FL=12;
int BL=13;





void setup() {
  // put your setup code here, to run once:
  
  
  Serial.begin(9600);

  // Print a message to the LCD.
  
  
  BT.begin(9600);
  pinMode(moto1,OUTPUT);
  pinMode(moto2,OUTPUT);
  pinMode(moto3,OUTPUT);
  pinMode(moto4,OUTPUT);
    pinMode(en,OUTPUT);
 digitalWrite(en,HIGH);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT);
//servo.attach(9);
pinMode(A0,OUTPUT);
pinMode(FL,OUTPUT);
pinMode(BL,OUTPUT);}


void loop() {
  // put your main code here, to run repeatedly:
  
digitalWrite(en,HIGH);
  
  
  if (BT.available()) 
  {
    data = BT.read();
    Serial.println(data);
  }
  if (Serial.available()) 
  {
    BT.write(Serial.read());
  }

 
  //AI from here

/*
 * char c = 'a';
 * char * cp = ['a', 'b'];
 * 
 * cp[1];
 * 
 * c == 'd';
 * int x = 10;
 * x == 10;
*/

//////////////////////ULTRA SONIC HERE


/*

a=millis();
  digitalWrite(trigPin, HIGH);
  if(a>=b+c){
    b=millis();
  digitalWrite(trigPin, LOW);
  }
  duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;

if(distance<0){
distance=0;
}
*/
//Bluetooth from here
  if(data==83 || data==7 || distance<=15) {
    digitalWrite(moto1,LOW);
    digitalWrite(moto4,LOW);
    digitalWrite(moto3,LOW);
    digitalWrite(moto2,LOW);
   /* if (distance<=15){
      tone(buzz,1);
    }
  if (distance>15){
   noTone(buzz);
  }*/
  }
  
  if(data==70 || data==1){
    digitalWrite(moto1,HIGH);
    digitalWrite(moto4,HIGH);
    digitalWrite(moto3,LOW);
   digitalWrite(moto2,LOW);
  }
    if(data==66 || data==2){
    digitalWrite(moto2,HIGH);
    digitalWrite(moto3,HIGH);
      digitalWrite(moto1,LOW);
      digitalWrite(moto4,LOW);
  }
  if(data==76 || data==4){
    digitalWrite(moto1,HIGH);
    digitalWrite(moto3,HIGH);
  digitalWrite(moto4,LOW);
  digitalWrite(moto2,LOW);
  }
   if(data==82 || data==3){
    digitalWrite(moto2,HIGH);
    digitalWrite(moto4,HIGH);
  digitalWrite(moto1,LOW);
  digitalWrite(moto3,LOW);
  }
    if(data==73 || data==6){
    
    digitalWrite(moto4,HIGH);
    digitalWrite(moto1,LOW); 
    digitalWrite(moto3,LOW);
    digitalWrite(moto2,LOW);
  }
  if(data==71 || data==5){
    
    digitalWrite(moto4,LOW);
    digitalWrite(moto1,HIGH); 
    digitalWrite(moto3,LOW);
    digitalWrite(moto2,LOW);
  } 
if(data==72 ){
    
    digitalWrite(moto4,LOW);
    digitalWrite(moto1,LOW); 
    digitalWrite(moto2,HIGH);
    digitalWrite(moto3,LOW);
  }
  if(data==74 ){
    
    digitalWrite(moto4,LOW);
    digitalWrite(moto1,LOW); 
    digitalWrite(moto2,LOW);
    digitalWrite(moto3,HIGH);
  }
    if(data==87){
      digitalWrite(FL,HIGH);
    }
     if(data==119){
      digitalWrite(FL,LOW);
    }
  if(data==85){
      digitalWrite(BL,HIGH);
    }
     if(data==117){
      digitalWrite(BL,LOW);
    }
  if(data==86){
      tone(buzz,1);
    }
     if(data==118){
      noTone(buzz);
    }
    if(data==88){
   
       lcd.setCursor(1,0);
  lcd.print("       13      ");
  lcd.setCursor(1,1);
 lcd.print("");
      //digitalWrite(BL,HIGH);
      //digitalWrite(FL,HIGH);
    }
     if(data==120){
   
      lcd.clear();

      //digitalWrite(BL,LOW);
      //digitalWrite(FL,LOW);
    }
  
  }