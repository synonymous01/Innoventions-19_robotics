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
#define recv 24

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