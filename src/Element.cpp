#include "Element.h"

namespace molphene {
    Element::Element(std::string name, std::string symbol, unsigned char number, float VdWRadii, float covalentRadii) :
    name(name),
    symbol(symbol),
    number(number),
    radiiVdW(VdWRadii),
    radiiCovalent(covalentRadii)
    {
    }
}