#include <header_main.h>


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