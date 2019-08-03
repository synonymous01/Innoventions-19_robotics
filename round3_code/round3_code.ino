// HEADER START

void setDir(int direction);
void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd);
void bt_main();
void line_main();
void wall_main();


// sensor (jumper) pins
#define BT 20
#define WALL 22

// sensor pins
#define trig 12
#define echo 13
#define rx 0
#define tx 1
#define send 23
#define reci 24

#define FWD 0
#define BKD 1
#define RHT_FWD 2
#define LFT_FWD 3
#define RHT 4
#define LFT 5

//L293D pins
#define rt_fwd 15
#define lt_fwd 16
#define lt_bkd 18
#define rt_bkd 19


#include <NewPing.h>
#include <SoftwareSerial.h>
// HEADER END
SoftwareSerial bluetooth(rx, tx);
NewPing wallFollowingSensor(trig, echo);


void setup() {
  pinMode(rt_fwd, OUTPUT);
  pinMode(lt_fwd, OUTPUT);
  pinMode(rt_bkd, OUTPUT);
  pinMode(lt_bkd, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(send, OUTPUT);
  pinMode(reci, OUTPUT);
  pinMode(BT, INPUT);
  pinMode(WALL, INPUT);
//  turningTimer.setTimeOutTime(1000);
  //turningTimer.reset();
}


void loop() {
  digitalRead(BT) ? bt_main() : digitalRead(WALL) ? wall_main() : line_main();
  }


void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd)
{
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
    
}


void bt_main(){
    
    int state  = bluetooth.read();

    switch(state){
        case 13:
            setDir(FWD);
        break;

        case 14:
            setDir(BKD);
        break;

        case 15:
            setDir(RHT);
        break;

        case 16:
            setDir(LFT);
        break;
    }
}

void wall_main(){
    unsigned long distance;
    setDir(FWD);
    distance = wallFollowingSensor.ping_cm();
   while (distance != 15){
       while (distance > 15) {
           distance = wallFollowingSensor.ping_cm();
           setDir(RHT_FWD);
       }
       while (distance < 15) {
           distance = wallFollowingSensor.ping_cm();
           setDir(LFT_FWD);
       }
    }     
}
