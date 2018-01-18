#ifndef _EXOSKELETON_H_
#define _EXOSKELETON_H_

#include <string>
#include <iostream>
#include <iomanip>

#include "Stimulation.h"

namespace AECS{
  class Exoskeleton : public Stimulation{
    std::string ExoName_;
    usint ExoIntensity_;
    usint ExoDuration_;
  public:
    Exoskeleton(std::string&,std::string&,usint,usint);
    ~Exoskeleton(){}
    void display(std::ostream&) const;
    std::string getName() const;
    Exoskeleton* clone() const  {return new Exoskeleton(*this);}
  };
}

#endif
