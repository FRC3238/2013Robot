#ifndef TOGGLE_H
#define TOGGLE_H

class Toggle {
public:
    Toggle(bool outStartUp = false, bool inStartUp = false)
        : prevOut(outStartUp), prevIn(inStartUp) {}
    bool Set(bool in) {
        if (in != prevIn) {
            prevIn = in;
            if (in) prevOut = !prevOut;
        }
        return prevOut;
    }
    bool Get() { return prevOut; }
    void SetRawIn(bool rawIn) { prevIn = rawIn; }
    void SetRawOut(bool rawOut) { prevOut = rawOut; }
private:
    bool prevOut;
    bool prevIn;
};

#endif//TOGGLE_H
