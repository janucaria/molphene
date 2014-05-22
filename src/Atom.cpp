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
        {"He", Element("Helium", "He", 2, 1.4, 0.28)},
        {"Li", Element("Lithium", "Li", 3, 1.82, 1.28)},
        {"Be", Element("Beryllium", "Be", 4, 0, 0.96)},
        {"B", Element("Boron", "B", 5, 0, 0.84)},
        {"C", Element("Carbon", "C", 6, 1.7, 0.76)},
        {"N", Element("Nitrogen", "N", 7, 1.55, 0.71)},
        {"O", Element("Oxygen", "O", 8, 1.52, 0.66)},
        {"F", Element("Fluorine", "F", 9, 1.47, 0.57)},
        {"Ne", Element("Neon", "Ne", 10, 1.54, 0.58)},
        {"Na", Element("Sodium", "Na", 11, 2.27, 1.66)},
        {"Mg", Element("Magnesium", "Mg", 12, 1.73, 1.41)},
        {"Al", Element("Aluminum", "Al", 13, 0, 1.21)},
        {"Si", Element("Silicon", "Si", 14, 2.1, 1.11)},
        {"P", Element("Phosphorus", "P", 15, 1.8, 1.07)},
        {"S", Element("Sulfur", "S", 16, 1.8, 1.05)},
        {"Cl", Element("Chlorine", "Cl", 17, 1.75, 1.02)},
        {"Ar", Element("Argon", "Ar", 18, 1.88, 1.06)},
        {"K", Element("Potassium", "K", 19, 2.75, 2.03)},
        {"Ca", Element("Calcium", "Ca", 20, 0, 1.76)},
        {"Sc", Element("Scandium", "Sc", 21, 0, 1.7)},
        {"Ti", Element("Titanium", "Ti", 22, 0, 1.6)},
        {"V", Element("Vanadium", "V", 23, 0, 1.53)},
        {"Cr", Element("Chromium", "Cr", 24, 0, 1.39)},
        {"Mn", Element("Manganese", "Mn", 25, 0, 1.39)},
        {"Fe", Element("Iron", "Fe", 26, 0, 1.32)},
        {"Co", Element("Cobalt", "Co", 27, 0, 1.26)},
        {"Ni", Element("Nickel", "Ni", 28, 1.63, 1.24)},
        {"Cu", Element("Copper", "Cu", 29, 1.4, 1.32)},
        {"Zn", Element("Zinc", "Zn", 30, 1.39, 1.22)},
        {"Ga", Element("Gallium", "Ga", 31, 1.87, 1.22)},
        {"Ge", Element("Germanium", "Ge", 32, 0, 1.2)},
        {"As", Element("Arsenic", "As", 33, 1.85, 1.19)},
        {"Se", Element("Selenium", "Se", 34, 1.9, 1.2)},
        {"Br", Element("Bromine", "Br", 35, 1.85, 1.2)},
        {"Kr", Element("Krypton", "Kr", 36, 2.02, 1.16)},
        {"Rb", Element("Rubidium", "Rb", 37, 0, 2.2)},
        {"Sr", Element("Strontium", "Sr", 38, 0, 1.95)},
        {"Y", Element("Yttrium", "Y", 39, 0, 1.9)},
        {"Zr", Element("Zirconium", "Zr", 40, 0, 1.75)},
        {"Nb", Element("Niobium", "Nb", 41, 0, 1.64)},
        {"Mo", Element("Molybdenum", "Mo", 42, 0, 1.54)},
        {"Tc", Element("Technetium", "Tc", 43, 0, 1.47)},
        {"Ru", Element("Ruthenium", "Ru", 44, 0, 1.46)},
        {"Rh", Element("Rhodium", "Rh", 45, 0, 1.42)},
        {"Pd", Element("Palladium", "Pd", 46, 1.63, 1.39)},
        {"Ag", Element("Silver", "Ag", 47, 1.72, 1.45)},
        {"Cd", Element("Cadmium", "Cd", 48, 1.58, 1.44)},
        {"In", Element("Indium", "In", 49, 1.93, 1.42)},
        {"Sn", Element("Tin", "Sn", 50, 2.17, 1.39)},
        {"Sb", Element("Antimony", "Sb", 51, 0, 1.39)},
        {"Te", Element("Tellurium", "Te", 52, 2.06, 1.38)},
        {"I", Element("Iodine", "I", 53, 1.98, 1.39)},
        {"Xe", Element("Xenon", "Xe", 54, 2.16, 1.4)},
        {"Cs", Element("Cesium", "Cs", 55, 0, 2.44)},
        {"Ba", Element("Barium", "Ba", 56, 0, 2.15)},
        {"La", Element("Lanthanum", "La", 57, 0, 2.07)},
        {"Ce", Element("Cerium", "Ce", 58, 0, 2.04)},
        {"Pr", Element("Praseodymium", "Pr", 59, 0, 2.03)},
        {"Nd", Element("Neodymium", "Nd", 60, 0, 2.01)},
        {"Pm", Element("Promethium", "Pm", 61, 0, 1.99)},
        {"Sm", Element("Samarium", "Sm", 62, 0, 1.98)},
        {"Eu", Element("Europium", "Eu", 63, 0, 1.98)},
        {"Gd", Element("Gadolinium", "Gd", 64, 0, 1.96)},
        {"Tb", Element("Terbium", "Tb", 65, 0, 1.94)},
        {"Dy", Element("Dysprosium", "Dy", 66, 0, 1.92)},
        {"Ho", Element("Holmium", "Ho", 67, 0, 1.92)},
        {"Er", Element("Erbium", "Er", 68, 0, 1.89)},
        {"Tm", Element("Thulium", "Tm", 69, 0, 1.9)},
        {"Yb", Element("Ytterbium", "Yb", 70, 0, 1.87)},
        {"Lu", Element("Lutetium", "Lu", 71, 0, 1.87)},
        {"Hf", Element("Hafnium", "Hf", 72, 0, 1.75)},
        {"Ta", Element("Tantalum", "Ta", 73, 0, 1.7)},
        {"W", Element("Tungsten", "W", 74, 0, 1.62)},
        {"Re", Element("Rhenium", "Re", 75, 0, 1.51)},
        {"Os", Element("Osmium", "Os", 76, 0, 1.44)},
        {"Ir", Element("Iridium", "Ir", 77, 0, 1.41)},
        {"Pt", Element("Platinum", "Pt", 78, 1.75, 1.36)},
        {"Au", Element("Gold", "Au", 79, 1.66, 1.36)},
        {"Hg", Element("Mercury", "Hg", 80, 1.55, 1.32)},
        {"Tl", Element("Thallium", "Tl", 81, 1.96, 1.45)},
        {"Pb", Element("Lead", "Pb", 82, 2.02, 1.46)},
        {"Bi", Element("Bismuth", "Bi", 83, 0, 1.48)},
        {"Po", Element("Polonium", "Po", 84, 0, 1.4)},
        {"At", Element("Astatine", "At", 85, 0, 1.5)},
        {"Rn", Element("Radon", "Rn", 86, 0, 1.5)},
        {"Fr", Element("Francium", "Fr", 87, 0, 2.6)},
        {"Ra", Element("Radium", "Ra", 88, 0, 2.21)},
        {"Ac", Element("Actinium", "Ac", 89, 0, 2.15)},
        {"Th", Element("Thorium", "Th", 90, 0, 2.06)},
        {"Pa", Element("Protactinium", "Pa", 91, 0, 2)},
        {"U", Element("Uranium", "U", 92, 1.86, 1.96)},
        {"Np", Element("Neptunium", "Np", 93, 0, 1.9)},
        {"Pu", Element("Plutonium", "Pu", 94, 0, 1.87)},
        {"Am", Element("Americium", "Am", 95, 0, 1.8)},
        {"Cm", Element("Curium", "Cm", 96, 0, 1.69)},
        {"Bk", Element("Berkelium", "Bk", 97, 0, 0)},
        {"Cf", Element("Californium", "Cf", 98, 0, 0)},
        {"Es", Element("Einsteinium", "Es", 99, 0, 0)},
        {"Fm", Element("Fermium", "Fm", 100, 0, 0)},
        {"Md", Element("Mendelevium", "Md", 101, 0, 0)},
        {"No", Element("Nobelium", "No", 102, 0, 0)},
        {"Lr", Element("Lawrencium", "Lr", 103, 0, 0)},
        {"Rf", Element("Rutherfordium", "Rf", 104, 0, 0)},
        {"Db", Element("Dubnium", "Db", 105, 0, 0)},
        {"Sg", Element("Seaborgium", "Sg", 106, 0, 0)},
        {"Bh", Element("Bohrium", "Bh", 107, 0, 0)},
        {"Hs", Element("Hassium", "Hs", 108, 0, 0)},
        {"Mt", Element("Meitnerium", "Mt", 109, 0, 0)},
        {"Ds", Element("Darmstadtium", "Ds", 110, 0, 0)},
        {"Rg", Element("Roentgenium", "Rg", 111, 0, 0)},
        {"Cn", Element("Copernicium", "Cn", 112, 0, 0)},
        {"Uut", Element("Ununtrium", "Uut", 113, 0, 0)},
        {"Uuq", Element("Ununquadium", "Uuq", 114, 0, 0)},
        {"Uup", Element("Ununpentium", "Uup", 115, 0, 0)},
        {"Uuh", Element("Ununhexium", "Uuh", 116, 0, 0)},
        {"Uus", Element("Ununseptium", "Uus", 117, 0, 0)},
        {"Uuo", Element("Ununoctium", "Uuo", 118, 0, 0)}
    });

    
}