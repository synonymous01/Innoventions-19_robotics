// HEADER START (Ignore this code)

void setDir(int direction);
void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd);



// sensor (jumper) pins
#define BT 11
#define WALL 12

// sensor pins
#define trig1 6 // first ultrasonic trig pin
#define echo1 5 // first ultrasonic echo pin
#define trig2 2 // second ultrasonic trig pin
#define echo2 3 // second ultrasonic echo pin
#define rx 8  // rx pin (to tx) for bluetooth
#define tx 7  // tx pin (to rx) for bluetooth
#define left 2 // left ir sensor digital pin
#define right 3 // right ir sensor digital pin

//potentiometer pin
#define pot A6

// definitions for setDir()
#define FWD 70
#define BKD 66
#define RHT_FWD 2
#define LFT_FWD 3
#define RHT 82
#define LFT 76

//L293D pins
#define rt_fwd A2 // right motors run forwards
#define lt_fwd A4 // left motors run forwards
#define lt_bkd A1 // left motors run backwards
#define rt_bkd A5 // right motors run backwards
#define enable A3 // enable pin to activate motors

// HEADER END

void setup()
{
}


void loop()
{
}


void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd)
{
  digitalWrite(rt_fwd, state_rt_fwd);
  digitalWrite(lt_fwd, state_lt_fwd);
  digitalWrite(rt_bkd, state_rt_bkd);
  digitalWrite(lt_bkd, state_lt_bkd);
}

// setDir(FWD); makes the car go forwards
// setDir(BKD); makes the car go backwards
// setDir(RHT); makes the car point-turn clockwise
// setDir(LFT); makes the car point-turn anti-clockwise
void setDir(int direction)
{
  switch(direction)
  {
    case FWD:
      writeMotors(HIGH, HIGH, LOW, LOW);
    break;

    case BKD:
      writeMotors(LOW, LOW, HIGH, HIGH);
    break;

    case RHT:
      writeMotors(LOW, HIGH, HIGH, LOW);
    break;

    case LFT:
      writeMotors(HIGH, LOW, LOW, HIGH);
    break;
  }
}
