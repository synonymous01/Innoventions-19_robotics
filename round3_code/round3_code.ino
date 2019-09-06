// HEADER START

void setDir(int direction);
void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd);
void bt_main();
void line_main();
void wall_main();
float getDistance(int trig, int echo);
void coolPrint();
void LEFT();
void RIGHT();
void specialPrint(int col, int row, char str);
// sensor (jumper) pins
#define BT 11 // d2 d3 d4 for ir
#define WALL 12 // d5 d6 us 

// sensor pins
#define trig1 6
#define echo1 5
#define trig2 2
#define echo2 3
#define rx 8
#define tx 7
#define left 2
#define right 3

#define FWD 70
#define BKD 66
#define RHT_FWD 2
#define LFT_FWD 3
#define SOFT_RHT 4
#define SOFT_LFT 5
#define SOFT_RHT2 6
#define SOFT_LFT2 7
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
#include <math.h>

// HEADER END


SoftwareSerial bluetooth(7, 8);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// LiquidCrystal lcd(A5, A4, A3, A2, A1, 9);

String alphabets[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

void setup() {
  SoftPWMBegin();
  SoftPWMSet(rt_fwd, 0);
  SoftPWMSet(lt_fwd, 0);
  SoftPWMSet(rt_bkd, 0);
  SoftPWMSet(lt_bkd, 0);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  // pinMode(right, OUTPUT);
  // pinMode(left, OUTPUT);
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
  digitalWrite(enable, HIGH);
  // wall_main();
  saukha_wall_main();
//  digitalRead(BT) == HIGH ? bt_main() : digitalRead(WALL) == HIGH ? wall_main() : line_main();
    // long difference, dist1, dist2;
    // dist1 = getDistance(trig1, echo1);
    // dist2 = getDistance(trig2, echo2);
    // difference = dist1 - dist2;
    // Serial.println("Difference = " + String(dist1) + " - " + String(dist2) + " = " + String(difference));
}


// void testPWM()
// {
//   int state;
    
//   if(bluetooth.available()) {
//     state = bluetooth.read();
//   }
  
//   if (state < 58){
//   state -= 48;
//   Serial.print("state before mapped is: " + String(state) + "\n");
//   state = map(state, 0, 9, 0, 255);
//   Serial.print("writing to enable with state: " + String(state) + "\n");
//   analogWrite(enable, state);
//   }
// }


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
      writeMotors(100, 5, 0, 0);
    break;

    case LFT_FWD:
      writeMotors(10, 85, 0, 0);
    break;

    case SOFT_LFT:
      writeMotors(35, 85, 0, 0);
      break;
    
    case SOFT_RHT:
      writeMotors(100, 30, 0, 0);
      break;

    case SOFT_RHT2:
      writeMotors(100, 55, 0, 0);
      break;

    case SOFT_LFT2:
      writeMotors(60, 85, 0, 0);
      break;

    case LFT:
      writeMotors(0, 100, 100, 0);
    break;

    case RHT:
      writeMotors(100, 0, 0, 100);
    break;

    default:
      writeMotors(0, 0, 0, 0);
    break;
  }
}


void bt_main(){
    int state;
    
    if(bluetooth.available()) {
      state = bluetooth.read();
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
        case 88:
          coolPrint();
          break;
        case 120:
          lcd.clear();
        break;
    }
}

void wall_main(){
    int velocityL, velocityR, percentageVelocity;
    long difference;
    const int dist = 0.74, carLength = 255, maxVelocity = 2.22;
    float angle;
    difference = getDifference();
    angle = atan2(difference, carLength);
    Serial.println("Angle: " + String(angle) + " Difference: " + String(difference));
    if (angle < 0){
      velocityL = ((2 * dist) / cos(angle)) - maxVelocity;
      percentageVelocity = (velocityL / maxVelocity) * 100;
      writeMotors(100, percentageVelocity, 0, 0);
    } else if(angle > 0) {
      velocityR = ((2 * dist) / cos(angle)) - maxVelocity;
      percentageVelocity = (velocityR / maxVelocity) * 100;
      writeMotors(percentageVelocity, 100, 0, 0);
    } else if(angle == 0){
      writeMotors(100, 100, 0, 0);
    }
    
}


void saukha_wall_main(){
  float difference;
  difference = getDifference();
       Serial.println(difference);
  while (difference){
    while (difference > 0){
       difference < 2 ? setDir(SOFT_LFT2) : difference < 5 ? setDir(SOFT_LFT) : setDir(LFT_FWD); 
       difference = getDifference();
       Serial.println(difference);
    }
    
    while (difference < 0)
    {
      difference > -2 ? setDir(SOFT_RHT2) : difference > -5 ? setDir(SOFT_RHT) : setDir(RHT_FWD);
      difference = getDifference();
       Serial.println(difference);
    }
  }
}


float getDifference()
{
  float sonar1, sonar2;
  sonar1 = getDistance(trig1, echo1);
  sonar2 = getDistance(trig2, echo2);
  return sonar1 - sonar2;
}

float getDistance(int trig, int echo){
    unsigned long duration;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    return duration * 0.034 / 2;
}


void coolPrint(){
  String c1output;
  String c2output;
  String event = "PROJECTX";
  int rand1, rand2;
  lcd.setCursor(0, 0);
  lcd.print("      XIII      ");
  delay(1000);
  for (int i = 0; i < 25; i++){
    c1output = "";
    c2output = "";
    for (int j = 0; j < 16; j++){
        rand1 = rand() % 26;
        rand2 = rand() % 26;
        Serial.println(rand2);
        c1output += rand1;
        c2output += rand2;
    }

    Serial.println(c2output);
    lcd.setCursor(0, 0);
    lcd.print(c1output);
    lcd.setCursor(0, 1);
    lcd.print(c2output);

    if (i >= 10){
      for (int k = 0; k < 8; k += 2){
        lcd.setCursor(k + 4, 0);
        lcd.print(event.charAt(k));
      }
    }
    if (i >= 20){
      for (int k = 1; k < 8; k += 2){
        lcd.setCursor(k + 4, 0);
        lcd.print(event.charAt(k));
      }
    }
  }
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print(event);
  delay(1000);
}    


void specialPrint(int col, int row, char str){
  lcd.setCursor(col, row);
  lcd.print(str);
}

void line_main(){
  analogWrite(enable, 110);
}