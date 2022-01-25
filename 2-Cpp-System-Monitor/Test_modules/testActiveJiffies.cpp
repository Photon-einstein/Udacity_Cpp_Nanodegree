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
const std::string kStatFilename{"/stat"};

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long ActiveJiffies(int pid) {
  long int utime{}, stime, cutime{}, cstime{};
  std::string line, aux;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);
  int steps{14-1}, i;
  /* read of memtotal */
  if (stream.is_open()) {
    /* advance data until step1-1 */
    for (i = 0; i < steps; ++i) {
      stream>>aux;
    }
    /* read data from #14 until #17 */
    stream >> utime >> stime >> cutime >> cstime;
  }
  std::cout<<"utime = "<<utime<<", stime = "<<stime<<", cutime = "<<cutime<<", cstime = "<<cstime<<std::endl;
  /* final calculations */
  return utime+stime+cutime+cstime;
}


int main () {
  long int actJiff = ActiveJiffies(1);
  std::cout<<"Active Jiffies (Hz) = "<<actJiff<<" Ticks/s."<<std::endl;
  return 0;
}
