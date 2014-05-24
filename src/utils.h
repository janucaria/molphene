#ifndef __Molphene__utils__
#define __Molphene__utils__

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <string>

namespace molphene {
    
    std::string trim_left_copy(const std::string & s);
    
    std::string & trim_left(std::string & s);
    
    std::string trim_right_copy(const std::string & s);
    
    std::string & trim_right(std::string & s);
    
    std::string trim_copy(const std::string & s);
    
    std::string & trim(std::string & s);
    
}



#endif /* defined(__Molphene__utils__) */
