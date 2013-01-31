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
            long dval = atol(value.c_str());
            longmap[key] = dval;
        }
        else if (type == "d" || type == "f") {
            double lval = atof(value.c_str());
            doublemap[key] = lval;
        }
    }
}
    
long SettingsGetter::getLong(std::string key, long defaultVal) {
    rehash();
    std::map<std::string, long>::iterator it = longmap.find(key);
    if (it == longmap.end()) return defaultVal;
    return it->second;
}
double SettingsGetter::getDouble(std::string key, double defaultVal) {
    rehash();
    std::map<std::string, double>::iterator it = doublemap.find(key);
    if (it == doublemap.end()) return defaultVal;
    return it->second;
}

SettingsGetter Settings("/settings.txt");
