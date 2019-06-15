const uint8_t rt_fwd = 15, lt_fwd = 16, lt_bkd = 18, rt_bkd = 19;
const uint8_t trig = 12, echo = 13, rx = 0, tx = 1, send = 23, recv = 24;

void setDir(int direction);
void writeMotors(int state_rt_fwd, int state_lt_fwd, int state_rt_bkd, int state_lt_bkd);
void bt_main();
void line_main();
void wall_main();

#define BT 20
#define LINE 21
#define WALL 22


#define FWD 0
#define BKD 1
#define RHT_FWD 2
#define LFT_FWD 3
#define RHT 4
#define LFT 5
