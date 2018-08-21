#include "Atom.hpp"
#include "Chain.hpp"
#include "Compound.hpp"
#include "Model.hpp"

namespace molphene {

Atom::Atom(Compound& compound,
           std::string elsym,
           std::string name,
           unsigned int serial)
: compound_ptr_{&compound}
, element_{std::move(elsym)}
, name_{std::move(name)}
, serial_{serial}
{
}

char
Atom::altloc() const
{
  return altloc_;
}

const Atom::Element&
Atom::element() const
{
  static const Atom::Element hydrogen{"Hydrogen", "H", 1, 1.2, 0.31};
  static const Atom::Element helium{"Helium", "He", 2, 1.4, 0.28};
  static const Atom::Element lithium{"Lithium", "Li", 3, 1.82, 1.28};
  static const Atom::Element beryllium{"Beryllium", "Be", 4, 0, 0.96};
  static const Atom::Element boron{"Boron", "B", 5, 0, 0.84};
  static const Atom::Element carbon{"Carbon", "C", 6, 1.7, 0.76};
  static const Atom::Element nitrogen{"Nitrogen", "N", 7, 1.55, 0.71};
  static const Atom::Element oxygen{"Oxygen", "O", 8, 1.52, 0.66};
  static const Atom::Element fluorine{"Fluorine", "F", 9, 1.47, 0.57};
  static const Atom::Element neon{"Neon", "Ne", 10, 1.54, 0.58};
  static const Atom::Element sodium{"Sodium", "Na", 11, 2.27, 1.66};
  static const Atom::Element magnesium{"Magnesium", "Mg", 12, 1.73, 1.41};
  static const Atom::Element aluminum{"Aluminum", "Al", 13, 0, 1.21};
  static const Atom::Element silicon{"Silicon", "Si", 14, 2.1, 1.11};
  static const Atom::Element phosphorus{"Phosphorus", "P", 15, 1.8, 1.07};
  static const Atom::Element sulfur{"Sulfur", "S", 16, 1.8, 1.05};
  static const Atom::Element chlorine{"Chlorine", "Cl", 17, 1.75, 1.02};
  static const Atom::Element argon{"Argon", "Ar", 18, 1.88, 1.06};
  static const Atom::Element potassium{"Potassium", "K", 19, 2.75, 2.03};
  static const Atom::Element calcium{"Calcium", "Ca", 20, 0, 1.76};
  static const Atom::Element scandium{"Scandium", "Sc", 21, 0, 1.7};
  static const Atom::Element titanium{"Titanium", "Ti", 22, 0, 1.6};
  static const Atom::Element vanadium{"Vanadium", "V", 23, 0, 1.53};
  static const Atom::Element chromium{"Chromium", "Cr", 24, 0, 1.39};
  static const Atom::Element manganese{"Manganese", "Mn", 25, 0, 1.39};
  static const Atom::Element iron{"Iron", "Fe", 26, 0, 1.32};
  static const Atom::Element cobalt{"Cobalt", "Co", 27, 0, 1.26};
  static const Atom::Element nickel{"Nickel", "Ni", 28, 1.63, 1.24};
  static const Atom::Element copper{"Copper", "Cu", 29, 1.4, 1.32};
  static const Atom::Element zinc{"Zinc", "Zn", 30, 1.39, 1.22};
  static const Atom::Element gallium{"Gallium", "Ga", 31, 1.87, 1.22};
  static const Atom::Element germanium{"Germanium", "Ge", 32, 0, 1.2};
  static const Atom::Element arsenic{"Arsenic", "As", 33, 1.85, 1.19};
  static const Atom::Element selenium{"Selenium", "Se", 34, 1.9, 1.2};
  static const Atom::Element bromine{"Bromine", "Br", 35, 1.85, 1.2};
  static const Atom::Element krypton{"Krypton", "Kr", 36, 2.02, 1.16};
  static const Atom::Element rubidium{"Rubidium", "Rb", 37, 0, 2.2};
  static const Atom::Element strontium{"Strontium", "Sr", 38, 0, 1.95};
  static const Atom::Element yttrium{"Yttrium", "Y", 39, 0, 1.9};
  static const Atom::Element zirconium{"Zirconium", "Zr", 40, 0, 1.75};
  static const Atom::Element niobium{"Niobium", "Nb", 41, 0, 1.64};
  static const Atom::Element molybdenum{"Molybdenum", "Mo", 42, 0, 1.54};
  static const Atom::Element technetium{"Technetium", "Tc", 43, 0, 1.47};
  static const Atom::Element ruthenium{"Ruthenium", "Ru", 44, 0, 1.46};
  static const Atom::Element rhodium{"Rhodium", "Rh", 45, 0, 1.42};
  static const Atom::Element palladium{"Palladium", "Pd", 46, 1.63, 1.39};
  static const Atom::Element silver{"Silver", "Ag", 47, 1.72, 1.45};
  static const Atom::Element cadmium{"Cadmium", "Cd", 48, 1.58, 1.44};
  static const Atom::Element indium{"Indium", "In", 49, 1.93, 1.42};
  static const Atom::Element tin{"Tin", "Sn", 50, 2.17, 1.39};
  static const Atom::Element antimony{"Antimony", "Sb", 51, 0, 1.39};
  static const Atom::Element tellurium{"Tellurium", "Te", 52, 2.06, 1.38};
  static const Atom::Element iodine{"Iodine", "I", 53, 1.98, 1.39};
  static const Atom::Element xenon{"Xenon", "Xe", 54, 2.16, 1.4};
  static const Atom::Element cesium{"Cesium", "Cs", 55, 0, 2.44};
  static const Atom::Element barium{"Barium", "Ba", 56, 0, 2.15};
  static const Atom::Element lanthanum{"Lanthanum", "La", 57, 0, 2.07};
  static const Atom::Element cerium{"Cerium", "Ce", 58, 0, 2.04};
  static const Atom::Element praseodymium{"Praseodymium", "Pr", 59, 0, 2.03};
  static const Atom::Element neodymium{"Neodymium", "Nd", 60, 0, 2.01};
  static const Atom::Element promethium{"Promethium", "Pm", 61, 0, 1.99};
  static const Atom::Element samarium{"Samarium", "Sm", 62, 0, 1.98};
  static const Atom::Element europium{"Europium", "Eu", 63, 0, 1.98};
  static const Atom::Element gadolinium{"Gadolinium", "Gd", 64, 0, 1.96};
  static const Atom::Element terbium{"Terbium", "Tb", 65, 0, 1.94};
  static const Atom::Element dysprosium{"Dysprosium", "Dy", 66, 0, 1.92};
  static const Atom::Element holmium{"Holmium", "Ho", 67, 0, 1.92};
  static const Atom::Element erbium{"Erbium", "Er", 68, 0, 1.89};
  static const Atom::Element thulium{"Thulium", "Tm", 69, 0, 1.9};
  static const Atom::Element ytterbium{"Ytterbium", "Yb", 70, 0, 1.87};
  static const Atom::Element lutetium{"Lutetium", "Lu", 71, 0, 1.87};
  static const Atom::Element hafnium{"Hafnium", "Hf", 72, 0, 1.75};
  static const Atom::Element tantalum{"Tantalum", "Ta", 73, 0, 1.7};
  static const Atom::Element tungsten{"Tungsten", "W", 74, 0, 1.62};
  static const Atom::Element rhenium{"Rhenium", "Re", 75, 0, 1.51};
  static const Atom::Element osmium{"Osmium", "Os", 76, 0, 1.44};
  static const Atom::Element iridium{"Iridium", "Ir", 77, 0, 1.41};
  static const Atom::Element platinum{"Platinum", "Pt", 78, 1.75, 1.36};
  static const Atom::Element gold{"Gold", "Au", 79, 1.66, 1.36};
  static const Atom::Element mercury{"Mercury", "Hg", 80, 1.55, 1.32};
  static const Atom::Element thallium{"Thallium", "Tl", 81, 1.96, 1.45};
  static const Atom::Element lead{"Lead", "Pb", 82, 2.02, 1.46};
  static const Atom::Element bismuth{"Bismuth", "Bi", 83, 0, 1.48};
  static const Atom::Element polonium{"Polonium", "Po", 84, 0, 1.4};
  static const Atom::Element astatine{"Astatine", "At", 85, 0, 1.5};
  static const Atom::Element radon{"Radon", "Rn", 86, 0, 1.5};
  static const Atom::Element francium{"Francium", "Fr", 87, 0, 2.6};
  static const Atom::Element radium{"Radium", "Ra", 88, 0, 2.21};
  static const Atom::Element actinium{"Actinium", "Ac", 89, 0, 2.15};
  static const Atom::Element thorium{"Thorium", "Th", 90, 0, 2.06};
  static const Atom::Element protactinium{"Protactinium", "Pa", 91, 0, 2};
  static const Atom::Element uranium{"Uranium", "U", 92, 1.86, 1.96};
  static const Atom::Element neptunium{"Neptunium", "Np", 93, 0, 1.9};
  static const Atom::Element plutonium{"Plutonium", "Pu", 94, 0, 1.87};
  static const Atom::Element americium{"Americium", "Am", 95, 0, 1.8};
  static const Atom::Element curium{"Curium", "Cm", 96, 0, 1.69};
  static const Atom::Element berkelium{"Berkelium", "Bk", 97, 0, 0};
  static const Atom::Element californium{"Californium", "Cf", 98, 0, 0};
  static const Atom::Element einsteinium{"Einsteinium", "Es", 99, 0, 0};
  static const Atom::Element fermium{"Fermium", "Fm", 100, 0, 0};
  static const Atom::Element mendelevium{"Mendelevium", "Md", 101, 0, 0};
  static const Atom::Element nobelium{"Nobelium", "No", 102, 0, 0};
  static const Atom::Element lawrencium{"Lawrencium", "Lr", 103, 0, 0};
  static const Atom::Element rutherfordium{"Rutherfordium", "Rf", 104, 0, 0};
  static const Atom::Element dubnium{"Dubnium", "Db", 105, 0, 0};
  static const Atom::Element seaborgium{"Seaborgium", "Sg", 106, 0, 0};
  static const Atom::Element bohrium{"Bohrium", "Bh", 107, 0, 0};
  static const Atom::Element hassium{"Hassium", "Hs", 108, 0, 0};
  static const Atom::Element meitnerium{"Meitnerium", "Mt", 109, 0, 0};
  static const Atom::Element darmstadtium{"Darmstadtium", "Ds", 110, 0, 0};
  static const Atom::Element roentgenium{"Roentgenium", "Rg", 111, 0, 0};
  static const Atom::Element copernicium{"Copernicium", "Cn", 112, 0, 0};
  static const Atom::Element ununtrium{"Ununtrium", "Uut", 113, 0, 0};
  static const Atom::Element ununquadium{"Ununquadium", "Uuq", 114, 0, 0};
  static const Atom::Element ununpentium{"Ununpentium", "Uup", 115, 0, 0};
  static const Atom::Element ununhexium{"Ununhexium", "Uuh", 116, 0, 0};
  static const Atom::Element ununseptium{"Ununseptium", "Uus", 117, 0, 0};
  static const Atom::Element ununoctium{"Ununoctium", "Uuo", 118, 0, 0};

  if(element_ == "H") {
    return hydrogen;
  }
  if(element_ == "HE") {
    return helium;
  }
  if(element_ == "LI") {
    return lithium;
  }
  if(element_ == "BE") {
    return beryllium;
  }
  if(element_ == "B") {
    return boron;
  }
  if(element_ == "C") {
    return carbon;
  }
  if(element_ == "N") {
    return nitrogen;
  }
  if(element_ == "O") {
    return oxygen;
  }
  if(element_ == "F") {
    return fluorine;
  }
  if(element_ == "NE") {
    return neon;
  }
  if(element_ == "NA") {
    return sodium;
  }
  if(element_ == "MG") {
    return magnesium;
  }
  if(element_ == "AL") {
    return aluminum;
  }
  if(element_ == "SI") {
    return silicon;
  }
  if(element_ == "P") {
    return phosphorus;
  }
  if(element_ == "S") {
    return sulfur;
  }
  if(element_ == "CL") {
    return chlorine;
  }
  if(element_ == "R") {
    return argon;
  }
  if(element_ == "K") {
    return potassium;
  }
  if(element_ == "CA") {
    return calcium;
  }
  if(element_ == "SC") {
    return scandium;
  }
  if(element_ == "TI") {
    return titanium;
  }
  if(element_ == "V") {
    return vanadium;
  }
  if(element_ == "CR") {
    return chromium;
  }
  if(element_ == "MN") {
    return manganese;
  }
  if(element_ == "FE") {
    return iron;
  }
  if(element_ == "CO") {
    return cobalt;
  }
  if(element_ == "NI") {
    return nickel;
  }
  if(element_ == "CU") {
    return copper;
  }
  if(element_ == "ZN") {
    return zinc;
  }
  if(element_ == "GA") {
    return gallium;
  }
  if(element_ == "GE") {
    return germanium;
  }
  if(element_ == "AS") {
    return arsenic;
  }
  if(element_ == "SE") {
    return selenium;
  }
  if(element_ == "BR") {
    return bromine;
  }
  if(element_ == "KR") {
    return krypton;
  }
  if(element_ == "RB") {
    return rubidium;
  }
  if(element_ == "SR") {
    return strontium;
  }
  if(element_ == "Y") {
    return yttrium;
  }
  if(element_ == "ZR") {
    return zirconium;
  }
  if(element_ == "NB") {
    return niobium;
  }
  if(element_ == "MO") {
    return molybdenum;
  }
  if(element_ == "TC") {
    return technetium;
  }
  if(element_ == "RU") {
    return ruthenium;
  }
  if(element_ == "RH") {
    return rhodium;
  }
  if(element_ == "PD") {
    return palladium;
  }
  if(element_ == "AG") {
    return silver;
  }
  if(element_ == "CD") {
    return cadmium;
  }
  if(element_ == "IN") {
    return indium;
  }
  if(element_ == "SN") {
    return tin;
  }
  if(element_ == "SB") {
    return antimony;
  }
  if(element_ == "TE") {
    return tellurium;
  }
  if(element_ == "I") {
    return iodine;
  }
  if(element_ == "XE") {
    return xenon;
  }
  if(element_ == "CS") {
    return cesium;
  }
  if(element_ == "BA") {
    return barium;
  }
  if(element_ == "LA") {
    return lanthanum;
  }
  if(element_ == "CE") {
    return cerium;
  }
  if(element_ == "PR") {
    return praseodymium;
  }
  if(element_ == "ND") {
    return neodymium;
  }
  if(element_ == "PM") {
    return promethium;
  }
  if(element_ == "SM") {
    return samarium;
  }
  if(element_ == "EU") {
    return europium;
  }
  if(element_ == "GD") {
    return gadolinium;
  }
  if(element_ == "TB") {
    return terbium;
  }
  if(element_ == "DY") {
    return dysprosium;
  }
  if(element_ == "HO") {
    return holmium;
  }
  if(element_ == "ER") {
    return erbium;
  }
  if(element_ == "TM") {
    return thulium;
  }
  if(element_ == "YB") {
    return ytterbium;
  }
  if(element_ == "LU") {
    return lutetium;
  }
  if(element_ == "HF") {
    return hafnium;
  }
  if(element_ == "TA") {
    return tantalum;
  }
  if(element_ == "W") {
    return tungsten;
  }
  if(element_ == "RE") {
    return rhenium;
  }
  if(element_ == "OS") {
    return osmium;
  }
  if(element_ == "IR") {
    return iridium;
  }
  if(element_ == "PT") {
    return platinum;
  }
  if(element_ == "AU") {
    return gold;
  }
  if(element_ == "HG") {
    return mercury;
  }
  if(element_ == "TL") {
    return thallium;
  }
  if(element_ == "PB") {
    return lead;
  }
  if(element_ == "BI") {
    return bismuth;
  }
  if(element_ == "PO") {
    return polonium;
  }
  if(element_ == "AT") {
    return astatine;
  }
  if(element_ == "RN") {
    return radon;
  }
  if(element_ == "FR") {
    return francium;
  }
  if(element_ == "RA") {
    return radium;
  }
  if(element_ == "AC") {
    return actinium;
  }
  if(element_ == "TH") {
    return thorium;
  }
  if(element_ == "PA") {
    return protactinium;
  }
  if(element_ == "U") {
    return uranium;
  }
  if(element_ == "NP") {
    return neptunium;
  }
  if(element_ == "PU") {
    return plutonium;
  }
  if(element_ == "AM") {
    return americium;
  }
  if(element_ == "CM") {
    return curium;
  }
  if(element_ == "BK") {
    return berkelium;
  }
  if(element_ == "CF") {
    return californium;
  }
  if(element_ == "ES") {
    return einsteinium;
  }
  if(element_ == "FM") {
    return fermium;
  }
  if(element_ == "MD") {
    return mendelevium;
  }
  if(element_ == "NO") {
    return nobelium;
  }
  if(element_ == "LR") {
    return lawrencium;
  }
  if(element_ == "RF") {
    return rutherfordium;
  }
  if(element_ == "DB") {
    return dubnium;
  }
  if(element_ == "SG") {
    return seaborgium;
  }
  if(element_ == "BH") {
    return bohrium;
  }
  if(element_ == "HS") {
    return hassium;
  }
  if(element_ == "MT") {
    return meitnerium;
  }
  if(element_ == "DS") {
    return darmstadtium;
  }
  if(element_ == "RG") {
    return roentgenium;
  }
  if(element_ == "CN") {
    return copernicium;
  }
  if(element_ == "UUT") {
    return ununtrium;
  }
  if(element_ == "UUQ") {
    return ununquadium;
  }
  if(element_ == "UUP") {
    return ununpentium;
  }
  if(element_ == "UUH") {
    return ununhexium;
  }
  if(element_ == "UUS") {
    return ununseptium;
  }
  if(element_ == "UUO") {
    return ununoctium;
  }

  // TODO(janucaria): Error element not recognise
  return hydrogen;
}

std::string
Atom::name() const
{
  return name_;
}

const Atom::Position&
Atom::position() const
{
  return position_;
}

unsigned int
Atom::serial() const
{
  return serial_;
}

void
Atom::altloc(char altloc)
{
  altloc_ = altloc == ' ' ? 0 : altloc;
}

const Atom::Position&
Atom::position(float x, float y, float z)
{
  return position_ = Vec3f{x, y, z};
}

Atom::Element::Element(std::string name,
                       std::string symbol,
                       unsigned char number,
                       float rVdW,
                       float rcov) noexcept
: name{std::move(name)}
, number{number}
, rcov{rcov}
, rvdw{rVdW}
, symbol{std::move(symbol)}
{
}

} // namespace molphene
