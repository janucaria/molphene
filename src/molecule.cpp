#include "molecule.h"

namespace molphene {
molecule::molecule()
{
}

model&
molecule::addModel()
{
  models.emplace_back(*this);
  return models.at(models.size() - 1);
}

molecule::model_iterator
molecule::mdlbegin()
{
  return models.begin();
}

molecule::model_iterator
molecule::mdlend()
{
  return models.end();
}
} // namespace molphene
