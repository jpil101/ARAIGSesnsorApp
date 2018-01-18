#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include "Profile.h"
#include "ARAIG_Sensors.h"
#include "Task.h"
#include "Exoskeleton.h"
#include "Stims.h"
#include "Stimulation.h"

int main(int argc, char** argv) {
   if (argc != 5) {
     std::cerr << argv[0] << ": incorrect number of arguments\n";
     std::cerr << "Usage: " << argv[0] << " Profile_config Stim_config Task_config Output_file\n";
     return 1;
   }
   try{
     //Main Menu Start
     system("clear");
     AECS::usint exit;
     char input;
     exit=0;
     std::ofstream ostr(argv[4],std::ofstream::out);
     AECS::ARAIG_Sensors ARAIG(argv[2],argv[3]);
     AECS::Profile PROFILE(argv[1],ostr,ARAIG);
     while(exit==0){
       std::cout<<std::endl;
       std::cout<<"--------------------ARAIG--------------------"<<std::endl;
       std::cout<<"|                 MAIN MENU                 |"<<std::endl;
       std::cout<<"---------------------------------------------"<<std::endl;
       std::cout<<"| 1 - Display Flight Plan                   |"<<std::endl;
       std::cout<<"| 2 - Display Completed Tasks               |"<<std::endl;
       std::cout<<"| 3 - Display Next Task in Plan             |"<<std::endl;
       std::cout<<"| 4 - Display Last Task Run                 |"<<std::endl;
       std::cout<<"| 5 - Run Flight Plan                       |"<<std::endl;
       std::cout<<"| 6 - Reload Flight Plan                    |"<<std::endl;
       std::cout<<"| 7 - Adjust Flight Plan                    |"<<std::endl;
       std::cout<<"| 8 - Write Flight Plan to File             |"<<std::endl;
       std::cout<<"| 0 - Exit                                  |"<<std::endl;
       std::cout<<"---------------------------------------------"<<std::endl;
       std::cout<<">";
       std::cin>>input;
       //Checks to see if input is between ASCII 48 to 56 (0-8) for Validating and Selecting a Main Menu Option
       if(!std::cin.fail() && (int)input>=48 && (int)input<=56){
         std::cin.ignore(50,'\n');
         switch (atoi(&input)) {
           //Exit
           case 0:
            exit=1;
            break;
            //Display Flight Plan Option
           case 1:
            system("clear");
            PROFILE.displayToRun(std::cout);
            std::cout << "\nPress any key to continue ... ";
            std::cin.get();
            system("clear");
            break;
            //Display Completed Tasks Option
           case 2:
            system("clear");
            PROFILE.displayCompleted(std::cout);
            std::cout << "\nPress any key to continue ... ";
            std::cin.get();
            system("clear");
            break;
            //Display Next Task Option
           case 3:
            system("clear");
            PROFILE.displayNext(std::cout);
            std::cout << "\nPress any key to continue ... ";
            std::cin.get();
            system("clear");
            break;
            //Display Last Task Run Option
           case 4:
            system("clear");
            PROFILE.displayLast(std::cout);
            std::cout << "\nPress any key to continue ... ";
            std::cin.get();
            system("clear");
            break;
            //Run Flight Plan Option
           case 5:
            system("clear");
            try{PROFILE.run();} catch(const char* err) {std::cout<<std::endl<<err<<std::endl;}
            std::cout <<std::endl<< "\nPress any key to continue ... ";
            std::cin.get();
            system("clear");
            break;
            //Reload the Flight Plan Option
           case 6:
            system("clear");
            try{PROFILE.reloadPlan();} catch(const char* err) {std::cout<<std::endl<<err<<std::endl;}
            std::cout <<std::endl<< "\nPress any key to continue ... ";
            std::cin.get();
            system("clear");
            break;
            //Edit Flight Plan Option
           case 7:
            std::cout<<"This function is still in the Beta stage"<<std::endl;
            std::cout << "\nPress any key to continue ... ";
            std::cin.get();
            system("clear");
            break;
           case 8:
           //Write Flight Plan to File Option
            try{PROFILE.outputInfo(ostr);
            std::cout<<std::endl<<"The Completed Flight Plan has been Written to "<<argv[4]<<"!"<<std::endl;
            }  catch(const char * err){std::cout<<std::endl<<err<<std::endl;}
            std::cout << "\nPress any key to continue ... ";
            std::cin.get();
            system("clear");
            break;
         }
       }else{
         std::cout<<std::endl<<"Error: Incorrect Menu Item Selected!"<<std::endl;
         std::cin.get();
         std::cout << "\nPress any key to continue ... ";
         std::cin.get();
         system("clear");
         exit=0;
       }
     }
     ostr.close();
   }catch(const char* err) {std::cout<<err<<std::endl;}
   std::cout << "\nPress any key to continue ... ";
   std::cin.get();
   system("clear");
   return 0;
   }
