#ifndef _TASK_H_
#define _TASK_H_

#include <string>
#include <iostream>
#include <list>
#include <iterator>
#include "Stims.h"
#include "Exoskeleton.h"

namespace AECS{
  class Task{
    std::string TaskName_;
    std::list<Stimulation*> TaskList_;
  public:
    Task();
    Task(const Task&);
    Task(Task&&);
    Task(std::string& name_)  {TaskName_=name_.substr(0,name_.length()-1);TaskList_.clear();}
    Task& operator=(const Task&);
    Task&& operator=(Task&&);
    Task& operator+=(Stimulation*);
    ~Task();
    Stimulation* operator[](usint);
    void removeStim(const std::string);
    void dumpConfig(std::ostream&)const;
    void execStim(std::ostream&)const;
    const std::string getTaskName();
    void setTaskName(const std::string&);
  };
}


#endif
