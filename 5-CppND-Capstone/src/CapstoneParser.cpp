#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "CapstoneParser.h"

enum CommandFirstName {out=0, add_elevator, status, call_elevator, enter_elevator, exit_elevator, continue_, not_a_valid_command};
static const char *commandFirstName_str[] = {"out", "add_elevator", "status", "call_elevator", "enter_elevator", "exit_elevator", "continue", "not_a_valid_command"};

void CapstoneParser::addFloorData(Scheduler &s) {
  /* floors hardcoded */
  s._floors.emplace_back(std::make_shared<Floor>(-2, "Garage-Lower level"));
  s._floors.emplace_back(std::make_shared<Floor>(-1, "Garage-Upper level"));
  s._floors.emplace_back(std::make_shared<Floor>(0, "Restauration"));
  s._floors.emplace_back(std::make_shared<Floor>(1, "Commerce-Lower level"));
  s._floors.emplace_back(std::make_shared<Floor>(2, "Commerce-Upper level"));
  s._floors.emplace_back(std::make_shared<Floor>(3, "Office-Lower level"));
  s._floors.emplace_back(std::make_shared<Floor>(4, "Office-Mid level"));
  s._floors.emplace_back(std::make_shared<Floor>(5, "Office-Upper level"));
  return;
}
/******************************************************************************/
void CapstoneParser::printFloorDataToFile(const std::vector<std::shared_ptr<Floor>> floors, std::ofstream &outFile) {
  /* this function make the print of the floor data to the file outFile, and then it just returns */
  /* print floors data */
  outFile<<"\nElevator number\t\tElevator type\n"<<std::endl;
  for (std::size_t i = 0; i < floors.size(); ++i) {
    outFile<<floors[i]->getFloorNumber()<<"\t\t\t"<<floors[i]->getFloorType()<<std::endl;
  }
  outFile<<"\n";
  return;
}
/******************************************************************************/
void CapstoneParser::printFloorDataToStandartOutput(const std::vector<std::shared_ptr<Floor>> floors) {
  /* this function make the print of the floor data to the file outFile, and then it just returns */
  /* print floors data */
  std::cout<<"\nElevator number\t\tElevator type"<<std::endl;
  for (std::size_t i = 0; i < floors.size(); ++i) {
    std::cout<<floors[i]->getFloorNumber()<<"\t\t\t"<<floors[i]->getFloorType()<<std::endl;
  }
  return;
}
/******************************************************************************/
void CapstoneParser::printCommands() {
  std::cout<<"\nPlease enter a valid comand from the followings:"<<
  /* commandId = 0 */
  "\nout\t(to exit simulator)"<<
  /* commandId = 1*/
  "\nadd_elevator <elevator-id> <max-weight-supported-in-kgs>"<<
  /* commandId = 2 */
  "\nstatus <elevator-id>"<<
  /* commandId = 3 */
  "\ncall_elevator <elevator-id> <floor-id>"<<
  /* commandId = 4 */
  "\nenter_elevator <elevator-id> <total-weight-in-kgs-entering> <floor-number-requested>"<<
  /* commandId = 5 */
  "\nexit_elevator <elevator-id> <weight-exiting>"<<
  /* commandId = 6 */
  "\ncontinue <elevator-id>\n"<<std::endl;
  return;
}
/******************************************************************************/
/* this function makes the parsing of the command, namely it returns:
0 if 'out'
1 if 'add-elevator'
2 if 'status'
3 if 'call-elevator',
4 if 'enter-elevator'
5 if 'exit-elevator'
6 if 'continue'
7 if  not-a-valid command.

It fills the other values in the vector by reference.
*/
int CapstoneParser::commandParser(std::string command, std::vector<double> &otherValues) {
  std::istringstream linestream(command);
  std::string firstStringCommand="", test="";
  bool b;
  if (command.size() > 0) {
    linestream >> firstStringCommand;
  } else {
    return CommandFirstName::not_a_valid_command;
  }
  if (firstStringCommand == "out") {
      return CommandFirstName::out;
  } else {
    /* otherValues vector fulling and testing */
    if (linestream.rdbuf()->in_avail() > 0) {
      linestream >> test;
      if (!CapstoneParser::isNumber(test)){return CommandFirstName::not_a_valid_command;}
      otherValues.emplace_back(std::stod(test));
    } else {
      return CommandFirstName::not_a_valid_command;
    }
  }
  /* get second value */
  if (firstStringCommand != "status" && firstStringCommand != "continue") {
      /* get next value from the input string */
      if (linestream.rdbuf()->in_avail() > 0) {
        linestream >> test;
      } else {
        test="";
      }
    if (!CapstoneParser::isNumber(test)){return CommandFirstName::not_a_valid_command;}
    otherValues.emplace_back(std::stod(test));
  }
  /* get third value */
  if (firstStringCommand == "enter_elevator") {
      /* get next value from the input string */
      if (linestream.rdbuf()->in_avail() > 0) {
        linestream >> test;
      } else {
        test="";
      }
    if (!CapstoneParser::isNumber(test)){return CommandFirstName::not_a_valid_command;}
    otherValues.emplace_back(std::stod(test));
  }
  /* return final code */
  if (firstStringCommand == "add_elevator") {
    return CommandFirstName::add_elevator;
  } else if (firstStringCommand == "status") {
    return CommandFirstName::status;
  } else if (firstStringCommand == "call_elevator") {
    return CommandFirstName::call_elevator;
  } else if (firstStringCommand == "enter_elevator") {
    return CommandFirstName::enter_elevator;
  } else if (firstStringCommand == "exit_elevator") {
    return CommandFirstName::exit_elevator;
  } else if (firstStringCommand == "continue") {
    return CommandFirstName::continue_;
  } else {
    return CommandFirstName::not_a_valid_command;
  }
}
/******************************************************************************/
bool CapstoneParser::isNumber(const std::string& s) {
  /* this function returns true if the string s contains a valid double number or
  false otherwise */
  char* end = nullptr;
  double val = strtod(s.c_str(), &end);
  return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}
/******************************************************************************/
void CapstoneParser::getAndParseCommand(std::ofstream &outFile, std::vector<double> &otherValues, std::string &command, int &commandId) {
  /* this function gets and parses the command from the user, it returns by
  reference in the end the code command */
  getline(std::cin,command);
  /* parse the command to see what is the measure to take */
  commandId = CapstoneParser::commandParser(command, otherValues);
  if (commandId != CommandFirstName::not_a_valid_command) {
    std::cout<<"\t#### Command: \""<<commandFirstName_str[commandId];
    outFile<<"Command: \""<<commandFirstName_str[commandId];
    for (std::size_t i = 0; i < otherValues.size(); ++i) {
      if (i == 0 || commandId == CommandFirstName::call_elevator) {
        otherValues[i] = trunc(otherValues[i]);
      }
      std::cout<<" "<<otherValues[i];
      outFile<<" "<<otherValues[i];
    }
    std::cout<<"\""<<std::endl;
    outFile<<"\""<<std::endl;
  } else {
    std::cout<<"\t#### Command: \""<<command<<"\" is not a valid command"<<std::endl;
    outFile<<"Command: \""<<command<<"\" is not a valid command"<<std::endl;
    /* erase data, to prepare to another round */
    otherValues.clear();
    command.clear();
  }
  return;
}
/******************************************************************************/
