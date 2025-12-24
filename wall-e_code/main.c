
#include "main.h"

void SendUint8ToComputer(uint8_t* data, uint16_t size) 
{
    chSequentialStreamWrite((BaseSequentialStream *)&SD3, (uint8_t*)"START", 5);
    chSequentialStreamWrite((BaseSequentialStream *)&SD3, (uint8_t*)&size, sizeof(uint16_t));
    chSequentialStreamWrite((BaseSequentialStream *)&SD3, (uint8_t*)data, size);
}

static void serial_start(void)
{
    static SerialConfig ser_cfg = {
        115200,
        0,
        0,
        0,
    };

    sdStart(&SD3, &ser_cfg); // UART3.
}

int main(void)
	{
    halInit();
    chSysInit();
    mpu_init(); 

    //starts the serial communication
    serial_start();
    //start the USB communication
    usb_start();
    //starts the camera
    dcmi_start();
    po8030_start();
    //inits the motors
    motors_init();
	//starts tof and process
	VL53L0X_start();          
	init_see_object();
	//init process of image   
    hd_camera_start();
	
    while (1) {
        chThdSleepMilliseconds(MAIN_SLEEP); 
    }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
