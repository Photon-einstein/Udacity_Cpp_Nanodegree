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
const std::string kUptimeFilename{"/uptime"};

// TODO: Read and return the system uptime
long UpTime() {
  long int systemUpTime=0;
  std::string line, systemUpTimeS;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  /* read of memtotal */
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> systemUpTimeS;
    systemUpTime = atol(systemUpTimeS.c_str());
  }
  /* return final value in seconds */
  return systemUpTime;
}

int main () {
  std::cout<<"System uptime is = "<<UpTime()<<" s."<<std::endl;
  return 0;
}
