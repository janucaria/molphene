#include "ColourManager.h"

namespace molphene {
    ColourManager::ColourManager() :
    elementColors({
        {"C", colour(0xFF0000)},
        {"N", colour(0x00FF00)},
        {"O", colour(0x0000FF)}
    })
    {
        
    }
    
    const colour & ColourManager::getElementColor(std::string elementSymbol) {
        return elementColors.at(elementSymbol);
    }
}
