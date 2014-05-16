#include "Atom.h"

namespace molphene {
    Atom::Atom(unsigned int serial) :
        serial(serial)
    {
        
    }
    
    void Atom::setPosition(float x, float y, float z) {
        position(x, y, z);
    }
    
    void Atom::setElement(std::string elementSymbol) {
        Element el = ELEMENTS.at(elementSymbol);
        element = &el;
    }
    
    unsigned int Atom::getSerial() const {
        return serial;
    }
    
    const Element & Atom::getElement() const {
        return *element;
    }
    
    const vec3f & Atom::getPosition() const {
        return position;
    }
    
    
    const std::unordered_map<std::string, Element> Atom::ELEMENTS({
        {"C", Element("Carbon", "C", 6, 1.7f, 0.76f)}
    });

    
}