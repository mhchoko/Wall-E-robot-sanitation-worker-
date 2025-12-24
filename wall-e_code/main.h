#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ch.h>
#include <hal.h>
#include <memory_protection.h>
#include <usbcfg.h>
#include <motors.h>
#include <camera/po8030.h>
#include <chprintf.h>
#include <sensors/VL53L0X/VL53L0X.h>
#include "hd_cam.h"
#include "hd_tof.h"


// deplacement constants
#define SPIN_SPEED  250 // set motor speed for spin
#define LINEAR_SPEED  500// set linear speed, FWRD and BCKWRD
#define ZERO 0 // remove magic number 0
#define STEPS_FORWARD 200 // advance after red dot encounter to center robot
#define RAYON_CERCLE 500 // rayon max pour detection des objets
#define SLEEP_TIME 200 // sleep time tof
#define SLEEP_TIME_CAM 300 //sleep time camera
#define TOF_THREAD_SPACE 256 //allowed space for tof thread
#define TRESHHOLD_BLACK 65000 // treshhold detection for black
#define TRESHHOLD_RED 30000 // treshhold detection for red
#define COLOR_IMG_SIZE 340 // size of the image used
#define THREAD_SIZE_CAM 3000 //thread size allowance
#define MAIN_SLEEP 2000 //sleep time for the main

#ifdef __cplusplus
extern "C" {
#endif

#include <camera/dcmi_camera.h>
#include <msgbus/messagebus.h>
#include <parameter/parameter.h>


//constants for the differents parts of the project
#define IMAGE_BUFFER_SIZE		640

/** Robot wide IPC bus. */
extern messagebus_t bus;

extern parameter_namespace_t parameter_root;

void SendUint8ToComputer(uint8_t* data, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif
