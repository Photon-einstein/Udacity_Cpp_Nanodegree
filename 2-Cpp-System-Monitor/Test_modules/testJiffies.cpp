#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <regex>

// TODO: Read and return the number of jiffies for the system
long Jiffies() {
  return sysconf(_SC_CLK_TCK);
}

int main () {
  std::cout<<"System HZ is = "<<Jiffies()<<"Ticks/s."<<std::endl;
  return 0;
}
