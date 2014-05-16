#ifndef __Molphene__Atom__
#define __Molphene__Atom__

#include <string>
#include <unordered_map>

#include "vec3f.h"
#include "Element.h"

namespace molphene {
    class Atom {
        
        static const std::unordered_map<std::string, Element> ELEMENTS;
        
        unsigned int serial;
        
        vec3f position;
        Element * element;
        
    public:
        
        Atom(unsigned int serial);
        
        void setPosition(float x, float y, float z);
        
        void setElement(std::string elementSymbol);
        
        unsigned int getSerial() const;
        
        const Element & getElement() const;
        
        const vec3f & getPosition() const;
        
    };
}



#endif /* defined(__Molphene__Atom__) */
