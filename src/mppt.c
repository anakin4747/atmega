#include "../include/mppt.h"
#include "../include/uart.h"
#include "../include/adc.h"

void mpptAlgorithm(void){
    static int16_t oldPowerxFF, oldVoltxFF, oldCurrxFF;
    oldPowerxFF = oldVoltxFF = oldCurrxFF = 0;
        
    uint16_t voltagexFF = rawVoltReading * 5 * FLOATFACTOR / 1023;
    uint16_t currentxFF = rawCurrReading * 5 * FLOATFACTOR / 1023;

//    uint16_t batteryxFF = rawBatteryReading * 5 * FLOATFACTOR / 1023;
//    Come back to this once you start implementing the control system

    int16_t powerxFF = voltagexFF * currentxFF / FLOATFACTOR;
    // Both current and voltage are multipied by FF so to make
    // sure power is only 1FF bigger I also divide by FF

    if(powerxFF > oldPowerxFF){
        if(voltagexFF > oldVoltxFF){
            if(currentxFF > oldCurrxFF){
                // d=d+delta*d
            } else {
                // d=d-delta*d
            }
        } else {
            if(currentxFF > oldCurrxFF){
                // d=d+delta*d
            } else {
                // d=d-delta*d
            }
        }
    } else if(powerxFF < oldPowerxFF){
        if(voltagexFF > oldVoltxFF){
            if(currentxFF > oldCurrxFF){
                // d=d-2*delta*d
            } else {
                // d=d+2*delta*d
            }
        } else {
            // d=d-2*delta*d
        }
    }


    oldPowerxFF = powerxFF;
    oldVoltxFF = voltagexFF;
    oldCurrxFF = currentxFF;
    // x(k) = x(k-1)

}
