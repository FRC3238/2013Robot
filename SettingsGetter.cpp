#include "Settings.h"
#include <WPILib.h>

SettingsGetter::SettingsGetter(std::string settingsfilenamein) :
    settingsfilename(settingsfilenamein)//, settingsfile(settingsfilename.c_str())
    {

}

void SettingsGetter::rehash() {
   // printf("Rehash() called. \n");
    ifstream settingsfile(settingsfilename.c_str());
    settingsfile.sync();
    settingsfile.seekg(0, ios::beg);
    settingsfile.clear();
    while (settingsfile) {
        std::string key, type, value;
        settingsfile >> key >> type >> value;
        // TODO: find errors in string to type conversion better
        if (type == "l" ||  type == "i") {
            long lval = atol(value.c_str());
            //printf("Found setting: key: `%s' type: long value: `%ld' from longmap; `%ld'\n", key.c_str(), lval, longmap[key]);
            longmap[key] = lval;
        }
        else if (type == "d" || type == "f") {
            double dval = atof(value.c_str());
            doublemap[key] = dval;
            //printf("Found setting: key: `%s' type: double value: `%f' from doublemap: `%f'\n", key.c_str(), dval, doublemap[key]);
        }
    }
}
    
long SettingsGetter::getLong(std::string key, long defaultVal, bool printToDashboard) {
    //rehash();
    long ret = defaultVal;
    //std::map<std::string, long>::iterator it = longmap.find(key);
    //if (it != longmap.end()) ret = it->second;
    ret = longmap[key];
    if (printToDashboard) SmartDashboard::PutNumber(key, ret);
    return ret;
}
double SettingsGetter::getDouble(std::string key, double defaultVal, bool printToDashboard) {
    //rehash();
    double ret = defaultVal;
    //std::map<std::string, double>::iterator it = doublemap.find(key);
    //if (it != doublemap.end()) ret = it->second;
    //else {
    //	printf("Nothing found for key `%s'", key.c_str());
    //}
    ret = doublemap[key];
    if (printToDashboard) SmartDashboard::PutNumber(key, ret);
    return ret;
}

SettingsGetter Settings("/settings.txt");
