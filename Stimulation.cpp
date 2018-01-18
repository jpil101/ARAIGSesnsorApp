#include "Stimulation.h"

namespace AECS{
  //Constructor
  Stimulation::Stimulation(const std::string& type) : Stimtype_(type) {}
  //Get function which returns the Name of the type of Stimulation (Stim or Exo)
  std::string Stimulation::getSimType()const    {return Stimtype_;}
}
