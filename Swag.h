#ifndef SWAG_H
#define SWAG_H

class Swag {
public:
	Swag(UINT32 redSwagIn, UINT32 blueSwagIn) : red(redSwagIn), blue(blueSwagIn) {}
	void Red(bool on) { red.Set(on); }
	void Blue(bool on) { blue.Set(on); }
private:
	Solenoid red, blue;
};

#endif
