// HEADER START

void setDir(int direction);
void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd);
void bt_main();
void line_main();
void wall_main();
long getDistance();


// sensor (jumper) pins
#define BT 11 // d2 d3 d4 for ir
#define WALL 12 // d5 d6 us 

// sensor pins
#define trig 6
#define echo 5
#define rx 8
#define tx 7
#define left 2
#define right 3

#define FWD 70
#define BKD 66
#define RHT_FWD 2
#define LFT_FWD 3
#define SOFT_RHT 4
#define SOFT_LFT
#define RHT 82
#define LFT 76

//L293D pins
#define rt_fwd A2
#define lt_fwd A4
#define lt_bkd A1
#define rt_bkd A5
#define enable A3

//extra only for the led
const int rs = 9, en = 10, d4 = 12, d5 = 11, d6 = A0, d7 = 13;

#include <SoftwareSerial.h>
#include <SoftPWM.h>
#include <SoftPWM_timer.h>
#include <LiquidCrystal.h>
#include <string.h>
#include <stdlib.h>


// HEADER END
SoftwareSerial bluetooth(7, 8);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String alphabets[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

void setup() {
  SoftPWMBegin();
  SoftPWMSet(rt_fwd, 0);
  SoftPWMSet(lt_fwd, 0);
  SoftPWMSet(rt_bkd, 0);
  SoftPWMSet(lt_bkd, 0);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(BT, INPUT);
  pinMode(enable, OUTPUT);
  pinMode(WALL, INPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
  randomSeed(1);
  lcd.begin(16,2);
  lcd.clear();
  lcd.home();
}


void loop() {
  // digitalWrite(enable, HIGH);
  // digitalRead(BT) == HIGH ? bt_main() : digitalRead(WALL) == HIGH ? wall_main() : line_main();
  // testPWM();
  // bt_main();
  coolPrint();
  delay(50000);
  }


void testPWM()
{
  int state;
    
  if(bluetooth.available()) {
    state = bluetooth.read();
  }
  
  if (state < 58){
  state -= 48;
  Serial.print("state before mapped is: " + String(state) + "\n");
  state = map(state, 0, 9, 0, 255);
  Serial.print("writing to enable with state: " + String(state) + "\n");
  analogWrite(enable, state);
  }
}


void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd)
{
  // Serial.println("Function writeMotors running with parameters %i, %i, %i, %i.", state_rt_fwd, state_lt_fwd, state_rt_bkd, state_lt_bkd);
  SoftPWMSetPercent(rt_fwd, state_rt_fwd);
  SoftPWMSetPercent(lt_fwd, state_lt_fwd);
  SoftPWMSetPercent(rt_bkd, state_rt_bkd);
  SoftPWMSetPercent(lt_bkd, state_lt_bkd);
}

void setDir(int direction){
  switch(direction){
    case FWD:
      writeMotors(100, 100, 0, 0);
    break;

    case BKD:
      writeMotors(0, 0, 100, 100);
    break;

    case RHT_FWD:
      writeMotors(25 , 100, 0, 0);
    break;

    case LFT_FWD:
      writeMotors(100, 25, 0, 0);
    break;

    case SOFT_RHT:
      writeMotors(50, 100, 0, 0);
      break;
    
    case SOFT_LFT:
      writeMotors(100, 50, 0, 0);
      break;

    case RHT:
      writeMotors(0, 100, 100, 0);
    break;

    case LFT:
      writeMotors(100, 0, 0, 100);
    break;

    default:
      writeMotors(0, 0, 0, 0);
    break;
  }
}

void line_main(){
   while(true)
   {
     int Left = digitalRead(left);
     int Right = digitalRead(right);
     
     if( (Left==0 && Right==1) == 1) LEFT();
     else if((Right == 0 && Left == 1) == 1) RIGHT();
   }
}

void LEFT (void)
{
  setDir(RHT_FWD);
  int Left, Right;
  
  while(Left == 0)
  {
   Left = digitalRead(left);
   Right = digitalRead(right);
   if(Right == 0)
   {
     int lprev = Left;
     int rprev = Right;
     setDir(0);
     while(((lprev==Left)&&(rprev==Right))==1)
     {
        Left = digitalRead(left);
        Right = digitalRead(right);
     }
   }
   setDir(RHT_FWD); 
  }
  setDir(FWD);
}

void RIGHT (void)
{
  int Right, Left;
  setDir(LFT_FWD);
  while(Right==0)
  {
   Left=digitalRead(left);
   Right=digitalRead(right);
   if(Left==0)
   {
     int lprev=Left;
     int rprev=Right;
    setDir(0);
     while(((lprev==Left)&&(rprev==Right))==1)
     {
        Left=digitalRead(left);
        Right=digitalRead(right);
     }
   }
   setDir(LFT_FWD);
   }
  setDir(FWD);
}

void bt_main(){
    int state;
    
    if(bluetooth.available()) {
      state = bluetooth.read();
//      Serial.println(state);
    }
    
    if (state < 58){
      state -= 48;
      Serial.print("state before mapped is: " + String(state) + "\n");
      state = map(state, 0, 9, 0, 255);
      Serial.print("writing to enable with state: " + String(state) + "\n");
      analogWrite(enable, state);
    }
    switch(state){
        case 70:
            setDir(FWD);
            break;

        case 66:
            setDir(BKD);
            break;

        case 82:
            setDir(RHT);
            break;

        case 76:
            setDir(LFT);
            break;
        case 83:
            setDir(0);
            break;
    }
}

void wall_main(){
    unsigned long long distance;
    setDir(FWD);
    distance = getDistance();
   while (distance != 15){
       while (distance > 15) {
           setDir(RHT_FWD);
           
           distance = getDistance();
       }
       while (distance < 15) {
           setDir(LFT_FWD);
           distance = getDistance();
       }
    }     
}

long getDistance(){
    unsigned long duration, distance;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;
    return distance;
}


void coolPrint(){
  String c1output;
  String c2output;
  int rand1, rand2;
  for (int i = 0; i < 25; i++){
    c1output = "";
    c2output = "";
    for (int j = 0; j < 16; j++){
        rand1 = rand() % 26;
        rand2 = rand() % 26;
        Serial.println(rand2);
        c1output += alphabets[rand1];
        c2output += alphabets[rand2];
        Serial.println(c2output);
    }

    // Serial.println(c2output);
    lcd.setCursor(0, 0);
    lcd.print(c1output);
    lcd.setCursor(0, 1);
    lcd.print(c2output);

    printPartial13(5, 'X', i, 0);
    printPartial13(10, 'I', i, 1);
    printPartial13(15, 'I', i, 2);
    printPartial13(20, 'I', i, 3);
    // delay(5);
  }
  lcd.setCursor(0, 0);
  lcd.print(" XIII XIII XIII ");
  
  lcd.setCursor(0, 1);
  lcd.print(" XIII XIII XIII ");
}    


void printPartial13(int check, char str, int inc, int count){
  if (inc >= check){
    for (int k = 0; k < 2; k++){
        specialPrint(1 + count, k, str);
        specialPrint(6 + count, k, str);
        specialPrint(11 + count, k, str);      
    }
  }
}

void specialPrint(int col, int row, char str){
  lcd.setCursor(col, row);
  lcd.print(str);
}