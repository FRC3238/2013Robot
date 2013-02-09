#ifndef TWOBUTTONTOGGLE_H
#define TWOBUTTONTOGGLE_H

class TwoButtonToggle {
public:
    TwoButtonToggle(bool outStartUp = false)
        : out(outStartUp) {}
    bool Set(bool on, bool off) {
        if (off) out = false;
        else if (on) out = true;
        return out;
    }
    bool Get() { return out; }
    void SetRawOut(bool rawOut) { out = rawOut; }
private:
    bool out;
};

#endif//TWOBUTTONTOGGLE_H
