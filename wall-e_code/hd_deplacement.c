#include "hd_deplacement.h"
// all SPEED_SMTH defined in main.h

// basic move fct
void spin(void){                           
    left_motor_set_speed(-SPIN_SPEED);
	right_motor_set_speed(SPIN_SPEED);
}

void forward(void){
    left_motor_set_speed(LINEAR_SPEED);
	right_motor_set_speed(LINEAR_SPEED);
}

void backward(void){
    left_motor_set_speed(-LINEAR_SPEED);
	right_motor_set_speed(-LINEAR_SPEED);
}

void stop(void){
    left_motor_set_speed(ZERO); 
	right_motor_set_speed(ZERO);
}

void set_position_null(void){
    left_motor_set_pos(ZERO); 
	right_motor_set_pos(ZERO);
}

// center robot after red dot detection, red dot indicates center of circle
void forward_few_step(void){
    set_position_null();
    while(right_motor_get_pos() < STEPS_FORWARD){
        forward();
    }
    stop();
}