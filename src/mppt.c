#include "../include/mppt.h"
#include "../include/pwm.h"

void mppt(uint32_t inputVoltage, uint32_t inputCurrent, uint32_t battVoltage){

    if(battVoltage > CHARGED_BATT_VOLTAGE){
        updatePWM(0);
        // Lower PWM the voltage so the battery does not get charged anymore
        //
        // DOUBLE CHECK THAT THIS WILL WORK
        //
        // THIS IS UNTESTED
        //
    }
   
    uint32_t inputPower;

    inputPower = inputVoltage * inputCurrent;
    // Each input is multiplied by a FLOATFACTOR 
    // So inputPower is multiplied by FLOATFACTOR^2
    
    uint32_t lastPower, lastVoltage, lastCurrent;
    lastPower = lastVoltage = lastCurrent = 0;


    if(inputPower > lastPower){
        if(inputVoltage > lastVoltage){
            if(inputCurrent > lastCurrent){
                duty += DELTA * duty;
                // d=d+delta*d
            } else {
                duty -= DELTA * duty;
                // d=d-delta*d
            }
        } else {
            if(inputCurrent > lastCurrent){
                duty += DELTA * duty;
                // d=d+delta*d
            } else {
                duty -= DELTA * duty;
                // d=d-delta*d
            }
        }
    } else if(inputPower < lastPower){
        if(inputVoltage > lastVoltage){
            if(inputCurrent > lastCurrent){
                duty -= 2 * DELTA * duty;
                // d=d-2*delta*d
            } else {
                duty += 2 * DELTA * duty;
                // d=d+2*delta*d
            }
        } else {
            duty -= 2 * DELTA * duty;
            // d=d-2*delta*d
        }
    }


    lastPower = inputPower;
    lastVoltage = inputVoltage;
    lastCurrent = inputCurrent;
}
