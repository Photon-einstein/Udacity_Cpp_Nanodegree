#ifndef CAPSTONE_PARSER_H
#define CAPSTONE_PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "Floor.h"
#include "Scheduler.h"

namespace CapstoneParser {

  void addFloorData(Scheduler &s);

  /* this function make the print of the floor data to the file outFile, and then it just returns */
  void printFloorDataToFile(const std::vector<std::shared_ptr<Floor>> floors, std::ofstream &outFile);

  /* this function make the print of the floor data to the stantdart output and
  then it just returns */
  void printFloorDataToStandartOutput(const std::vector<std::shared_ptr<Floor>> floors);

  /* this function prints the commands to the standart output, and then it
  returns */
  void printCommands();

  /* this function makes the parsing of the command, namely it returns:
  0 if 'out'
  1 if 'add-elevator'
  2 if 'status'
  3 if 'call-elevator',
  4 if 'enter-elevator'
  5 if 'exit-elevator'
  6 if 'continue'
  7 if not a  valid command.

  It fills the other values in the vector by reference.
  */
  int commandParser(std::string command, std::vector<double> &otherValues);

  /* this function returns true if the string s contains a valid double number or
  false otherwise */
  bool isNumber(const std::string& s);

  /* this function gets and parses the command from the user, it returns by
  reference in the end the code command */
  void getAndParseCommand(std::ofstream &outFile, std::vector<double> &otherValues, std::string &command, int &commandId);
};

#endif
