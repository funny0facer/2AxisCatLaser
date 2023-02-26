#pragma once
#ifndef _DECODE_HH_
#define _DECODE_HH_
#include <string>


class floatResult{
    public:
    bool success = false;
    float value = 0.0;
    bool evaluate (const char* message, const char* valuename);

    private:
    static bool myRegex(const char* prefix, const std::string message, float &result);
    
};

class intResult{
    public:
    bool success = false;
    int value = 0;
    bool evaluate (const char* message, const char* valuename);

    private:
    static bool myRegex(const char* prefix, const std::string message, int &result);
};

class boolResult{

    public:
    bool success = false;
    bool value = false;
    bool evaluate(const char* message, const char* valuename);

    private:
    static bool myRegex(const char* prefix, const std::string message, bool &result);
};


#endif