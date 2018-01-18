#ifndef _STIMULATION_H_
#define _STIMULATION_H_

#include <iostream>
#include <string>
#include <fstream>

namespace AECS{
  enum localStim{abs,front,back,traps};
  typedef unsigned short int usint;

  class Stimulation{
    std::string Stimtype_;
  protected:
    Stimulation(const std::string&);
    ~Stimulation(){}
  public:
    virtual void display(std::ostream&) const = 0;
    std::string getSimType() const;
    virtual std::string getName() const = 0;
  };
}

#endif
