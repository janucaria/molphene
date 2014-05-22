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
        
    private:
        std::unordered_map<std::string, colour> elementColors;
    };
}

#endif /* defined(__Molphene__ColourManager__) */
