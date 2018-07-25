#include "ColourManager.h"

namespace molphene {
ColourManager::ColourManager()
: elementColors({{"H", colour(0xFFFFFF)},  {"He", colour(0xFFC0CB)},
                 {"Li", colour(0xB22222)}, {"Be", colour(0xFF1493)},
                 {"B", colour(0x00FF00)},  {"C", colour(0xC8C8C8)},
                 {"N", colour(0x8F8FFF)},  {"O", colour(0xF00000)},
                 {"F", colour(0xDAA520)},  {"Ne", colour(0xFF1493)},
                 {"Na", colour(0x0000FF)}, {"Mg", colour(0x228B22)},
                 {"Al", colour(0x808090)}, {"Si", colour(0xDAA520)},
                 {"P", colour(0xFFA500)},  {"S", colour(0xFFC832)},
                 {"Cl", colour(0x00FF00)}, {"Ar", colour(0xFF1493)},
                 {"K", colour(0xFF1493)},  {"Ca", colour(0x808090)},
                 {"Sc", colour(0xFF1493)}, {"Ti", colour(0x808090)},
                 {"V", colour(0xFF1493)},  {"Cr", colour(0x808090)},
                 {"Mn", colour(0x808090)}, {"Fe", colour(0xFFA500)},
                 {"Co", colour(0xFF1493)}, {"Ni", colour(0xA52A2A)},
                 {"Cu", colour(0xA52A2A)}, {"Zn", colour(0xA52A2A)},
                 {"Ga", colour(0xFF1493)}, {"Ge", colour(0xFF1493)},
                 {"As", colour(0xFF1493)}, {"Se", colour(0xFF1493)},
                 {"Br", colour(0xA52A2A)}, {"Kr", colour(0xFF1493)},
                 {"Rb", colour(0xFF1493)}, {"Sr", colour(0xFF1493)},
                 {"Y", colour(0xFF1493)},  {"Zr", colour(0xFF1493)},
                 {"Nb", colour(0xFF1493)}, {"Mo", colour(0xFF1493)},
                 {"Tc", colour(0xFF1493)}, {"Ru", colour(0xFF1493)},
                 {"Rh", colour(0xFF1493)}, {"Pd", colour(0xFF1493)},
                 {"Ag", colour(0x808090)}, {"Cd", colour(0xFF1493)},
                 {"In", colour(0xFF1493)}, {"Sn", colour(0xFF1493)},
                 {"Sb", colour(0xFF1493)}, {"Te", colour(0xFF1493)},
                 {"I", colour(0xA020F0)},  {"Xe", colour(0xFF1493)},
                 {"Cs", colour(0xFF1493)}, {"Ba", colour(0xFFA500)},
                 {"La", colour(0xFF1493)}, {"Ce", colour(0xFF1493)},
                 {"Pr", colour(0xFF1493)}, {"Nd", colour(0xFF1493)},
                 {"Pm", colour(0xFF1493)}, {"Sm", colour(0xFF1493)},
                 {"Eu", colour(0xFF1493)}, {"Gd", colour(0xFF1493)},
                 {"Tb", colour(0xFF1493)}, {"Dy", colour(0xFF1493)},
                 {"Ho", colour(0xFF1493)}, {"Er", colour(0xFF1493)},
                 {"Tm", colour(0xFF1493)}, {"Yb", colour(0xFF1493)},
                 {"Lu", colour(0xFF1493)}, {"Hf", colour(0xFF1493)},
                 {"Ta", colour(0xFF1493)}, {"W", colour(0xFF1493)},
                 {"Re", colour(0xFF1493)}, {"Os", colour(0xFF1493)},
                 {"Ir", colour(0xFF1493)}, {"Pt", colour(0xFF1493)},
                 {"Au", colour(0xDAA520)}, {"Hg", colour(0xFF1493)},
                 {"Tl", colour(0xFF1493)}, {"Pb", colour(0xFF1493)},
                 {"Bi", colour(0xFF1493)}, {"Po", colour(0xFF1493)},
                 {"At", colour(0xFF1493)}, {"Rn", colour(0xFF1493)},
                 {"Fr", colour(0xFF1493)}, {"Ra", colour(0xFF1493)},
                 {"Ac", colour(0xFF1493)}, {"Th", colour(0xFF1493)},
                 {"Pa", colour(0xFF1493)}, {"U", colour(0xFF1493)},
                 {"Np", colour(0xFF1493)}, {"Pu", colour(0xFF1493)},
                 {"Am", colour(0xFF1493)}, {"Cm", colour(0xFF1493)},
                 {"Bk", colour(0xFF1493)}, {"Cf", colour(0xFF1493)},
                 {"Es", colour(0xFF1493)}, {"Fm", colour(0xFF1493)},
                 {"Md", colour(0xFF1493)}, {"No", colour(0xFF1493)},
                 {"Lr", colour(0xFF1493)}, {"Rf", colour(0xFF1493)},
                 {"Db", colour(0xFF1493)}, {"Sg", colour(0xFF1493)},
                 {"Bh", colour(0xFF1493)}, {"Hs", colour(0xFF1493)},
                 {"Mt", colour(0xFF1493)}})
,

 altlocColors(
  {{0, colour(0xFFFFFF)},   {'A', colour(0xFFC0CB)}, {'B', colour(0xB22222)},
   {'C', colour(0xFF1493)}, {'D', colour(0x00FF00)}, {'E', colour(0xC8C8C8)},
   {'F', colour(0x8F8FFF)}, {'G', colour(0xF00000)}, {'H', colour(0xDAA520)},
   {'I', colour(0xFF1493)}, {'K', colour(0xA52A2A)}, {'L', colour(0xA52A2A)},
   {'M', colour(0xA52A2A)}, {'O', colour(0xFF1493)}, {'P', colour(0xFF1493)},
   {'Q', colour(0xFF1493)}, {'R', colour(0xFF1493)}, {'S', colour(0xA52A2A)},
   {'T', colour(0xFF1493)}, {'U', colour(0xFF1493)}, {'V', colour(0xFF1493)},
   {'W', colour(0xFF1493)}, {'X', colour(0xFF1493)}, {'Y', colour(0xFF1493)},
   {'Z', colour(0xFF1493)}})
{
}

const colour&
ColourManager::getElementColor(std::string elementSymbol)
{
  return elementColors.at(elementSymbol);
}

const colour&
ColourManager::getAltlocColor(char altloc)
{
  return altlocColors.at(altloc);
}
} // namespace molphene
