#ifndef __Molphene__Element__
#define __Molphene__Element__

#include <string>

namespace molphene {
    struct Element {
        const std::string name;
        const std::string symbol;
        const unsigned char number;
        const float radiiVdW;
        const float radiiCovalent;
        
        Element(std::string name, std::string symbol, unsigned char number, float VdWRadii, float covalentRadii);
    };
}

#endif /* defined(__Molphene__Element__) */
