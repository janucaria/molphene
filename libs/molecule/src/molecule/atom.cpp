#include "atom.hpp"

namespace molphene {

atom::atom(std::string elsym, std::string name, unsigned int serial)
: element_{std::move(elsym)}
, name_{std::move(name)}
, serial_{serial}
{
}

auto atom::element() const noexcept -> const atom_element&
{
  static const atom_element hydrogen{"Hydrogen", "H", 1, 1.2, 0.31};
  static const atom_element helium{"Helium", "He", 2, 1.4, 0.28};
  static const atom_element lithium{"Lithium", "Li", 3, 1.82, 1.28};
  static const atom_element beryllium{"Beryllium", "Be", 4, 0, 0.96};
  static const atom_element boron{"Boron", "B", 5, 0, 0.84};
  static const atom_element carbon{"Carbon", "C", 6, 1.7, 0.76};
  static const atom_element nitrogen{"Nitrogen", "N", 7, 1.55, 0.71};
  static const atom_element oxygen{"Oxygen", "O", 8, 1.52, 0.66};
  static const atom_element fluorine{"Fluorine", "F", 9, 1.47, 0.57};
  static const atom_element neon{"Neon", "Ne", 10, 1.54, 0.58};
  static const atom_element sodium{"Sodium", "Na", 11, 2.27, 1.66};
  static const atom_element magnesium{"Magnesium", "Mg", 12, 1.73, 1.41};
  static const atom_element aluminum{"Aluminum", "Al", 13, 0, 1.21};
  static const atom_element silicon{"Silicon", "Si", 14, 2.1, 1.11};
  static const atom_element phosphorus{"Phosphorus", "P", 15, 1.8, 1.07};
  static const atom_element sulfur{"Sulfur", "S", 16, 1.8, 1.05};
  static const atom_element chlorine{"Chlorine", "Cl", 17, 1.75, 1.02};
  static const atom_element argon{"Argon", "Ar", 18, 1.88, 1.06};
  static const atom_element potassium{"Potassium", "K", 19, 2.75, 2.03};
  static const atom_element calcium{"Calcium", "Ca", 20, 0, 1.76};
  static const atom_element scandium{"Scandium", "Sc", 21, 0, 1.7};
  static const atom_element titanium{"Titanium", "Ti", 22, 0, 1.6};
  static const atom_element vanadium{"Vanadium", "V", 23, 0, 1.53};
  static const atom_element chromium{"Chromium", "Cr", 24, 0, 1.39};
  static const atom_element manganese{"Manganese", "Mn", 25, 0, 1.39};
  static const atom_element iron{"Iron", "Fe", 26, 0, 1.32};
  static const atom_element cobalt{"Cobalt", "Co", 27, 0, 1.26};
  static const atom_element nickel{"Nickel", "Ni", 28, 1.63, 1.24};
  static const atom_element copper{"Copper", "Cu", 29, 1.4, 1.32};
  static const atom_element zinc{"Zinc", "Zn", 30, 1.39, 1.22};
  static const atom_element gallium{"Gallium", "Ga", 31, 1.87, 1.22};
  static const atom_element germanium{"Germanium", "Ge", 32, 0, 1.2};
  static const atom_element arsenic{"Arsenic", "As", 33, 1.85, 1.19};
  static const atom_element selenium{"Selenium", "Se", 34, 1.9, 1.2};
  static const atom_element bromine{"Bromine", "Br", 35, 1.85, 1.2};
  static const atom_element krypton{"Krypton", "Kr", 36, 2.02, 1.16};
  static const atom_element rubidium{"Rubidium", "Rb", 37, 0, 2.2};
  static const atom_element strontium{"Strontium", "Sr", 38, 0, 1.95};
  static const atom_element yttrium{"Yttrium", "Y", 39, 0, 1.9};
  static const atom_element zirconium{"Zirconium", "Zr", 40, 0, 1.75};
  static const atom_element niobium{"Niobium", "Nb", 41, 0, 1.64};
  static const atom_element molybdenum{"Molybdenum", "Mo", 42, 0, 1.54};
  static const atom_element technetium{"Technetium", "Tc", 43, 0, 1.47};
  static const atom_element ruthenium{"Ruthenium", "Ru", 44, 0, 1.46};
  static const atom_element rhodium{"Rhodium", "Rh", 45, 0, 1.42};
  static const atom_element palladium{"Palladium", "Pd", 46, 1.63, 1.39};
  static const atom_element silver{"Silver", "Ag", 47, 1.72, 1.45};
  static const atom_element cadmium{"Cadmium", "Cd", 48, 1.58, 1.44};
  static const atom_element indium{"Indium", "In", 49, 1.93, 1.42};
  static const atom_element tin{"Tin", "Sn", 50, 2.17, 1.39};
  static const atom_element antimony{"Antimony", "Sb", 51, 0, 1.39};
  static const atom_element tellurium{"Tellurium", "Te", 52, 2.06, 1.38};
  static const atom_element iodine{"Iodine", "I", 53, 1.98, 1.39};
  static const atom_element xenon{"Xenon", "Xe", 54, 2.16, 1.4};
  static const atom_element cesium{"Cesium", "Cs", 55, 0, 2.44};
  static const atom_element barium{"Barium", "Ba", 56, 0, 2.15};
  static const atom_element lanthanum{"Lanthanum", "La", 57, 0, 2.07};
  static const atom_element cerium{"Cerium", "Ce", 58, 0, 2.04};
  static const atom_element praseodymium{"Praseodymium", "Pr", 59, 0, 2.03};
  static const atom_element neodymium{"Neodymium", "Nd", 60, 0, 2.01};
  static const atom_element promethium{"Promethium", "Pm", 61, 0, 1.99};
  static const atom_element samarium{"Samarium", "Sm", 62, 0, 1.98};
  static const atom_element europium{"Europium", "Eu", 63, 0, 1.98};
  static const atom_element gadolinium{"Gadolinium", "Gd", 64, 0, 1.96};
  static const atom_element terbium{"Terbium", "Tb", 65, 0, 1.94};
  static const atom_element dysprosium{"Dysprosium", "Dy", 66, 0, 1.92};
  static const atom_element holmium{"Holmium", "Ho", 67, 0, 1.92};
  static const atom_element erbium{"Erbium", "Er", 68, 0, 1.89};
  static const atom_element thulium{"Thulium", "Tm", 69, 0, 1.9};
  static const atom_element ytterbium{"Ytterbium", "Yb", 70, 0, 1.87};
  static const atom_element lutetium{"Lutetium", "Lu", 71, 0, 1.87};
  static const atom_element hafnium{"Hafnium", "Hf", 72, 0, 1.75};
  static const atom_element tantalum{"Tantalum", "Ta", 73, 0, 1.7};
  static const atom_element tungsten{"Tungsten", "W", 74, 0, 1.62};
  static const atom_element rhenium{"Rhenium", "Re", 75, 0, 1.51};
  static const atom_element osmium{"Osmium", "Os", 76, 0, 1.44};
  static const atom_element iridium{"Iridium", "Ir", 77, 0, 1.41};
  static const atom_element platinum{"Platinum", "Pt", 78, 1.75, 1.36};
  static const atom_element gold{"Gold", "Au", 79, 1.66, 1.36};
  static const atom_element mercury{"Mercury", "Hg", 80, 1.55, 1.32};
  static const atom_element thallium{"Thallium", "Tl", 81, 1.96, 1.45};
  static const atom_element lead{"Lead", "Pb", 82, 2.02, 1.46};
  static const atom_element bismuth{"Bismuth", "Bi", 83, 0, 1.48};
  static const atom_element polonium{"Polonium", "Po", 84, 0, 1.4};
  static const atom_element astatine{"Astatine", "At", 85, 0, 1.5};
  static const atom_element radon{"Radon", "Rn", 86, 0, 1.5};
  static const atom_element francium{"Francium", "Fr", 87, 0, 2.6};
  static const atom_element radium{"Radium", "Ra", 88, 0, 2.21};
  static const atom_element actinium{"Actinium", "Ac", 89, 0, 2.15};
  static const atom_element thorium{"Thorium", "Th", 90, 0, 2.06};
  static const atom_element protactinium{"Protactinium", "Pa", 91, 0, 2};
  static const atom_element uranium{"Uranium", "U", 92, 1.86, 1.96};
  static const atom_element neptunium{"Neptunium", "Np", 93, 0, 1.9};
  static const atom_element plutonium{"Plutonium", "Pu", 94, 0, 1.87};
  static const atom_element americium{"Americium", "Am", 95, 0, 1.8};
  static const atom_element curium{"Curium", "Cm", 96, 0, 1.69};
  static const atom_element berkelium{"Berkelium", "Bk", 97, 0, 0};
  static const atom_element californium{"Californium", "Cf", 98, 0, 0};
  static const atom_element einsteinium{"Einsteinium", "Es", 99, 0, 0};
  static const atom_element fermium{"Fermium", "Fm", 100, 0, 0};
  static const atom_element mendelevium{"Mendelevium", "Md", 101, 0, 0};
  static const atom_element nobelium{"Nobelium", "No", 102, 0, 0};
  static const atom_element lawrencium{"Lawrencium", "Lr", 103, 0, 0};
  static const atom_element rutherfordium{"Rutherfordium", "Rf", 104, 0, 0};
  static const atom_element dubnium{"Dubnium", "Db", 105, 0, 0};
  static const atom_element seaborgium{"Seaborgium", "Sg", 106, 0, 0};
  static const atom_element bohrium{"Bohrium", "Bh", 107, 0, 0};
  static const atom_element hassium{"Hassium", "Hs", 108, 0, 0};
  static const atom_element meitnerium{"Meitnerium", "Mt", 109, 0, 0};
  static const atom_element darmstadtium{"Darmstadtium", "Ds", 110, 0, 0};
  static const atom_element roentgenium{"Roentgenium", "Rg", 111, 0, 0};
  static const atom_element copernicium{"Copernicium", "Cn", 112, 0, 0};
  static const atom_element ununtrium{"Ununtrium", "Uut", 113, 0, 0};
  static const atom_element ununquadium{"Ununquadium", "Uuq", 114, 0, 0};
  static const atom_element ununpentium{"Ununpentium", "Uup", 115, 0, 0};
  static const atom_element ununhexium{"Ununhexium", "Uuh", 116, 0, 0};
  static const atom_element ununseptium{"Ununseptium", "Uus", 117, 0, 0};
  static const atom_element ununoctium{"Ununoctium", "Uuo", 118, 0, 0};

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

auto atom::name() const noexcept -> std::string
{
  return name_;
}

auto atom::position() const noexcept -> position_type
{
  return position_;
}

auto atom::serial() const noexcept -> unsigned int
{
  return serial_;
}

auto atom::position(float x, float y, float z) noexcept -> const position_type&
{
  return position_ = {x, y, z};
}

atom::atom_element::atom_element(std::string name,
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
