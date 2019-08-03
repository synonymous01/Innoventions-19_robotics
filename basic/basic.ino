// HEADER START (Ignore this code)

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

void setup(){}


void loop(){}


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
  }
}