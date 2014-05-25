#include "Atom.h"

namespace molphene {
    Atom::Atom(const std::string & elementSymbol, unsigned int serial) :
        element(ELEMENTS.at(elementSymbol)),
        serial(serial)
    {
        
    }
    
    void Atom::setPosition(float x, float y, float z) {
        position(x, y, z);
    }
    
    unsigned int Atom::getSerial() const {
        return serial;
    }
    
    const Element & Atom::getElement() const {
        return element;
    }
    
    const vec3f & Atom::getPosition() const {
        return position;
    }
    
    
    const std::unordered_map<std::string, Element> Atom::ELEMENTS({
        {"H", Element("Hydrogen", "H", 1, 1.2, 0.31)},
        {"HE", Element("Helium", "He", 2, 1.4, 0.28)},
        {"LI", Element("Lithium", "Li", 3, 1.82, 1.28)},
        {"BE", Element("Beryllium", "Be", 4, 0, 0.96)},
        {"B", Element("Boron", "B", 5, 0, 0.84)},
        {"C", Element("Carbon", "C", 6, 1.7, 0.76)},
        {"N", Element("Nitrogen", "N", 7, 1.55, 0.71)},
        {"O", Element("Oxygen", "O", 8, 1.52, 0.66)},
        {"F", Element("Fluorine", "F", 9, 1.47, 0.57)},
        {"NE", Element("Neon", "Ne", 10, 1.54, 0.58)},
        {"NA", Element("Sodium", "Na", 11, 2.27, 1.66)},
        {"MG", Element("Magnesium", "Mg", 12, 1.73, 1.41)},
        {"AL", Element("Aluminum", "Al", 13, 0, 1.21)},
        {"SI", Element("Silicon", "Si", 14, 2.1, 1.11)},
        {"P", Element("Phosphorus", "P", 15, 1.8, 1.07)},
        {"S", Element("Sulfur", "S", 16, 1.8, 1.05)},
        {"CL", Element("Chlorine", "Cl", 17, 1.75, 1.02)},
        {"R", Element("Argon", "Ar", 18, 1.88, 1.06)},
        {"K", Element("Potassium", "K", 19, 2.75, 2.03)},
        {"CA", Element("Calcium", "Ca", 20, 0, 1.76)},
        {"SC", Element("Scandium", "Sc", 21, 0, 1.7)},
        {"TI", Element("Titanium", "Ti", 22, 0, 1.6)},
        {"V", Element("Vanadium", "V", 23, 0, 1.53)},
        {"CR", Element("Chromium", "Cr", 24, 0, 1.39)},
        {"MN", Element("Manganese", "Mn", 25, 0, 1.39)},
        {"FE", Element("Iron", "Fe", 26, 0, 1.32)},
        {"CO", Element("Cobalt", "Co", 27, 0, 1.26)},
        {"NI", Element("Nickel", "Ni", 28, 1.63, 1.24)},
        {"CU", Element("Copper", "Cu", 29, 1.4, 1.32)},
        {"ZN", Element("Zinc", "Zn", 30, 1.39, 1.22)},
        {"GA", Element("Gallium", "Ga", 31, 1.87, 1.22)},
        {"GE", Element("Germanium", "Ge", 32, 0, 1.2)},
        {"AS", Element("Arsenic", "As", 33, 1.85, 1.19)},
        {"SE", Element("Selenium", "Se", 34, 1.9, 1.2)},
        {"BR", Element("Bromine", "Br", 35, 1.85, 1.2)},
        {"KR", Element("Krypton", "Kr", 36, 2.02, 1.16)},
        {"RB", Element("Rubidium", "Rb", 37, 0, 2.2)},
        {"SR", Element("Strontium", "Sr", 38, 0, 1.95)},
        {"Y", Element("Yttrium", "Y", 39, 0, 1.9)},
        {"ZR", Element("Zirconium", "Zr", 40, 0, 1.75)},
        {"NB", Element("Niobium", "Nb", 41, 0, 1.64)},
        {"MO", Element("Molybdenum", "Mo", 42, 0, 1.54)},
        {"TC", Element("Technetium", "Tc", 43, 0, 1.47)},
        {"RU", Element("Ruthenium", "Ru", 44, 0, 1.46)},
        {"RH", Element("Rhodium", "Rh", 45, 0, 1.42)},
        {"PD", Element("Palladium", "Pd", 46, 1.63, 1.39)},
        {"AG", Element("Silver", "Ag", 47, 1.72, 1.45)},
        {"CD", Element("Cadmium", "Cd", 48, 1.58, 1.44)},
        {"IN", Element("Indium", "In", 49, 1.93, 1.42)},
        {"SN", Element("Tin", "Sn", 50, 2.17, 1.39)},
        {"SB", Element("Antimony", "Sb", 51, 0, 1.39)},
        {"TE", Element("Tellurium", "Te", 52, 2.06, 1.38)},
        {"I", Element("Iodine", "I", 53, 1.98, 1.39)},
        {"XE", Element("Xenon", "Xe", 54, 2.16, 1.4)},
        {"CS", Element("Cesium", "Cs", 55, 0, 2.44)},
        {"BA", Element("Barium", "Ba", 56, 0, 2.15)},
        {"LA", Element("Lanthanum", "La", 57, 0, 2.07)},
        {"CE", Element("Cerium", "Ce", 58, 0, 2.04)},
        {"PR", Element("Praseodymium", "Pr", 59, 0, 2.03)},
        {"ND", Element("Neodymium", "Nd", 60, 0, 2.01)},
        {"PM", Element("Promethium", "Pm", 61, 0, 1.99)},
        {"SM", Element("Samarium", "Sm", 62, 0, 1.98)},
        {"EU", Element("Europium", "Eu", 63, 0, 1.98)},
        {"GD", Element("Gadolinium", "Gd", 64, 0, 1.96)},
        {"TB", Element("Terbium", "Tb", 65, 0, 1.94)},
        {"DY", Element("Dysprosium", "Dy", 66, 0, 1.92)},
        {"HO", Element("Holmium", "Ho", 67, 0, 1.92)},
        {"ER", Element("Erbium", "Er", 68, 0, 1.89)},
        {"TM", Element("Thulium", "Tm", 69, 0, 1.9)},
        {"YB", Element("Ytterbium", "Yb", 70, 0, 1.87)},
        {"LU", Element("Lutetium", "Lu", 71, 0, 1.87)},
        {"HF", Element("Hafnium", "Hf", 72, 0, 1.75)},
        {"TA", Element("Tantalum", "Ta", 73, 0, 1.7)},
        {"W", Element("Tungsten", "W", 74, 0, 1.62)},
        {"RE", Element("Rhenium", "Re", 75, 0, 1.51)},
        {"OS", Element("Osmium", "Os", 76, 0, 1.44)},
        {"IR", Element("Iridium", "Ir", 77, 0, 1.41)},
        {"PT", Element("Platinum", "Pt", 78, 1.75, 1.36)},
        {"AU", Element("Gold", "Au", 79, 1.66, 1.36)},
        {"HG", Element("Mercury", "Hg", 80, 1.55, 1.32)},
        {"TL", Element("Thallium", "Tl", 81, 1.96, 1.45)},
        {"PB", Element("Lead", "Pb", 82, 2.02, 1.46)},
        {"BI", Element("Bismuth", "Bi", 83, 0, 1.48)},
        {"PO", Element("Polonium", "Po", 84, 0, 1.4)},
        {"AT", Element("Astatine", "At", 85, 0, 1.5)},
        {"RN", Element("Radon", "Rn", 86, 0, 1.5)},
        {"FR", Element("Francium", "Fr", 87, 0, 2.6)},
        {"RA", Element("Radium", "Ra", 88, 0, 2.21)},
        {"AC", Element("Actinium", "Ac", 89, 0, 2.15)},
        {"TH", Element("Thorium", "Th", 90, 0, 2.06)},
        {"PA", Element("Protactinium", "Pa", 91, 0, 2)},
        {"U", Element("Uranium", "U", 92, 1.86, 1.96)},
        {"NP", Element("Neptunium", "Np", 93, 0, 1.9)},
        {"PU", Element("Plutonium", "Pu", 94, 0, 1.87)},
        {"AM", Element("Americium", "Am", 95, 0, 1.8)},
        {"CM", Element("Curium", "Cm", 96, 0, 1.69)},
        {"BK", Element("Berkelium", "Bk", 97, 0, 0)},
        {"CF", Element("Californium", "Cf", 98, 0, 0)},
        {"ES", Element("Einsteinium", "Es", 99, 0, 0)},
        {"FM", Element("Fermium", "Fm", 100, 0, 0)},
        {"MD", Element("Mendelevium", "Md", 101, 0, 0)},
        {"NO", Element("Nobelium", "No", 102, 0, 0)},
        {"LR", Element("Lawrencium", "Lr", 103, 0, 0)},
        {"RF", Element("Rutherfordium", "Rf", 104, 0, 0)},
        {"DB", Element("Dubnium", "Db", 105, 0, 0)},
        {"SG", Element("Seaborgium", "Sg", 106, 0, 0)},
        {"BH", Element("Bohrium", "Bh", 107, 0, 0)},
        {"HS", Element("Hassium", "Hs", 108, 0, 0)},
        {"MT", Element("Meitnerium", "Mt", 109, 0, 0)},
        {"DS", Element("Darmstadtium", "Ds", 110, 0, 0)},
        {"RG", Element("Roentgenium", "Rg", 111, 0, 0)},
        {"CN", Element("Copernicium", "Cn", 112, 0, 0)},
        {"UUT", Element("Ununtrium", "Uut", 113, 0, 0)},
        {"UUQ", Element("Ununquadium", "Uuq", 114, 0, 0)},
        {"UUP", Element("Ununpentium", "Uup", 115, 0, 0)},
        {"UUH", Element("Ununhexium", "Uuh", 116, 0, 0)},
        {"UUS", Element("Ununseptium", "Uus", 117, 0, 0)},
        {"UUO", Element("Ununoctium", "Uuo", 118, 0, 0)}
    });

    
}