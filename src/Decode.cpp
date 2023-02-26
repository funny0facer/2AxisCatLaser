#include <string>
#include "Decode.hh"
#include <regex>

        
    bool floatResult::evaluate(const char* mymessage, const char* valuename){
        success = floatResult::myRegex(valuename, std::string(mymessage), value);
        return success;
    }
    bool intResult::evaluate(const char* mymessage, const char* valuename){
        success = intResult::myRegex(valuename, std::string(mymessage), value);
        return success;
    }
    bool boolResult::evaluate(const char* mymessage, const char* valuename){
        success = boolResult::myRegex(valuename, std::string(mymessage), value);
        return success;
    }
    

    bool floatResult::myRegex(const char* prefix, const std::string message, float &result){
        std::string expression = std::string("(").append(std::string(prefix).append(")[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)"));
        std::regex myregex (expression);
        std::smatch stringMatch;
        bool foundSomething = std::regex_search(message,stringMatch,myregex);
        if (foundSomething){
            std::string matchedString = stringMatch[0].str();
            matchedString = matchedString.substr(matchedString.find('=')+1);
            result = std::stof(matchedString);
            return true;
        }

        return false;
    }
    bool intResult::myRegex(const char* prefix, const std::string message, int &result){
        std::string expression = std::string("(").append(std::string(prefix).append(")[0-9]+")); //different to float
        std::regex myregex (expression);
        std::smatch stringMatch;
        bool foundSomething = std::regex_search(message,stringMatch,myregex);
        if (foundSomething){
            std::string matchedString = stringMatch[0].str();
            matchedString = matchedString.substr(matchedString.find('=')+1);
            result = std::stoi(matchedString); //different to float
            return true;
        }

        return false;
    }

    bool boolResult::myRegex(const char* prefix, const std::string message, bool &result){
        std::string expression = std::string("(").append(std::string(prefix).append(")[01]")); //different to float
        std::regex myregex (expression);
        std::smatch stringMatch;
        bool foundSomething = std::regex_search(message,stringMatch,myregex);
        if (foundSomething){
            std::string matchedString = stringMatch[0].str();
            matchedString = matchedString.substr(matchedString.find('=')+1);
            result = (bool) std::stoi(matchedString); //different to float
            return true;
        }

        return false;
    }

    
