#include "Task.h"

namespace AECS{
  //Constructor
  Task::Task()  {TaskName_.clear();TaskList_.clear();}

  //Copy Constructor
  Task::Task(const Task& _src_)  {TaskName_=_src_.TaskName_;TaskList_=std::list<Stimulation*>(_src_.TaskList_);}

  //Move Constructor
  Task::Task(Task&& _src_){
      TaskName_=_src_.TaskName_;
      TaskList_=std::list<Stimulation*>(_src_.TaskList_);
      _src_.TaskName_.clear();
      _src_.TaskList_.clear();
  }

  //Overloaded = Copy operator
  Task& Task::operator=(const Task& _src_){
    if(this!=&_src_){
      TaskName_=_src_.TaskName_;
      TaskList_=std::list<Stimulation*>(_src_.TaskList_);
    }
    else{
      TaskName_.clear();
      TaskList_.clear();
      throw "This task is the same as the task selected for copying";
    }
    return *this;
  }

  //Overloaded = Move operator
  Task&& Task::operator=(Task&& _src_){
    if(this!=&_src_){
      TaskName_=_src_.TaskName_;
      TaskList_=std::list<Stimulation*>(_src_.TaskList_);
      _src_.TaskName_.clear();
      _src_.TaskList_.clear();
    }
    else{
      TaskName_.clear();
      TaskList_.clear();
      throw "This task is the same as the task selected for moving";
    }
    return std::move(*this);
  }

  //Overloaded += Operator to add Stimulations to Tasks
  Task& Task::operator+=(Stimulation* _stim_)  {TaskList_.push_back(_stim_);return *this;}

  //Destructor
  Task::~Task(){
    for(size_t i=0;i<TaskList_.size();i++)  {TaskList_.front() = nullptr;TaskList_.pop_front();}
  }

  //Overloaded [] operator to retrieve a Stimulation based on a iterator
  Stimulation* Task::operator[](usint num_){
    if(TaskList_.size()>num_){
      std::list<Stimulation*>::iterator _iterator_=TaskList_.begin();
      std::advance(_iterator_,num_);
      return *_iterator_;
    }
    else  throw "That stimulation is not within the task of stimulations!";
  }

//Function to remove a stim from the list of Stimulations
  void Task::removeStim(const std::string _stimName_){
    for(std::list<Stimulation*>::iterator _iterator_=TaskList_.begin();_iterator_!=TaskList_.end();_iterator_++){
      if((*_iterator_)->getName()==_stimName_)  {TaskList_.erase(_iterator_);_iterator_=TaskList_.end();}
    }
  }

//Function that dumps the Stimulations Names
  void Task::dumpConfig(std::ostream& ostr)const{
    ostr<<std::endl<<"Task - "<<TaskName_<<std::endl;
    for(std::list<Stimulation*>::const_iterator _iterator_=TaskList_.begin();_iterator_!=TaskList_.end();_iterator_++) {ostr<<std::setw(4)<<(*_iterator_)->getName()<<std::endl;}
  }

//Function that would be used to execute the flight plan by displaying the Stims within the specific task object
  void Task::execStim(std::ostream& ostr)const {
    ostr<<std::endl<<"TASK: "<<TaskName_<<std::endl;
    for(std::list<Stimulation*>::const_iterator _iterator_=TaskList_.begin();_iterator_!=TaskList_.end();_iterator_++)  {(*_iterator_)->display(ostr);}
  }

//Getter function for the Task Name
  const std::string Task::getTaskName() {return TaskName_;}

//Setter Function for the Task Name
  void Task::setTaskName(const std::string& name_)  {TaskName_=name_;}
}
