#include "Stims.h"


namespace AECS{
  //Constructor for a Stims which takes in arguments for a Stim stimulation. Validation occurs before implementation. Error's tossed out otherwise.
  Stims::Stims(const std::string& type_,const std::string& name_,const localStim location_,const usint intensity_,const usint freq_, const usint duration_) : Stimulation(type_) {
    if(!type_.empty() && (type_=="stim" || type_=="Stim")){
      if(!name_.empty() && location_>=0 && intensity_>=0 && intensity_<=100 && freq_>=0 && duration_>=0){
        StimName_=name_;
        StimLocation_=location_;
        StimIntensity_=intensity_;
        StimFreq_=freq_;
        StimDuration_=duration_;
      } else  throw "Error Code 2.1: Stim not created! Ensure input file has a proper name, location of stim(abs,front,back,traps),an intensity between 0%-100%, and a frequency and duration greater then 0!";
    } else  throw "Error Code 1.1: Stim not created! Stimulation type must be stim or exoskeleton!";
  }
  
//Display function for the Stims object
  void Stims::display(std::ostream& ostr) const{
    ostr<<StimName_<<std::endl;
    ostr<<"\tType = "<<getSimType()<<std::endl;

    switch(StimLocation_){
      case abs:
        ostr<<"\tLocation = abs"<<std::endl;
        break;
      case front:
        ostr<<"\tLocation = front"<<std::endl;
        break;
      case back:
        ostr<<"\tLocation = back"<<std::endl;
        break;
      case traps:
        ostr<<"\tLocation = traps"<<std::endl;
        break;
    }
    ostr<<"\tIntensity = "<<StimIntensity_<<std::endl;
    ostr<<"\tFrequency = "<<StimFreq_<<std::endl;
    ostr<<"\tDuration = "<<StimDuration_<<std::endl;
  }

  //Get function for the name of the Stim Stimulation.
  std::string Stims::getName()const  {return StimName_;}
}
