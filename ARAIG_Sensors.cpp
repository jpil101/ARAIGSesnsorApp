#include "ARAIG_Sensors.h"

namespace AECS{
  ARAIG_Sensors::ARAIG_Sensors(const char* _Stim,const char* _Task) : Stimcount_(0),_Taskcount(0)
  {
    //Open stim configuration file
    std::ifstream fileStim(_Stim);

  if(fileStim){
    //Determine the amount of stims in file and set Stims object to that amount
    while(!fileStim.eof()){
      std::getline(fileStim,tmpin);
      Stimcount_++;
    }
    fileStim.clear();
    fileStim.seekg(0);
    Stimcount_--;
    _Stims_=new Stimulation*[Stimcount_];
    Stimcount_=0;

    //Determining if the stimulation is a stim or an exoskeleton stim
      while((std::getline(fileStim,tmpin))){
        if(tmpin[0]=='s' || tmpin[0]=='S'){
          enum sensorType{_type,_name,_location,_intensity,_freq,_duration};
          std::vector<std::string> data_;
          localStim Location_;
          //Calling parsing function
          size_t check=std::count(tmpin.begin(),tmpin.end(),',');
          for(size_t i=0;i<(check+1);i++)   getNext(data_);

          if(data_[_location]==std::string("abs"))  Location_=abs;
          else if(data_[_location]==std::string("front"))  Location_=front;
          else if(data_[_location]==std::string("back")) Location_=back;
          else if(data_[_location]==std::string("traps"))  Location_=traps;

          //Placing the stimulations within file into Stims object
          if(Location_>=0){
            Stims* tempstim_=new Stims(data_[_type],data_[_name],Location_,stoi(data_[_intensity]),stoi(data_[_freq]),stoi(data_[_duration]));
            _Stims_[Stimcount_++]=tempstim_->clone();
          }
          else  throw "Error code 5: Input file has not been created properly! The location must be abs,front,back or traps!";
        }
        else if(tmpin[0]=='e' || tmpin[0]=='E'){
          enum sensorType{_type,_name,_intensity,_duration};
          std::vector<std::string> data_;
          //Calling parsing function
          size_t check=std::count(tmpin.begin(),tmpin.end(),',');
          for(size_t i=0;i<(check+1);i++)   getNext(data_);

          //Placing the stimulations within the file into Exoskeleton object
          Exoskeleton* tempexo_=new Exoskeleton(data_[_type],data_[_name],stoi(data_[_intensity]),stoi(data_[_duration]));
          _Stims_[Stimcount_++]=tempexo_->clone();
        }
        else  throw "Error code 3: Input file has not been created properly! Stim or Exoskeleton not present in file!";
      }
      fileStim.close();
    }else throw "Error code 4: File has not been opened correctly!";

    //Opening task configuration file
    std::ifstream fileTask(_Task);
  if(fileTask){
    //Determining the amount of tasks within the file and setting the Task object to that amount
    while((std::getline(fileTask,tmpin))){
      if(tmpin.find("TASK")!=std::string::npos)  _Taskcount++;
    }
    _Task_=new Task[_Taskcount];
    fileTask.clear();
    fileTask.seekg(0);
    _Taskcount=0;

    //Creating new tasks based on the task name
      while((std::getline(fileTask,tmpin))){
        if(tmpin.find("TASK")!=std::string::npos){
          size=tmpin.length();
          found=tmpin.find(',');
          tmpin=tmpin.substr(found+1,size-1);
          _Task_[_Taskcount++]= Task(tmpin);
        }
        else{
          //Adding the specific stims in the task configuration file to the task object from the sims configuration file
          tmpin=tmpin.substr(0,(tmpin.length()-1));
          for(size_t i=0;i<Stimcount_;i++){
            if(_Stims_[i]->getName()==tmpin)  _Task_[_Taskcount-1]+=_Stims_[i];
            else if(i==Stimcount_)  throw "Error code 6: Stim in Task is not within list of Stimulations!";
          }
        }
      }
      fileTask.close();
    }else throw "Error code 4.2: File has not been opened correctly!";
  }
//
//Copy Constructor
  /*ARAIG_Sensors::ARAIG_Sensors(const ARAIG_Sensors& ARAIG) {
    Stimcount_=ARAIG.Stimcount_;
    _Taskcount=ARAIG._Taskcount;
    size=ARAIG.size;
    found=ARAIG.found;
    tmpin=ARAIG.tmpin;
    _Task_ = new Task[_Taskcount];
    _Stims_= new Stimulation*[Stimcount_];

    for(usint i=0;i<_Taskcount;i++){
      _Task_[i]=ARAIG._Task_[i];
    }
    for(usint i=0;i<Stimcount_;i++){
      _Stims_[i]=ARAIG._Stims_[i];
    }
  }*/

//Destructor
  ARAIG_Sensors::~ARAIG_Sensors(){
    delete []_Stims_;
    _Stims_=nullptr;
    delete [] _Task_;
    _Task_=nullptr;
  }

//Stims Display Dump Function
  void ARAIG_Sensors::dump(std::ostream& ostr)const{
    for(size_t i=0;i<Stimcount_;i++)  _Stims_[i]->display(ostr);
  }

  //Parsing function meant to be used with the stimulation configuration file
  void ARAIG_Sensors::getNext(std::vector<std::string>& data_){
    size=tmpin.length();
    found=tmpin.find(',');

    if(found){
      data_.push_back(tmpin.substr(0,found));
      tmpin=tmpin.substr(found+1,size);
    }
    else  data_.push_back(tmpin);
  }

  //Getter function for the count of tasks
  size_t ARAIG_Sensors::_getTaskcount() {return _Taskcount;}

  //Getter function for a specific task
  Task& ARAIG_Sensors::getTask(std::string& _name_){
    for(usint i=0;i<_Taskcount;i++){
      if(_Task_[i].getTaskName() == _name_){
        return _Task_[i];
        break;
      }else if(i==_Taskcount-1) std::cout<<std::endl<<_name_<<" is not in Task Config File!"<<std::endl;
    }throw "Error code 10: Task is NOT FOUND! Task is NOT loaded!";
  }
//
  /*void ARAIG_Sensors::delSet(){
    for(usint i=0;i<Stimcount_;i++){
      delete &_Stims_[i];
      _Stims_[i]=nullptr;
    }

    for(usint i=0;i<_Taskcount;i++) delete &_Task_[i];
  }*/

}
