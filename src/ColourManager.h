#ifndef __Molphene__ColourManager__
#define __Molphene__ColourManager__

#include <unordered_map>
#include <string>
#include "colour.h"

namespace molphene {
    class ColourManager {
    public:
        ColourManager();
        
        const colour & getElementColor(std::string elementSymbol);
        const colour & getAltlocColor(char altloc);
        
    private:
        std::unordered_map<std::string, colour> elementColors;
        std::unordered_map<char, colour> altlocColors;
    };
}

#endif /* defined(__Molphene__ColourManager__) */
