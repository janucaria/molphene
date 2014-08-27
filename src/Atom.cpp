#include "Atom.h"
#include "Compound.h"
#include "Chain.h"
#include "Model.h"

namespace molphene {
    
    Atom::element::element(std::string name, std::string symbol, unsigned char number, float VdWRadii, float covalentRadii)
    : name(name)
    , symbol(symbol)
    , number(number)
    , radiiVdW(VdWRadii)
    , radiiCovalent(covalentRadii)
    {
    }
    
    Atom::Atom(Compound & compound, const std::string & elementSymbol, std::string name, unsigned int serial)
    : compoundPtr_(&compound)
    , element_(elements.at(elementSymbol))
    , name_(name)
    , serial(serial)
    {
    }
    
    void Atom::setPosition(float x, float y, float z) {
        position_(x, y, z);
    }
    
    unsigned int Atom::getSerial() const {
        return serial;
    }
    
    const Atom::element & Atom::getElement() const {
        return element_;
    }
    
    const vec3f & Atom::getPosition() const {
        return position_;
    }
    
    void Atom::setAltLoc(char value) {
        altLoc_ = value == ' ' ? 0 : value;
    }
    
    char Atom::getAltLoc() const {
        return altLoc_;
    }
    
    std::string Atom::getName() {
        return name_;
    }
    
