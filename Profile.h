
#ifndef _PROFILE_H
#define _PROFILE_H

#include <vector>
#include <string>
#include <iostream>
#include "ARAIG_Sensors.h"


namespace AECS{
  class Profile{
    std::string StuLastName,StuFirstName,InstFirstName,InstLastName,StuNum,InstNum;
    std::ostream& ostr;
    ARAIG_Sensors *ARAIG;
    struct Calib{
      usint max;
      usint min;
    } Calibration;
    std::vector<Task> ToRun;
    std::vector<Task> Completed;
    std::vector<Task> PlanBegin;
    std::vector<Task> PlanEnd;

  public:
    Profile(const char*,std::ostream&,ARAIG_Sensors&);
    ~Profile();
    void displayToRun(std::ostream& ostr)const;
    void displayCompleted(std::ostream& ostr)const;
    void displayNext(std::ostream& ostr)const;
    void displayLast(std::ostream& ostr)const;
    void run();
    void outputInfo(std::ostream& ostr)const;
    void reloadPlan();
    /* Not implemented
    
    void editPlan();
    bool addTask();
    bool delTask();
    bool swapTask();
    bool editTask();
    */

  };
}

#endif
