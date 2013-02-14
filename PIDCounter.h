#ifndef PIDCOUNTER_H
#define PIDCOUNTER_H

class PIDCounter : public Counter, public PIDSource {
	
public:
	PIDCounter(){}
	explicit PIDCounter(UINT32 channel) : Counter(channel){}
	PIDCounter(UINT8 moduleNumber, UINT32 channel) : Counter(moduleNumber, channel){}
	explicit PIDCounter(DigitalSource *source) : Counter(source){}
	explicit PIDCounter(DigitalSource &source) : Counter(source){}
	explicit PIDCounter(AnalogTrigger *trigger) : Counter(trigger){}
	explicit PIDCounter(AnalogTrigger &trigger) : Counter(trigger){}
	PIDCounter(EncodingType encodingType, DigitalSource *upSource, DigitalSource *downSource, bool inverted);
	double PIDGet() { return Get(); }
};

#endif
