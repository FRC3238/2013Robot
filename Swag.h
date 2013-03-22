#ifndef SWAG_H
#define SWAG_H

#include <WPILib.h>

class Swag {
public:
	Swag(UINT8 moduleNum, UINT32 arduinoI2CNum) {
        DigitalModule* m = DigitalModule::GetInstance(moduleNum);
        arduinoSwag = m->GetI2C(arduinoI2CNum);
    }
    void ResetSwag(bool reset = true) {
        if (reset) {
            UINT8 d [1] = { 1, };
            arduinoSwag->Transaction(d, 1, NULL, 0);
        }
    }
    void HaveFrisbee(bool have = true) {
        UINT8 d [1] = { have? 2 : 3, };
        arduinoSwag->Transaction(d, 1, NULL, 0);
    }
    void DropFrisbee(bool drop = true) {
        if (drop) {
            UINT8 d [1] = { 4, };
            arduinoSwag->Transaction(d, 1, NULL, 0);
        }
    }
    void FireFrisbee(bool fire = true) {
        if (fire) {
            UINT8 d [1] = { 5, };
            arduinoSwag->Transaction(d, 1, NULL, 0);
        }
    }
    void StartClimb(bool climbing = true) {
        if (climbing) {
            UINT8 d [1] = { 6, };
            arduinoSwag->Transaction(d, 1, NULL, 0);
        }
    }
    void DoneClimb(bool done = true) {
        if (done) {
            UINT8 d [1] = { 7, };
            arduinoSwag->Transaction(d, 1, NULL, 0);
        }
    }

private:
    I2C* arduinoSwag;
};

#endif
