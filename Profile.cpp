#include "Profile.h"
using namespace std;
namespace AECS{
  Profile::Profile(const char* profileName,std::ostream& os,ARAIG_Sensors& _ARAIG_) : ostr(os),ARAIG(&_ARAIG_){
    std::ifstream profileInfo(profileName);
//
  //  ARAIG = new ARAIG_Sensors(_ARAIG_);
//
    ARAIG->dump(std::cout);

    //Check if Profile Config file has Opened
    if(profileInfo){
      std::string tmpin;
      size_t size,found;

      //Getting the Student Information from Profile Config File
      std::getline(profileInfo,tmpin);
      size=tmpin.length();
      found=tmpin.find(',');
      StuFirstName=tmpin.substr(0,found);
      tmpin=tmpin.substr(found+1,size);
      size=tmpin.length();
      found=tmpin.find(',');
      StuLastName=tmpin.substr(0,found);
      tmpin=tmpin.substr(found+1,size);
      StuNum=tmpin.substr(0,tmpin.length()-1);

//Getting the Instructor Information from Profile Config File
      std::getline(profileInfo,tmpin);
      size=tmpin.length();
      found=tmpin.find(',');
      InstFirstName=tmpin.substr(0,found);
      tmpin=tmpin.substr(found+1,size);
      size=tmpin.length();
      found=tmpin.find(',');
      InstLastName=tmpin.substr(0,found);
      tmpin=tmpin.substr(found+1,size);
      InstNum=tmpin.substr(0,tmpin.length()-1);

//Setting the Calibration Information from Profile Config File
      std::getline(profileInfo,tmpin);
      found=tmpin.find(',');
      size=tmpin.length();
      Calibration.max=stoi(tmpin.substr(0,found));
      Calibration.min=stoi(tmpin.substr(found+1,size));

//Loading The Tasks within the Profile Config File into The Flight Plan
      while((std::getline(profileInfo,tmpin))){
        tmpin=tmpin.substr(0,(tmpin.length()-1));
          try{ToRun.push_back(_ARAIG_.getTask(tmpin));
          }catch(const char* err) {std::cout<<err<<std::endl;}
      }
    }
    profileInfo.close();
  }

//Destructor
  Profile::~Profile(){
    for(size_t i=0;i<ToRun.size();i++)  ToRun.erase(ToRun.begin());
    for(size_t i=0;i<Completed.size();i++)  Completed.erase(Completed.begin());
//
    //ARAIG.delSet();
    //delete ARAIG;
    //ARAIG=nullptr;
  }

//Display function that Display Flight Plan
  void Profile::displayToRun(std::ostream& ostr) const{
    ostr<<"+-------------------------+"<<std::endl;
    ostr<<"|       Flight Plan       |"<<std::endl;
    ostr<<"+-------------------------+"<<std::endl;
    if(!ToRun.empty()){
      for(size_t i=0;i<ToRun.size();i++)  ToRun[i].dumpConfig(ostr);
    }else ostr<<std::endl<<"The Flight Plan is Empty!"<<std::endl;
  }

//Display function that Displays the Completed Tasks
  void Profile::displayCompleted(std::ostream& ostr) const{
    ostr<<"+---------------------------+"<<std::endl;
    ostr<<"|      Completed Tasks      |"<<std::endl;
    ostr<<"+---------------------------+"<<std::endl;
    if(!Completed.empty()){
      for(size_t i=0;i<Completed.size();i++)  Completed[i].dumpConfig(ostr);
    }else ostr<<std::endl<<"There are no Completed Tasks! The Flight Plan is Full!"<<std::endl;
  }

//Display function that Displays the Next Task in The Flight Plan
  void Profile::displayNext(std::ostream& ostr) const{
    ostr<<"+----------------------------+"<<std::endl;
    ostr<<"|  Next Task in Flight Plan  |"<<std::endl;
    ostr<<"+----------------------------+"<<std::endl;
    if(!ToRun.empty()) ToRun[0].execStim(ostr);
    else  ostr<<std::endl<<"There are no more Tasks within the Flight Plan!"<<std::endl;
  }

//Display function that Displays the Last Task Run
  void Profile::displayLast(std::ostream& ostr) const{
    ostr<<"+-----------------------------+"<<std::endl;
    ostr<<"|        Last Task Run        |"<<std::endl;
    ostr<<"+-----------------------------+"<<std::endl;
    if(!Completed.empty()) Completed[0].execStim(ostr);
    else  ostr<<std::endl<<"There are currently no completed Tasks!"<<std::endl;
  }

//Run function which Executes the Flight Plan
  void Profile::run(){
    usint uin,exit1;
    char input;
    exit1=0;
    while(exit1==0){
      if(!ToRun.empty()){
        //Run Flight Plan Menu with Current Available Tasks in Flight Plan
        std::cout<<"--There are "<<ToRun.size()<<" Tasks available to Run within the Flight Plan--"<<std::endl<<std::endl;
        std::cout<<"+----------------------------+"<<std::endl;
        std::cout<<"|    Run Flight Plan Menu    |"<<std::endl;
        std::cout<<"+----------------------------+"<<std::endl;
        std::cout<<"| 1 - Run Flight Plan        |"<<std::endl;
        std::cout<<"| 2 - Exit                   |"<<std::endl;
        std::cout<<"+----------------------------+"<<std::endl;
        std::cout<<">";
        std::cin>>input;
        std::cout<<std::endl;
        if((int)input==49){
          //Request for User to Input the Ammount of Tasks to Execute from The Flight Plan
          std::cout<<"How many tasks within the flight plan should be executed at one time?"<<std::endl;
          std::cout<<">";
          std::cin>>uin;
          system("clear");
          //Flight Plan Executes based on User Input then Puts the Tasks within the Completed Tasks
          if(!std::cin.fail()){
            std::cin.ignore(50,'\n');
            //If User input is Less then the Remaining Tasks in The Flight Plan
            if(uin>0 && uin<=ToRun.size()){
              for(usint j=0;j<uin;j++){
                ToRun[0].execStim(std::cout);
                Completed.push_back(std::move(ToRun[0]));
                ToRun.erase(ToRun.begin());
                std::cout << "\nPress any key to continue ... "<<std::endl;
                std::cin.get();
                if(j==(uin-1))  system("clear");
              }
              //If User input is Greater then the Remaining Tasks in The Flight Plan, All the Remaining Tasks will Run
            }else if(uin>0 && uin>ToRun.size()){
              usint x=ToRun.size();
              for(usint i=0;i<x;i++){
                ToRun[0].execStim(std::cout);
                Completed.push_back(std::move(ToRun[0]));
                ToRun.erase(ToRun.begin());
                std::cout << "\nPress any key to continue ... "<<std::endl;
                std::cin.get();
              }
            }
            else  throw "Error code 8: Number inputted must be greater then 0!";
          }else  throw "Error code 7: Invalid input!";
          //Exiting the Run function
        }else if ((int)input==50){
          exit1=1;
        }
        //Validation for Menu input
        else if((int)input<49 || (int)input>50){
          std::cout<<"Error: Incorrect Menu Item Selected!"<<std::endl<<std::endl;
          std::cin.get();
          std::cout << "\nPress any key to continue ... ";
          std::cin.get();
          system("clear");
        }
      }else{
        system("clear");
        throw "The Flight Plan has been Successfully Executed! There are no remaining tasks within the flight plan!";
        exit1=1;
      }
    }
  }

//Function that is used to write to File
  void Profile::outputInfo(std::ostream& ostr)const{
    if(ToRun.empty()){
      ostr<<"Student:"<<std::setw(10)<<std::right<<StuFirstName<<' '<<StuLastName<<" - "<<StuNum<<std::endl;
      ostr<<"Instructor:  "<<std::setw(6)<<std::right<<InstFirstName<<' '<<InstLastName<<" - "<<InstNum<<std::endl;
      ostr<<"Student Calibration:"<<std::endl;
      ostr<<"MAX = "<<Calibration.max<<std::endl;
      ostr<<"MIN = "<<Calibration.min<<std::endl;
      for(usint i=0;i<Completed.size();i++)  Completed[i].execStim(ostr);
    }
    else throw "Error! Flight Plan must be Completely Executed before Writing to File! - There are still Tasks remaining within the Flight Plan!";
  }

//Reload the Flight Plan Function
  void Profile::reloadPlan(){
    usint uin,exit1;
    char input;
    exit1=0;
    if(ToRun.empty()){
      while(exit1==0){
        std::cout<<"+-----------+Reload Flight Plan+-----------+"<<std::endl;
        std::cout<<"|    How should the Flight Plan be Reloaded|"<<std::endl;
        std::cout<<"+---------------------------------------------+"<<std::endl;
        std::cout<<"| 1 - Reload Full Flight Plan                 |"<<std::endl;
        std::cout<<"| 2 - Reload Partial Flight Plan              |"<<std::endl;
        std::cout<<"| 3 - Exit                                    |"<<std::endl;
        std::cout<<"+---------------------------------------------+"<<std::endl;
        std::cout<<">";
        std::cin>>input;
        std::cout<<std::endl;
        if((int)input==49){
        system("clear");
        usint x=Completed.size();
          for(usint i=0;i<x;i++){
            ToRun.push_back(std::move(Completed[0]));
            Completed.erase(Completed.begin());
          }
        std::cout<<std::endl;
        std::cout<<std::endl<<"The Flight Plan has been Successfully Reloaded! Flight Plan Ready for Execution!"<<std::endl;
        }
        if((int)input==50){
          std::cout<<"Please enter the Start of what will be Reloaded"<<std::endl;
          std::cout<<">";
          std::cin>>uin;
          std::cout<<endl;
          if(uin==1){
            std::cout<<"Please enter the End position of what will be Reloaded"<<std::endl;
            std::cin>>uin;
            if(uin==1){
              ToRun.push_back(std::move(Completed[0]));
              for(int i=0;i<Completed.size();i++){
                PlanEnd.push_back(std::move(Completed[0]));
              }
            }
            else if(uin<=Completed.size() && uin>1){
              for(int i=1;i<(uin+1);i++){
                ToRun.push_back(std::move(Completed[0]));
              }
              for(int i=(uin+1);i<Completed.size();i++){
                PlanEnd.push_back(std::move(Completed[0]));
              }
            }
          }
          else
          if(uin<=Completed.size() && uin>0){
            uin=uin-1;
            for(int i=0;i<uin;i++){
              ToRun.push_back(std::move(Completed[0]));
              Completed.erase(Completed.begin());
            }
          }
        }
      }
    }else throw "Error! Flight Plan must be Completely Executed before Reloading Occurs! - There are still Tasks remaining within the Flight Plan!";
  }


//Edit the Flight Plan - Not Implemented in Main Menu

/*  void Profile::editPlan(){
    if(ToRun.empty()){
      char input;
      std::cout<<"+-----------+Edit Flight Plan Menu+-----------+"<<std::endl;
      std::cout<<"|  Change Tasks Within Completed Flight Plan  |"<<std::endl;
      std::cout<<"+---------------------------------------------+"<<std::endl;
      std::cout<<"| 1 -                                         |"<<std::endl;
      std::cout<<"| 2 - Exit                                    |"<<std::endl;
      std::cout<<"+---------------------------------------------+"<<std::endl;
    }else{
      std::cout<<"Error: There are still TASKS within the current Flight Plan! Finish running the Flight Plan First!"<<std::endl;
      std::cin.get();
      std::cout << "\nPress any key to continue ... ";
      std::cin.get();
      system("clear");
    }
  }



  bool addTask(){

  }

  bool delTask(){

  }

  bool swapTask(){

  }

  bool editTask(){

  }
  */
}
