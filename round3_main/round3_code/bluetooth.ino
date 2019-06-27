void bt_main(){
    
    int state  = bluetooth.read()

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
