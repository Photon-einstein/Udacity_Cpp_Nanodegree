#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <map>

#include "Scheduler.h"
#include "Elevator.h"
#include "Floor.h"
#include "CapstoneParser.h"

enum CommandFirstName {out=0, add_elevator, status, call_elevator, enter_elevator, exit_elevator, continue_, not_a_valid_command};

int main() {
  std::string command{};
  int commandId;
  double firstNumber, secondNumber;
  bool b{true};
  std::vector <double> otherValues;
  std::ofstream outFile;
  /* output file initialization */
  outFile.open("output.txt", std::ios::out | std::ios::trunc);
  if (!outFile.is_open()) {
    std::cout<<"File \"output.txt\" failed to be open."<<std::endl;
    outFile<<"File \"output.txt\" failed to be open."<<std::endl;
    return 0;
  } else {
    std::cout<<"File \"output.txt\" opened sucessfully."<<std::endl;
    outFile<<"File \"output.txt\" opened sucessfully."<<std::endl;
  }
  Scheduler s(outFile);
  CapstoneParser::addFloorData(s);
  for (std::size_t i = 0; i < s._floors.size(); ++i) {
    /* map population */
    s._converterIdFloor[s._floors[i]->getFloorNumber()] = s._floors[i];
  }
  CapstoneParser::printFloorDataToFile(s._floors, outFile);
  /* enter simulation */
  while (b) {
    CapstoneParser::printFloorDataToStandartOutput(s._floors);
    CapstoneParser::printCommands();
    CapstoneParser::getAndParseCommand(outFile, otherValues, command, commandId);
    if (commandId == CommandFirstName::not_a_valid_command) {
      continue;
    }
    /* valid commands processing */
    switch (commandId) {
      case CommandFirstName::out:
        b  = false;
        break;
      case CommandFirstName::add_elevator:
        /* elevator still don´t exists */
        s.addElevatorCommand(otherValues);
        break;
      case CommandFirstName::status:
        s.statusElevatorCommand(otherValues);
        break;
      case CommandFirstName::call_elevator:
        s.callElevatorCommand(otherValues);
        break;
      case CommandFirstName::continue_:
        s.continueCommand(otherValues);
        break;
      case CommandFirstName::enter_elevator:
        s.enterElevatorCommand(otherValues);
        break;
      case CommandFirstName::exit_elevator:
        s.exitElevatorCommand(otherValues);
        break;
      default:
        break;
    }
    /* erase data, to prepare to another round */
    otherValues.clear();
    command.clear();
  }
  /* close file */
  std::cout<<"\t#### Closing file \"output.txt\""<<std::endl;
  outFile<<"Closing file \"output.txt\""<<std::endl;
  outFile.close();
  return 0;
}
/******************************************************************************/
