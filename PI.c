/**
  Section: Included Files
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "PI.h"

/**
  Section: PI Module APIs
 */

static uint8_t sensorHeight = 0;
static uint8_t setpoint = 112; 
static int error = 0;
static float integral = 0;
static float ki = 0.04;
static float kp = 4.2;
static int dutycycle;

uint8_t PI_GetSensorHeight(void) {
    return sensorHeight;
}

void PI_SetSetpoint(uint8_t value) {
    setpoint = value;
}
uint8_t PI_GetSetPoint(void) {
    return setpoint;
}


int PI_GetDutycycle(void) {
    return dutycycle;
}

void PI_SetKp(float value) {
    kp = value;
}
float PI_GetKp(void) {
    return kp;
}

void PI_SetKi(float value) {
    ki = value;
}
float PI_GetKi(void) {
    return ki;
}

void PI(void) {
    sensorHeight = (uint8_t) (ADC_GetConversion(Hoogtesensor) >> 2); //resultaat van ADC (8 bit )
    
    error = (int) setpoint - (int) sensorHeight;
    float propA = kp * error;
    integral += error;
    if (integral > 255) {
        integral = 255;
    }
    int I = ki * integral;
    dutycycle = (int)(I + propA); 

    if (dutycycle > 0x03FF) {
        dutycycle = 0x03FF;
    }
    if (dutycycle < 0) {
        dutycycle = 0;
    }
    //discrete integraal schrijven
    
            

    PWM5_LoadDutyValue( (uint16_t) dutycycle); // output pwm signaal voor hoogte 10 bit (van 0 tot 0x3FF)
}

/**
 End of File
 */