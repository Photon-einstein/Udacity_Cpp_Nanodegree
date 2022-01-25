#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <regex>

const std::string kProcDirectory{"/proc/"};
const std::string kMeminfoFilename{"/meminfo"};

int main() {
  float memTotal=0, memFree=0;
  std::string line, dummyString, memTotalS, memFreeS;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  /* read of memtotal */
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> dummyString >> memTotalS;
    memTotal = atof(memTotalS.c_str());
    /* convertion to MB */
    memTotal/=1024;
  }
  /* read of memFree */
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> dummyString >> memFreeS;
    memFree = atof(memFreeS.c_str());
    /* convertion to MB */
    memFree/=1024;
  }
  std::cout<<"Mem utilization is: "<< memTotal<<"-"<<memFree<<"="<<memTotal-memFree<<" MB, "<<(memTotal-memFree)/memTotal<<"%."<<std::endl;
  return 0;
}
