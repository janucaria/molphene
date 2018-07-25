#include "atom.h"
#include "chain.h"
#include "compound.h"
#include "model.h"

namespace molphene {

atom::element::element(std::string name,
                       std::string symbol,
                       unsigned char number,
                       float VdWRadii,
                       float covalentRadii)
: name(name)
, symbol(symbol)
, number(number)
, radiiVdW(VdWRadii)
, radiiCovalent(covalentRadii)
{
}

atom::atom(compound& compound,
           const std::string& elementSymbol,
           std::string name,
           unsigned int serial)
: compoundPtr_(&compound)
, element_(elements.at(elementSymbol))
, name_(name)
, serial(serial)
, altLoc_(0)
{
}

void
atom::setPosition(float x, float y, float z)
{
  position_ = {x, y, z};
}

unsigned int
atom::getSerial() const
{
  return serial;
}

const atom::element&
atom::getElement() const
{
  return element_;
}

const vec3f&
atom::getPosition() const
{
  return position_;
}

void
atom::setAltLoc(char value)
{
  altLoc_ = value == ' ' ? 0 : value;
}

char
atom::getAltLoc() const
{
  return altLoc_;
}

std::string
atom::getName()
{
  return name_;
}

const std::unordered_map<std::string, atom::element>
 atom::elements({{"H", atom::element("Hydrogen", "H", 1, 1.2, 0.31)},
                 {"HE", atom::element("Helium", "He", 2, 1.4, 0.28)},
                 {"LI", atom::element("Lithium", "Li", 3, 1.82, 1.28)},
                 {"BE", atom::element("Beryllium", "Be", 4, 0, 0.96)},
                 {"B", atom::element("Boron", "B", 5, 0, 0.84)},
                 {"C", atom::element("Carbon", "C", 6, 1.7, 0.76)},
                 {"N", atom::element("Nitrogen", "N", 7, 1.55, 0.71)},
                 {"O", atom::element("Oxygen", "O", 8, 1.52, 0.66)},
                 {"F", atom::element("Fluorine", "F", 9, 1.47, 0.57)},
                 {"NE", atom::element("Neon", "Ne", 10, 1.54, 0.58)},
                 {"NA", atom::element("Sodium", "Na", 11, 2.27, 1.66)},
                 {"MG", atom::element("Magnesium", "Mg", 12, 1.73, 1.41)},
                 {"AL", atom::element("Aluminum", "Al", 13, 0, 1.21)},
                 {"SI", atom::element("Silicon", "Si", 14, 2.1, 1.11)},
                 {"P", atom::element("Phosphorus", "P", 15, 1.8, 1.07)},
                 {"S", atom::element("Sulfur", "S", 16, 1.8, 1.05)},
                 {"CL", atom::element("Chlorine", "Cl", 17, 1.75, 1.02)},
                 {"R", atom::element("Argon", "Ar", 18, 1.88, 1.06)},
                 {"K", atom::element("Potassium", "K", 19, 2.75, 2.03)},
                 {"CA", atom::element("Calcium", "Ca", 20, 0, 1.76)},
                 {"SC", atom::element("Scandium", "Sc", 21, 0, 1.7)},
                 {"TI", atom::element("Titanium", "Ti", 22, 0, 1.6)},
                 {"V", atom::element("Vanadium", "V", 23, 0, 1.53)},
                 {"CR", atom::element("Chromium", "Cr", 24, 0, 1.39)},
                 {"MN", atom::element("Manganese", "Mn", 25, 0, 1.39)},
                 {"FE", atom::element("Iron", "Fe", 26, 0, 1.32)},
                 {"CO", atom::element("Cobalt", "Co", 27, 0, 1.26)},
                 {"NI", atom::element("Nickel", "Ni", 28, 1.63, 1.24)},
                 {"CU", atom::element("Copper", "Cu", 29, 1.4, 1.32)},
                 {"ZN", atom::element("Zinc", "Zn", 30, 1.39, 1.22)},
                 {"GA", atom::element("Gallium", "Ga", 31, 1.87, 1.22)},
                 {"GE", atom::element("Germanium", "Ge", 32, 0, 1.2)},
                 {"AS", atom::element("Arsenic", "As", 33, 1.85, 1.19)},
                 {"SE", atom::element("Selenium", "Se", 34, 1.9, 1.2)},
                 {"BR", atom::element("Bromine", "Br", 35, 1.85, 1.2)},
                 {"KR", atom::element("Krypton", "Kr", 36, 2.02, 1.16)},
                 {"RB", atom::element("Rubidium", "Rb", 37, 0, 2.2)},
                 {"SR", atom::element("Strontium", "Sr", 38, 0, 1.95)},
                 {"Y", atom::element("Yttrium", "Y", 39, 0, 1.9)},
                 {"ZR", atom::element("Zirconium", "Zr", 40, 0, 1.75)},
                 {"NB", atom::element("Niobium", "Nb", 41, 0, 1.64)},
                 {"MO", atom::element("Molybdenum", "Mo", 42, 0, 1.54)},
                 {"TC", atom::element("Technetium", "Tc", 43, 0, 1.47)},
                 {"RU", atom::element("Ruthenium", "Ru", 44, 0, 1.46)},
                 {"RH", atom::element("Rhodium", "Rh", 45, 0, 1.42)},
                 {"PD", atom::element("Palladium", "Pd", 46, 1.63, 1.39)},
                 {"AG", atom::element("Silver", "Ag", 47, 1.72, 1.45)},
                 {"CD", atom::element("Cadmium", "Cd", 48, 1.58, 1.44)},
                 {"IN", atom::element("Indium", "In", 49, 1.93, 1.42)},
                 {"SN", atom::element("Tin", "Sn", 50, 2.17, 1.39)},
                 {"SB", atom::element("Antimony", "Sb", 51, 0, 1.39)},
                 {"TE", atom::element("Tellurium", "Te", 52, 2.06, 1.38)},
                 {"I", atom::element("Iodine", "I", 53, 1.98, 1.39)},
                 {"XE", atom::element("Xenon", "Xe", 54, 2.16, 1.4)},
                 {"CS", atom::element("Cesium", "Cs", 55, 0, 2.44)},
                 {"BA", atom::element("Barium", "Ba", 56, 0, 2.15)},
                 {"LA", atom::element("Lanthanum", "La", 57, 0, 2.07)},
                 {"CE", atom::element("Cerium", "Ce", 58, 0, 2.04)},
                 {"PR", atom::element("Praseodymium", "Pr", 59, 0, 2.03)},
                 {"ND", atom::element("Neodymium", "Nd", 60, 0, 2.01)},
                 {"PM", atom::element("Promethium", "Pm", 61, 0, 1.99)},
                 {"SM", atom::element("Samarium", "Sm", 62, 0, 1.98)},
                 {"EU", atom::element("Europium", "Eu", 63, 0, 1.98)},
                 {"GD", atom::element("Gadolinium", "Gd", 64, 0, 1.96)},
                 {"TB", atom::element("Terbium", "Tb", 65, 0, 1.94)},
                 {"DY", atom::element("Dysprosium", "Dy", 66, 0, 1.92)},
                 {"HO", atom::element("Holmium", "Ho", 67, 0, 1.92)},
                 {"ER", atom::element("Erbium", "Er", 68, 0, 1.89)},
                 {"TM", atom::element("Thulium", "Tm", 69, 0, 1.9)},
                 {"YB", atom::element("Ytterbium", "Yb", 70, 0, 1.87)},
                 {"LU", atom::element("Lutetium", "Lu", 71, 0, 1.87)},
                 {"HF", atom::element("Hafnium", "Hf", 72, 0, 1.75)},
                 {"TA", atom::element("Tantalum", "Ta", 73, 0, 1.7)},
                 {"W", atom::element("Tungsten", "W", 74, 0, 1.62)},
                 {"RE", atom::element("Rhenium", "Re", 75, 0, 1.51)},
                 {"OS", atom::element("Osmium", "Os", 76, 0, 1.44)},
                 {"IR", atom::element("Iridium", "Ir", 77, 0, 1.41)},
                 {"PT", atom::element("Platinum", "Pt", 78, 1.75, 1.36)},
                 {"AU", atom::element("Gold", "Au", 79, 1.66, 1.36)},
                 {"HG", atom::element("Mercury", "Hg", 80, 1.55, 1.32)},
                 {"TL", atom::element("Thallium", "Tl", 81, 1.96, 1.45)},
                 {"PB", atom::element("Lead", "Pb", 82, 2.02, 1.46)},
                 {"BI", atom::element("Bismuth", "Bi", 83, 0, 1.48)},
                 {"PO", atom::element("Polonium", "Po", 84, 0, 1.4)},
                 {"AT", atom::element("Astatine", "At", 85, 0, 1.5)},
                 {"RN", atom::element("Radon", "Rn", 86, 0, 1.5)},
                 {"FR", atom::element("Francium", "Fr", 87, 0, 2.6)},
                 {"RA", atom::element("Radium", "Ra", 88, 0, 2.21)},
                 {"AC", atom::element("Actinium", "Ac", 89, 0, 2.15)},
                 {"TH", atom::element("Thorium", "Th", 90, 0, 2.06)},
                 {"PA", atom::element("Protactinium", "Pa", 91, 0, 2)},
                 {"U", atom::element("Uranium", "U", 92, 1.86, 1.96)},
                 {"NP", atom::element("Neptunium", "Np", 93, 0, 1.9)},
                 {"PU", atom::element("Plutonium", "Pu", 94, 0, 1.87)},
                 {"AM", atom::element("Americium", "Am", 95, 0, 1.8)},
                 {"CM", atom::element("Curium", "Cm", 96, 0, 1.69)},
                 {"BK", atom::element("Berkelium", "Bk", 97, 0, 0)},
                 {"CF", atom::element("Californium", "Cf", 98, 0, 0)},
                 {"ES", atom::element("Einsteinium", "Es", 99, 0, 0)},
                 {"FM", atom::element("Fermium", "Fm", 100, 0, 0)},
                 {"MD", atom::element("Mendelevium", "Md", 101, 0, 0)},
                 {"NO", atom::element("Nobelium", "No", 102, 0, 0)},
                 {"LR", atom::element("Lawrencium", "Lr", 103, 0, 0)},
                 {"RF", atom::element("Rutherfordium", "Rf", 104, 0, 0)},
                 {"DB", atom::element("Dubnium", "Db", 105, 0, 0)},
                 {"SG", atom::element("Seaborgium", "Sg", 106, 0, 0)},
                 {"BH", atom::element("Bohrium", "Bh", 107, 0, 0)},
                 {"HS", atom::element("Hassium", "Hs", 108, 0, 0)},
                 {"MT", atom::element("Meitnerium", "Mt", 109, 0, 0)},
                 {"DS", atom::element("Darmstadtium", "Ds", 110, 0, 0)},
                 {"RG", atom::element("Roentgenium", "Rg", 111, 0, 0)},
                 {"CN", atom::element("Copernicium", "Cn", 112, 0, 0)},
                 {"UUT", atom::element("Ununtrium", "Uut", 113, 0, 0)},
                 {"UUQ", atom::element("Ununquadium", "Uuq", 114, 0, 0)},
                 {"UUP", atom::element("Ununpentium", "Uup", 115, 0, 0)},
                 {"UUH", atom::element("Ununhexium", "Uuh", 116, 0, 0)},
                 {"UUS", atom::element("Ununseptium", "Uus", 117, 0, 0)},
                 {"UUO", atom::element("Ununoctium", "Uuo", 118, 0, 0)}});

} // namespace molphene