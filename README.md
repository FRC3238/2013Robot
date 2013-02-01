# 2013 Team 3238 Robot Code
This is the robot code for Team 3238's 2013 robot.

There is one class per subsystem:
* Chassis
* Climber
* Collector
* Shooter

There are also several other utility classes such as
* Toggle
* TwoButtonToggle
* SettableCounter
* Settings

## Settings

Using Settings is quite simple. First, you must include the header file:

    #include "Settings.h"

To get a value, do this:

    double myval = Settings.getDouble("myvalue");
    
or, to provide a default value:

    double myval = Settings.getDouble("myvalue", 32.38);
    
or, to get an int or long out:

    long mylongval = Settings.getLong("myint", 4);
    
If you wish to automatically send the value to the smart dashboard every time a value is read from the settings file, pass a third argment of `true` to the function.

Once you have the function call, you just add to the `settings.txt` file.
This file is located on the root directory of the cRIO and is a simple text file that contains all the necessary settings.
It's recommended to use filezilla to emulate editing the text file over the ftp connection.
The syntax of the `settings.txt` file is:

    <key/name> <f, d, i, or l depending on if it's a float, double, int or long> <value>
    
So for our previous example,

    myvalue d 3238.3238
    myint l 392
    
Note that `double` and `long` are the only supported types, but can be casted to `float` or `int` if necessary.

See the correctly-written Climber.cpp for an example of using Settings.
