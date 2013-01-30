#ifndef SETTABLECOUNTER_H
#define SETTABLECOUNTER_H

#include <WPILib.h>

/* A class that duplicates WPILib's Counter class but can be set to a certain
 *  value rather than having to be reset completely.
 * Useful in the Climber class
 */
class SettableCounter : public Counter {
public:

	SettableCounter() : offset(0), Counter() {}
	explicit SettableCounter(UINT32 channel) : offset(0), Counter(channel) {}
	SettableCounter(UINT8 moduleNumber, UINT32 channel) : offset(0), Counter(moduleNumber, channel) {}
	explicit SettableCounter(DigitalSource *source) : offset(0), Counter(source) {}
	explicit SettableCounter(DigitalSource &source) : offset(0), Counter(source) {}
	explicit SettableCounter(AnalogTrigger *trigger) : offset(0), Counter(trigger) {}
	explicit SettableCounter(AnalogTrigger &trigger) : offset(0), Counter(trigger) {}
	SettableCounter(EncodingType encodingType, DigitalSource *upSource, DigitalSource *downSource, bool inverted) : offset(0), Counter(encodingType, upSource, downSource, inverted) {}
	virtual ~SettableCounter() {}

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
