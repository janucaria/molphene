#ifndef __Molphene__Atom__
#define __Molphene__Atom__

#include <string>
#include <unordered_map>
#include "vec3f.h"

namespace molphene {
    class Compound;
    
    class Atom {
    public:
        struct element {
            const std::string name;
            const std::string symbol;
            const unsigned char number;
            const float radiiVdW;
            const float radiiCovalent;
            
            element(std::string name, std::string symbol, unsigned char number, float VdWRadii, float covalentRadii);
        };
        
        Atom(Compound & compound, const std::string & elementSymbol, std::string name, unsigned int serial);
        
        void setPosition(float x, float y, float z);
        
        unsigned int getSerial() const;
        
        const element & getElement() const;
        
        const vec3f & getPosition() const;
        
        void setAltLoc(char value);
        
        char getAltLoc() const;
        
        std::string getName();
        
    private:
        static const std::unordered_map<std::string, element> elements;
        
        unsigned int serial;
        
        char altLoc_;
        
        std::string name_;
        
        vec3f position_;
        
        element element_;
        
        Compound * compoundPtr_;
    };
    
        
}



#endif /* defined(__Molphene__Atom__) */
