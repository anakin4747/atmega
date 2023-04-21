#include "../include/mppt.h"
#include "../include/pwm.h"
#include "../include/uart.h"


static uint8_t duty = 0;
// Duty cycle


void mppt(uint32_t inputVoltageX100, 
          uint32_t inputCurrentX100, 
          uint32_t battVoltageX100){
    // Inputs are x100 to account for lack of floats


    uint32_t inputPowerX10K;

    inputPowerX10K = inputVoltageX100 * inputCurrentX100;
    // Each input is multiplied by a FLOATFACTOR 
    // So inputPowerX10K is multiplied by FLOATFACTOR^2
    
    uint32_t lastPowerX10K, lastVoltageX100, lastCurrentX100;
    lastPowerX10K = lastVoltageX100 = lastCurrentX100 = 0;

    if(battVoltageX100 > CHARGED_BATT_VOLTAGE_X100){
        updatePWM(0);
        sendOverUART("Battery Charged", 0, 5);
        return; 
        // Tested and should be working
    }
   

    if(inputPowerX10K >= lastPowerX10K){
        if(inputVoltageX100 >= lastVoltageX100){
            if(inputCurrentX100 >= lastCurrentX100){

                duty += duty * DELTA;
                // duty += duty * DELTA;
                sendOverUART("Duty Increased 1 Duty:", duty, 5);
                // d=d+delta*d
            } else {
                duty -= duty * DELTA;
                sendOverUART("Duty Decreased 2 Duty:", duty, 5);
                // d=d-delta*d
            }
        } else {
            if(inputCurrentX100 >= lastCurrentX100){
                duty += duty * DELTA;
                sendOverUART("Duty Increased 3 Duty:", duty, 5);
                // d=d+delta*d
            } else {
                duty -= duty * DELTA;
                sendOverUART("Duty Decreased 4 Duty:", duty, 5);
                // d=d-delta*d
            }
        }
    } else if(inputPowerX10K < lastPowerX10K){
        if(inputVoltageX100 >= lastVoltageX100){
            if(inputCurrentX100 >= lastCurrentX100){
                duty -= 2 * duty * DELTA;
                sendOverUART("Duty Doubly Decreased 4 Duty:", duty, 5);
                // d=d-2*delta*d
            } else {
                duty += 2 * duty * DELTA;
                sendOverUART("Duty Doubly Increased 5 Duty:", duty, 5);
                // d=d+2*delta*d
            }
        } else {
            duty -= 2 * duty * DELTA;
            sendOverUART("Duty Doubly Decreased 6 Duty:", duty, 5);
            // d=d-2*delta*d
        }
    }

    updatePWM(duty);


    lastPowerX10K = inputPowerX10K;
    lastVoltageX100 = inputVoltageX100;
    lastCurrentX100 = inputCurrentX100;
    // Save last values
}

