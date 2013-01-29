#ifndef SETTABLECOUNTER_H
#define SETTABLECOUNTER_H

#include <WPILib.h>

/* A class that duplicates WPILib's Counter class but can be set to a certain
 *  value rather than having to be reset completely.
 * Useful in the Climber class
 */
class SettableCounter : Counter {
public:
    INT32 Get() {
        return Counter::Get() - offset;
    }
    void Set(INT32 curVal) {
        offset = Counter::Get() - curVal;
    }
    void SetAbsoluteOffset(INT32 offsetIn) { offset = offsetIn; }
    void IncreaseOffset(INT32 amt) { offset += amt; }
private:
    INT32 offset;
};

#endif//SETTABLECOUNTER_H
