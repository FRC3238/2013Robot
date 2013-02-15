#ifndef SETTINGSGETTER_H
#define SETTINGSGETTER_H

#include <string>
#include <fstream>
#include <map>

class SettingsGetter {
public:
    SettingsGetter(std::string settingsfilenamein);
    // Update the internal map to reread all the chances in the settings file
    void rehash();
    long getLong(std::string key, long defaultVal= 0, bool printToDashboard = false);
    double getDouble(std::string key, double defaultVal = 0.0, bool printToDashboard = false);
private:
    std::string settingsfilename;
    //std::ifstream settingsfile;
    std::map<std::string, long> longmap;
    std::map<std::string, double> doublemap;
};

extern SettingsGetter Settings;

#endif//SETTINGSGETTER_H
