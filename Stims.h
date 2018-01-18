#ifndef _STIMS_H_
#define _STIMS_H_

#include <iostream>
#include <iomanip>
#include <string>

#include "Stimulation.h"

namespace AECS{
  class Stims : public Stimulation{
    std::string StimName_;
    localStim StimLocation_;
    usint StimIntensity_;
    usint StimFreq_;
    usint StimDuration_;
  public:
    Stims(const std::string&,const std::string&,const localStim,const usint,const usint, const usint);
    ~Stims(){}
    void display(std::ostream&) const;
    std::string getName() const;
    Stims* clone() const  {return new Stims(*this);}
  };
}

#endif
