#ifndef SHOOTTACH_H
#define SHOOTTACH_H

#include <WPILib.h>

class ShootTach : public Counter, public PIDSource {
public:
	ShootTach(){}
	explicit ShootTach(UINT32 channel) : Counter(channel){}
	ShootTach(UINT8 moduleNumber, UINT32 channel) : Counter(moduleNumber, channel){}
	explicit ShootTach(DigitalSource *source) : Counter(source){}
	explicit ShootTach(DigitalSource &source) : Counter(source){}
	explicit ShootTach(AnalogTrigger *trigger) : Counter(trigger){}
	explicit ShootTach(AnalogTrigger &trigger) : Counter(trigger){}
	ShootTach(EncodingType encodingType, DigitalSource *upSource, DigitalSource *downSource, bool inverted);
	double GetRPM() { return 60.0/GetPeriod(); }
	double PIDGet() { return GetRPM(); }
};

#endif
