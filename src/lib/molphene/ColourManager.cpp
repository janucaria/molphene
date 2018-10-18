#include "ColourManager.hpp"

namespace molphene {
ColourManager::ColourManager()
: element_colors_({
   {"H", Rgba8 {0xFFFFFF}},  {"He", Rgba8 {0xFFC0CB}}, {"Li", Rgba8 {0xB22222}},
   {"Be", Rgba8 {0xFF1493}}, {"B", Rgba8 {0x00FF00}},  {"C", Rgba8 {0xC8C8C8}},
   {"N", Rgba8 {0x8F8FFF}},  {"O", Rgba8 {0xF00000}},  {"F", Rgba8 {0xDAA520}},
   {"Ne", Rgba8 {0xFF1493}}, {"Na", Rgba8 {0x0000FF}}, {"Mg", Rgba8 {0x228B22}},
   {"Al", Rgba8 {0x808090}}, {"Si", Rgba8 {0xDAA520}}, {"P", Rgba8 {0xFFA500}},
   {"S", Rgba8 {0xFFC832}},  {"Cl", Rgba8 {0x00FF00}}, {"Ar", Rgba8 {0xFF1493}},
   {"K", Rgba8 {0xFF1493}},  {"Ca", Rgba8 {0x808090}}, {"Sc", Rgba8 {0xFF1493}},
   {"Ti", Rgba8 {0x808090}}, {"V", Rgba8 {0xFF1493}},  {"Cr", Rgba8 {0x808090}},
   {"Mn", Rgba8 {0x808090}}, {"Fe", Rgba8 {0xFFA500}}, {"Co", Rgba8 {0xFF1493}},
   {"Ni", Rgba8 {0xA52A2A}}, {"Cu", Rgba8 {0xA52A2A}}, {"Zn", Rgba8 {0xA52A2A}},
   {"Ga", Rgba8 {0xFF1493}}, {"Ge", Rgba8 {0xFF1493}}, {"As", Rgba8 {0xFF1493}},
   {"Se", Rgba8 {0xFF1493}}, {"Br", Rgba8 {0xA52A2A}}, {"Kr", Rgba8 {0xFF1493}},
   {"Rb", Rgba8 {0xFF1493}}, {"Sr", Rgba8 {0xFF1493}}, {"Y", Rgba8 {0xFF1493}},
   {"Zr", Rgba8 {0xFF1493}}, {"Nb", Rgba8 {0xFF1493}}, {"Mo", Rgba8 {0xFF1493}},
   {"Tc", Rgba8 {0xFF1493}}, {"Ru", Rgba8 {0xFF1493}}, {"Rh", Rgba8 {0xFF1493}},
   {"Pd", Rgba8 {0xFF1493}}, {"Ag", Rgba8 {0x808090}}, {"Cd", Rgba8 {0xFF1493}},
   {"In", Rgba8 {0xFF1493}}, {"Sn", Rgba8 {0xFF1493}}, {"Sb", Rgba8 {0xFF1493}},
   {"Te", Rgba8 {0xFF1493}}, {"I", Rgba8 {0xA020F0}},  {"Xe", Rgba8 {0xFF1493}},
   {"Cs", Rgba8 {0xFF1493}}, {"Ba", Rgba8 {0xFFA500}}, {"La", Rgba8 {0xFF1493}},
   {"Ce", Rgba8 {0xFF1493}}, {"Pr", Rgba8 {0xFF1493}}, {"Nd", Rgba8 {0xFF1493}},
   {"Pm", Rgba8 {0xFF1493}}, {"Sm", Rgba8 {0xFF1493}}, {"Eu", Rgba8 {0xFF1493}},
   {"Gd", Rgba8 {0xFF1493}}, {"Tb", Rgba8 {0xFF1493}}, {"Dy", Rgba8 {0xFF1493}},
   {"Ho", Rgba8 {0xFF1493}}, {"Er", Rgba8 {0xFF1493}}, {"Tm", Rgba8 {0xFF1493}},
   {"Yb", Rgba8 {0xFF1493}}, {"Lu", Rgba8 {0xFF1493}}, {"Hf", Rgba8 {0xFF1493}},
   {"Ta", Rgba8 {0xFF1493}}, {"W", Rgba8 {0xFF1493}},  {"Re", Rgba8 {0xFF1493}},
   {"Os", Rgba8 {0xFF1493}}, {"Ir", Rgba8 {0xFF1493}}, {"Pt", Rgba8 {0xFF1493}},
   {"Au", Rgba8 {0xDAA520}}, {"Hg", Rgba8 {0xFF1493}}, {"Tl", Rgba8 {0xFF1493}},
   {"Pb", Rgba8 {0xFF1493}}, {"Bi", Rgba8 {0xFF1493}}, {"Po", Rgba8 {0xFF1493}},
   {"At", Rgba8 {0xFF1493}}, {"Rn", Rgba8 {0xFF1493}}, {"Fr", Rgba8 {0xFF1493}},
   {"Ra", Rgba8 {0xFF1493}}, {"Ac", Rgba8 {0xFF1493}}, {"Th", Rgba8 {0xFF1493}},
   {"Pa", Rgba8 {0xFF1493}}, {"U", Rgba8 {0xFF1493}},  {"Np", Rgba8 {0xFF1493}},
   {"Pu", Rgba8 {0xFF1493}}, {"Am", Rgba8 {0xFF1493}}, {"Cm", Rgba8 {0xFF1493}},
   {"Bk", Rgba8 {0xFF1493}}, {"Cf", Rgba8 {0xFF1493}}, {"Es", Rgba8 {0xFF1493}},
   {"Fm", Rgba8 {0xFF1493}}, {"Md", Rgba8 {0xFF1493}}, {"No", Rgba8 {0xFF1493}},
   {"Lr", Rgba8 {0xFF1493}}, {"Rf", Rgba8 {0xFF1493}}, {"Db", Rgba8 {0xFF1493}},
   {"Sg", Rgba8 {0xFF1493}}, {"Bh", Rgba8 {0xFF1493}}, {"Hs", Rgba8 {0xFF1493}},
   {"Mt", Rgba8 {0xFF1493}},
  })
{
}

Rgba8
ColourManager::get_element_color(const std::string& esymbol) const noexcept
{
  return element_colors_.at(esymbol);
}
} // namespace molphene
