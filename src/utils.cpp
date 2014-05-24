#include "utils.h"

namespace molphene {
    
    std::string trim_left_copy(const std::string & s) {
        std::string s2 = s;
        return trim_left(s2);
    }
    
    std::string & trim_left(std::string & s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }
    
    std::string trim_right_copy(const std::string & s) {
        std::string s2 = s;
        return trim_right(s2);
    }
    
    std::string & trim_right(std::string & s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }
    
    std::string trim_copy(const std::string & s) {
        std::string s2 = s;
        return trim(s2);
    }
    
    std::string & trim(std::string & s) {
        return trim_left(trim_right(s));
    }
}