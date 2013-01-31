#include "Settings.h"

SettingsGetter::SettingsGetter(std::string settingsfilenamein) :
    settingsfilename(settingsfilenamein), settingsfile(settingsfilename.c_str())
    {

}

void SettingsGetter::rehash() {
    while (settingsfile) {
        std::string key, type, value;
        settingsfile >> key >> type >> value;
        // TODO: find errors in string to type conversion better
        if (type == "l" ||  type == "i") {
            double dval = value.toDouble();
            if ((longmap::const_iterator itr = longmap.find(key)))
                *itr = dval;
            else longmap.insert(key, dval);
        }
        else if (type == "d" || type == "f") {
            long lval = value.toLong();
            if ((doublemap::const_iterator itr = doublemap.find(key)))
                *itr = lval;
            else doublemap.insert(key, lval);
        }
    }
}
    
long SettingsGetter::getLong(std::string key, long defaultVal, bool attempttorehash) {
    return defaultVal;
}
double SettingsGetter::getDouble(std::string key, double defaultVal, bool attempttorehash) {
    return defaultVal;
}

SettingsGetter Settings("settings.txt");
