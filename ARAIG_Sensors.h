#ifndef _ARAIG_SENSORS_H_
#define _ARAIG_SENSORS_H_

#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "Task.h"

namespace AECS{
  class ARAIG_Sensors{
    Task* _Task_;
    Stimulation** _Stims_;
    std::string tmpin;
    size_t Stimcount_,_Taskcount,size,found;

  public:
    ARAIG_Sensors(const char*,const char*);
    //ARAIG_Sensors(const ARAIG_Sensors&);
    ~ARAIG_Sensors();
    void dump(std::ostream&)const;
    void getNext(std::vector<std::string>&);
    size_t _getTaskcount();
    Task& getTask(std::string&);
    //void delSet();
  };
}
#endif
