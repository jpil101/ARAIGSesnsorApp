#include "Stimulation.h"
#include "Exoskeleton.h"

namespace AECS{
  //Constructor for Exo which takes in arguments for an Exo Stim. Validation will occur before implementation. Error's tossed out otherwise.
  Exoskeleton::Exoskeleton(std::string& type_,std::string& name_,usint intensity_,usint duration_) : Stimulation(type_) {
    if(!type_.empty() && (type_=="exoskeleton" || type_=="Exoskeleton")){
      if(!name_.empty() && intensity_>=0 && intensity_<=100 && duration_>=0){
        ExoName_=name_;
        ExoIntensity_=intensity_;
        ExoDuration_=duration_;
      } else  throw "Error Code 2.2: Exoskeleton stim not created! Ensure input file has a proper name, an intensity between 0%-100%, and a duration greater then 0!";
    } else  throw "Error Code 1.2: Exoskeleton stim not created! Stimulation type must be Exoskeleton!";
  }
  
  //Display function for the Exo Stim
  void Exoskeleton::display(std::ostream& ostr) const{
    ostr<<ExoName_<<std::endl;
    ostr<<"\tType = "<<getSimType()<<std::endl;
    ostr<<"\tIntensity = "<<ExoIntensity_<<std::endl;
    ostr<<"\tDuration = "<<ExoDuration_<<std::endl;
  }
  //Get function for the name of the Exo Stim
  std::string Exoskeleton::getName() const  {return ExoName_;}
}
