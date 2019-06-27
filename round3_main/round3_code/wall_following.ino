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