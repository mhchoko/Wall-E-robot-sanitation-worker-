#include "hd_tof.h"

bool detection_object(void){
    u_int16_t distance = ZERO; 
        distance = VL53L0X_get_dist_mm();       
        if(distance <= RAYON_CERCLE){
            return true;
        }
        else{
            return false;
        }
    
}
static THD_WORKING_AREA(waSee_Object, TOF_THREAD_SPACE); 
static THD_FUNCTION(See_Object, arg) {

    chRegSetThreadName(__FUNCTION__);
    (void)arg;
    // logique pour avancer ou spin
    while(1){
        //chprintf((BaseSequentialStream *) &SD3, "get_backward_state(): %d\r\n",  get_backward_state()); //debug
        if(detection_object() == false && get_backward_state() == false){ 
            spin(); 
        }
        if(detection_object() == true && get_backward_state() == false){
            forward();         
        }
         chThdSleepMilliseconds(SLEEP_TIME);
    }
}

//permet l'appel du thread depuis le main
void init_see_object(void){ 
chThdCreateStatic(waSee_Object, sizeof(waSee_Object), NORMALPRIO, See_Object, NULL);
}
