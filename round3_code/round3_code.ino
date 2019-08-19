// HEADER START

void setDir(int direction);
void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd);
void bt_main();
void line_main();
void wall_main();
unsigned long long getDistance();


// sensor (jumper) pins
#define BT 11 // d2 d3 d4 for ir
#define WALL 12 // d5 d6 us 

// sensor pins
#define trig 5
#define echo 6
#define rx 8
#define tx 7
#define left 2
#define right 3

#define FWD 70
#define BKD 66
#define RHT_FWD 2
#define LFT_FWD 3
#define RHT 82
#define LFT 76

//L293D pins
#define rt_fwd A2
#define lt_fwd A4
#define lt_bkd A1
#define rt_bkd A5
#define enable A3


#include <SoftwareSerial.h>
// HEADER END
SoftwareSerial bluetooth(7, 8);


void setup() {
  pinMode(rt_fwd, OUTPUT);
  pinMode(lt_fwd, OUTPUT);
  pinMode(rt_bkd, OUTPUT);
  pinMode(lt_bkd, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(BT, INPUT);
  pinMode(enable, OUTPUT);
  pinMode(WALL, INPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
}


void loop() {
  digitalWrite(enable, HIGH);
  digitalRead(BT) == HIGH? bt_main() : digitalRead(WALL) == HIGH? wall_main() : line_main();
  }


void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd)
{
  // Serial.println("Function writeMotors running with parameters %i, %i, %i, %i.", state_rt_fwd, state_lt_fwd, state_rt_bkd, state_lt_bkd);
  digitalWrite(rt_fwd, state_rt_fwd);
  digitalWrite(lt_fwd, state_lt_fwd);
  digitalWrite(rt_bkd, state_rt_bkd);
  digitalWrite(lt_bkd, state_lt_bkd);
}

void setDir(int direction){
  switch(direction){
    case FWD:
      writeMotors(HIGH, HIGH, LOW, LOW);
    break;

    case BKD:
      writeMotors(LOW, LOW, HIGH, HIGH);
    break;

    case RHT_FWD:
      writeMotors(LOW, HIGH, LOW, LOW);
    break;

    case LFT_FWD:
      writeMotors(HIGH, LOW, LOW, LOW);
    break;

    case RHT:
      writeMotors(LOW, HIGH, HIGH, LOW);
    break;

    case LFT:
      writeMotors(HIGH, LOW, LOW, HIGH);
    break;

    default:
      writeMotors(LOW, LOW, LOW, LOW);
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

unsigned long long getDistance(){
    unsigned long long duration, distance;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;
    return distance;
}