    const std::unordered_map<std::string, Atom::element> Atom::elements({
        {"H", Atom::element("Hydrogen", "H", 1, 1.2, 0.31)},
        {"HE", Atom::element("Helium", "He", 2, 1.4, 0.28)},
        {"LI", Atom::element("Lithium", "Li", 3, 1.82, 1.28)},
        {"BE", Atom::element("Beryllium", "Be", 4, 0, 0.96)},
        {"B", Atom::element("Boron", "B", 5, 0, 0.84)},
        {"C", Atom::element("Carbon", "C", 6, 1.7, 0.76)},
        {"N", Atom::element("Nitrogen", "N", 7, 1.55, 0.71)},
        {"O", Atom::element("Oxygen", "O", 8, 1.52, 0.66)},
        {"F", Atom::element("Fluorine", "F", 9, 1.47, 0.57)},
        {"NE", Atom::element("Neon", "Ne", 10, 1.54, 0.58)},
        {"NA", Atom::element("Sodium", "Na", 11, 2.27, 1.66)},
        {"MG", Atom::element("Magnesium", "Mg", 12, 1.73, 1.41)},
        {"AL", Atom::element("Aluminum", "Al", 13, 0, 1.21)},
        {"SI", Atom::element("Silicon", "Si", 14, 2.1, 1.11)},
        {"P", Atom::element("Phosphorus", "P", 15, 1.8, 1.07)},
        {"S", Atom::element("Sulfur", "S", 16, 1.8, 1.05)},
        {"CL", Atom::element("Chlorine", "Cl", 17, 1.75, 1.02)},
        {"R", Atom::element("Argon", "Ar", 18, 1.88, 1.06)},
        {"K", Atom::element("Potassium", "K", 19, 2.75, 2.03)},
        {"CA", Atom::element("Calcium", "Ca", 20, 0, 1.76)},
        {"SC", Atom::element("Scandium", "Sc", 21, 0, 1.7)},
        {"TI", Atom::element("Titanium", "Ti", 22, 0, 1.6)},
        {"V", Atom::element("Vanadium", "V", 23, 0, 1.53)},
        {"CR", Atom::element("Chromium", "Cr", 24, 0, 1.39)},
        {"MN", Atom::element("Manganese", "Mn", 25, 0, 1.39)},
        {"FE", Atom::element("Iron", "Fe", 26, 0, 1.32)},
        {"CO", Atom::element("Cobalt", "Co", 27, 0, 1.26)},
        {"NI", Atom::element("Nickel", "Ni", 28, 1.63, 1.24)},
        {"CU", Atom::element("Copper", "Cu", 29, 1.4, 1.32)},
        {"ZN", Atom::element("Zinc", "Zn", 30, 1.39, 1.22)},
        {"GA", Atom::element("Gallium", "Ga", 31, 1.87, 1.22)},
        {"GE", Atom::element("Germanium", "Ge", 32, 0, 1.2)},
        {"AS", Atom::element("Arsenic", "As", 33, 1.85, 1.19)},
        {"SE", Atom::element("Selenium", "Se", 34, 1.9, 1.2)},
        {"BR", Atom::element("Bromine", "Br", 35, 1.85, 1.2)},
        {"KR", Atom::element("Krypton", "Kr", 36, 2.02, 1.16)},
        {"RB", Atom::element("Rubidium", "Rb", 37, 0, 2.2)},
        {"SR", Atom::element("Strontium", "Sr", 38, 0, 1.95)},
        {"Y", Atom::element("Yttrium", "Y", 39, 0, 1.9)},
        {"ZR", Atom::element("Zirconium", "Zr", 40, 0, 1.75)},
        {"NB", Atom::element("Niobium", "Nb", 41, 0, 1.64)},
        {"MO", Atom::element("Molybdenum", "Mo", 42, 0, 1.54)},
        {"TC", Atom::element("Technetium", "Tc", 43, 0, 1.47)},
        {"RU", Atom::element("Ruthenium", "Ru", 44, 0, 1.46)},
        {"RH", Atom::element("Rhodium", "Rh", 45, 0, 1.42)},
        {"PD", Atom::element("Palladium", "Pd", 46, 1.63, 1.39)},
        {"AG", Atom::element("Silver", "Ag", 47, 1.72, 1.45)},
        {"CD", Atom::element("Cadmium", "Cd", 48, 1.58, 1.44)},
        {"IN", Atom::element("Indium", "In", 49, 1.93, 1.42)},
        {"SN", Atom::element("Tin", "Sn", 50, 2.17, 1.39)},
        {"SB", Atom::element("Antimony", "Sb", 51, 0, 1.39)},
        {"TE", Atom::element("Tellurium", "Te", 52, 2.06, 1.38)},
        {"I", Atom::element("Iodine", "I", 53, 1.98, 1.39)},
        {"XE", Atom::element("Xenon", "Xe", 54, 2.16, 1.4)},
        {"CS", Atom::element("Cesium", "Cs", 55, 0, 2.44)},
        {"BA", Atom::element("Barium", "Ba", 56, 0, 2.15)},
        {"LA", Atom::element("Lanthanum", "La", 57, 0, 2.07)},
        {"CE", Atom::element("Cerium", "Ce", 58, 0, 2.04)},
        {"PR", Atom::element("Praseodymium", "Pr", 59, 0, 2.03)},
        {"ND", Atom::element("Neodymium", "Nd", 60, 0, 2.01)},
        {"PM", Atom::element("Promethium", "Pm", 61, 0, 1.99)},
        {"SM", Atom::element("Samarium", "Sm", 62, 0, 1.98)},
        {"EU", Atom::element("Europium", "Eu", 63, 0, 1.98)},
        {"GD", Atom::element("Gadolinium", "Gd", 64, 0, 1.96)},
        {"TB", Atom::element("Terbium", "Tb", 65, 0, 1.94)},
        {"DY", Atom::element("Dysprosium", "Dy", 66, 0, 1.92)},
        {"HO", Atom::element("Holmium", "Ho", 67, 0, 1.92)},
        {"ER", Atom::element("Erbium", "Er", 68, 0, 1.89)},
        {"TM", Atom::element("Thulium", "Tm", 69, 0, 1.9)},
        {"YB", Atom::element("Ytterbium", "Yb", 70, 0, 1.87)},
        {"LU", Atom::element("Lutetium", "Lu", 71, 0, 1.87)},
        {"HF", Atom::element("Hafnium", "Hf", 72, 0, 1.75)},
        {"TA", Atom::element("Tantalum", "Ta", 73, 0, 1.7)},
        {"W", Atom::element("Tungsten", "W", 74, 0, 1.62)},
        {"RE", Atom::element("Rhenium", "Re", 75, 0, 1.51)},
        {"OS", Atom::element("Osmium", "Os", 76, 0, 1.44)},
        {"IR", Atom::element("Iridium", "Ir", 77, 0, 1.41)},
        {"PT", Atom::element("Platinum", "Pt", 78, 1.75, 1.36)},
        {"AU", Atom::element("Gold", "Au", 79, 1.66, 1.36)},
        {"HG", Atom::element("Mercury", "Hg", 80, 1.55, 1.32)},
        {"TL", Atom::element("Thallium", "Tl", 81, 1.96, 1.45)},
        {"PB", Atom::element("Lead", "Pb", 82, 2.02, 1.46)},
        {"BI", Atom::element("Bismuth", "Bi", 83, 0, 1.48)},
        {"PO", Atom::element("Polonium", "Po", 84, 0, 1.4)},
        {"AT", Atom::element("Astatine", "At", 85, 0, 1.5)},
        {"RN", Atom::element("Radon", "Rn", 86, 0, 1.5)},
        {"FR", Atom::element("Francium", "Fr", 87, 0, 2.6)},
        {"RA", Atom::element("Radium", "Ra", 88, 0, 2.21)},
        {"AC", Atom::element("Actinium", "Ac", 89, 0, 2.15)},
        {"TH", Atom::element("Thorium", "Th", 90, 0, 2.06)},
        {"PA", Atom::element("Protactinium", "Pa", 91, 0, 2)},
        {"U", Atom::element("Uranium", "U", 92, 1.86, 1.96)},
        {"NP", Atom::element("Neptunium", "Np", 93, 0, 1.9)},
        {"PU", Atom::element("Plutonium", "Pu", 94, 0, 1.87)},
        {"AM", Atom::element("Americium", "Am", 95, 0, 1.8)},
        {"CM", Atom::element("Curium", "Cm", 96, 0, 1.69)},
        {"BK", Atom::element("Berkelium", "Bk", 97, 0, 0)},
        {"CF", Atom::element("Californium", "Cf", 98, 0, 0)},
        {"ES", Atom::element("Einsteinium", "Es", 99, 0, 0)},
        {"FM", Atom::element("Fermium", "Fm", 100, 0, 0)},
        {"MD", Atom::element("Mendelevium", "Md", 101, 0, 0)},
        {"NO", Atom::element("Nobelium", "No", 102, 0, 0)},
        {"LR", Atom::element("Lawrencium", "Lr", 103, 0, 0)},
        {"RF", Atom::element("Rutherfordium", "Rf", 104, 0, 0)},
        {"DB", Atom::element("Dubnium", "Db", 105, 0, 0)},
        {"SG", Atom::element("Seaborgium", "Sg", 106, 0, 0)},
        {"BH", Atom::element("Bohrium", "Bh", 107, 0, 0)},
        {"HS", Atom::element("Hassium", "Hs", 108, 0, 0)},
        {"MT", Atom::element("Meitnerium", "Mt", 109, 0, 0)},
        {"DS", Atom::element("Darmstadtium", "Ds", 110, 0, 0)},
        {"RG", Atom::element("Roentgenium", "Rg", 111, 0, 0)},
        {"CN", Atom::element("Copernicium", "Cn", 112, 0, 0)},
        {"UUT", Atom::element("Ununtrium", "Uut", 113, 0, 0)},
        {"UUQ", Atom::element("Ununquadium", "Uuq", 114, 0, 0)},
        {"UUP", Atom::element("Ununpentium", "Uup", 115, 0, 0)},
        {"UUH", Atom::element("Ununhexium", "Uuh", 116, 0, 0)},
        {"UUS", Atom::element("Ununseptium", "Uus", 117, 0, 0)},
        {"UUO", Atom::element("Ununoctium", "Uuo", 118, 0, 0)}
    });

    
}