// definitions for setDir()
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


void setup() {
  pinMode(rt_fwd, OUTPUT);
  pinMode(lt_fwd, OUTPUT);
  pinMode(rt_bkd, OUTPUT);
  pinMode(rt_fwd, OUTPUT);
}

void loop() {
  digitalWrite(enable, HIGH);
  setDir(FWD);
  delay(5000);
  setDir(BKD);
  delay(5000);
  setDir(LFT);
  delay(5000);
  setDir(RHT);
  delay(5000);
  setDir(1);
  delay(10000);
}

void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd)
{
  digitalWrite(rt_fwd, state_rt_fwd);
  digitalWrite(lt_fwd, state_lt_fwd);
  digitalWrite(rt_bkd, state_rt_bkd);
  digitalWrite(lt_bkd, state_lt_bkd);
}

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
