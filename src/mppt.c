#include "../include/mppt.h"
#include "../include/pwm.h"

/*
 * A new piecewise adaptive step MPPT algorithm for PV systems
 * Y. Xue, S. Sun, J. Fei and H. Wu, "A new piecewise adaptive step MPPT algorithm for PV systems,"
 * 2017 12th IEEE Conference on Industrial Electronics and Applications (ICIEA), Siem Reap, Cambodia, 
 * 2017, pp. 1652-1656, doi: 10.1109/ICIEA.2017.8283104.
 *
 * https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=8283104
 */

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


    // What about the case when inputPower == lastPower???
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
    // Save results
}
