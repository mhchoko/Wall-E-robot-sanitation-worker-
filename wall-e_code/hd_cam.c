
//RGB LED used for interaction with plotImage Python code
//#include <leds.h>

#include "hd_cam.h"


static bool backward_state = false; // ici justifié car réutilisé avec un get, besoin dans plusieurs fct.

static BSEMAPHORE_DECL(image_ready_sem, TRUE); 
static THD_WORKING_AREA(waCaptureImage, TOF_THREAD_SPACE);
static THD_FUNCTION(CaptureImage, arg) {

    chRegSetThreadName(__FUNCTION__);
    (void)arg;
	po8030_advanced_config(FORMAT_RGB565, 0, USED_LINE, IMAGE_BUFFER_SIZE, 2, SUBSAMPLING_X1, SUBSAMPLING_X1);
    po8030_set_awb(0);
	dcmi_enable_double_buffering();
	dcmi_set_capture_mode(CAPTURE_ONE_SHOT);
	dcmi_prepare();

    while(1){
        //starts a capture
		dcmi_capture_start();
		//waits for the capture to be done
		wait_image_ready();
		//signals an image has been captured
		chBSemSignal(&image_ready_sem);
    }
}

static THD_WORKING_AREA(waProcessImage, THREAD_SIZE_CAM); 
static THD_FUNCTION(ProcessImage, arg) {

    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    //initialisation à 0
	uint8_t *img_buff_ptr;
	uint8_t image_red[IMAGE_BUFFER_SIZE] = {0};  
    uint8_t image_green[IMAGE_BUFFER_SIZE] = {0}; 
    uint8_t image_blue[IMAGE_BUFFER_SIZE] = {0};
   
    while(1){
    	//waits until an image has been captured
        chBSemWait(&image_ready_sem);
		//gets the pointer to the array filled with the last image in RGB565    
		img_buff_ptr = dcmi_get_last_image_ptr();
 
        //initialisation à 0
        uint32_t color = 0;
        uint32_t red_color = 0;
        uint32_t green_color = 0;
        uint32_t blue_color = 0;
        uint32_t diff_green_red = 0;

        // de tp4 solution                
        for(uint16_t i = 0 ; i < (2 * IMAGE_BUFFER_SIZE) ; i+=2){
			//extracts 5 MSbits of the MSbyte (First byte in big-endian format)
			//takes nothing from the second byte
			image_red[i/2] = (uint8_t)img_buff_ptr[i] & 0xF8;
        }
        for(uint16_t i = 0 ; i < (2 * IMAGE_BUFFER_SIZE) ; i+=2){
            //extracts 3 LSbits of the first byte and the 3 MSbits of second byte
			image_green[i/2] = (((uint8_t)img_buff_ptr[i] & 0x07) << 5 )
							   + (((uint8_t)img_buff_ptr[i+1] & 0xE0) >> 3);
        }
        for(uint16_t i = 0 ; i < (2 * IMAGE_BUFFER_SIZE) ; i+=2){
            //extracts 5 LSbits of the LSByte (Second byte in big-endian format)
            image_blue[i/2] = ((uint8_t)img_buff_ptr[i+1] & 0x1F) << 3;   
		}
        for(uint16_t i=0 ; i < COLOR_IMG_SIZE; i+=1){
            red_color += image_red[i];
        }
        for(uint16_t i=0 ; i < COLOR_IMG_SIZE; i+=1){
            green_color += image_green[i];
        }
        for(uint16_t i=0 ; i < COLOR_IMG_SIZE; i+=1){
            blue_color += image_blue[i];
        } 
    
        color = red_color + green_color + blue_color;
   
        if(backward_state == true || color < TRESHHOLD_BLACK){  
             //recule si arrive a la ligne noir 
            backward_state = true;
            backward(); 
        }
        // detect drop de green, contre le rouge!, centre le robot si detecte du rouge
        diff_green_red = red_color - green_color; 
        if(diff_green_red > TRESHHOLD_RED ){
            backward_state = false; 
            forward_few_step();  
        }   
        chThdSleepMilliseconds(SLEEP_TIME_CAM);
    }  
}

//getter fct
bool get_backward_state(void){
    return backward_state;
}

//to be callable from main
void hd_camera_start(void){
	chThdCreateStatic(waProcessImage, sizeof(waProcessImage), NORMALPRIO, ProcessImage, NULL);
	chThdCreateStatic(waCaptureImage, sizeof(waCaptureImage), NORMALPRIO, CaptureImage, NULL);
}
