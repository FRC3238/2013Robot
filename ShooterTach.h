#ifndef SHOOTERTACH_H
#define SHOOTERTACH_H

#include <WPILib.h>

class ShooterTach : public Counter, public PIDSource {
	
public:
	ShooterTach(){}
	explicit ShooterTach(UINT32 channel) : Counter(channel){}
	ShooterTach(UINT8 moduleNumber, UINT32 channel) : Counter(moduleNumber, channel){}
	explicit ShooterTach(DigitalSource *source) : Counter(source){}
	explicit ShooterTach(DigitalSource &source) : Counter(source){}
	explicit ShooterTach(AnalogTrigger *trigger) : Counter(trigger){}
	explicit ShooterTach(AnalogTrigger &trigger) : Counter(trigger){}
	ShooterTach(EncodingType encodingType, DigitalSource *upSource, DigitalSource *downSource, bool inverted);
	double GetRPM() { return 60.0/GetPeriod(); }
	double PIDGet() { return GetRPM(); }
};

#endif
