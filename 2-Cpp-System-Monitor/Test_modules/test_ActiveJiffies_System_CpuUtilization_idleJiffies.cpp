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

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_,
  kLast_
};

long ActiveJiffies();
std::vector<long int> CpuUtilization();
long IdleJiffies();

// TODO: Read and return the number of active jiffies for the system
long ActiveJiffies() {
  long activeJiffies{};
  std::vector<long>cpuJiffiesUtilization = CpuUtilization();
  std::size_t i;
  /* store numeric data in vector */
  for (i = CPUStates::kUser_; i != CPUStates::kLast_; ++i) {
    if (i != CPUStates::kIdle_ && i != CPUStates::kIOwait_ && i != CPUStates::kSteal_) {
        activeJiffies+=cpuJiffiesUtilization.at(i);
    }
  }
  /* return the number of active jiffies in the system */
  return activeJiffies;
}

// TODO: Read and return the number of idle jiffies for the system
long IdleJiffies() {
  long idleJiffies{};
  std::vector<long>cpuJiffies = CpuUtilization();
  std::cout<<"Idle read: "<<cpuJiffies.at(CPUStates::kIdle_)<<" "<<cpuJiffies.at(kIOwait_)<<" "<<cpuJiffies.at(kSteal_)<<std::endl;
  return cpuJiffies.at(CPUStates::kIdle_)+cpuJiffies.at(kIOwait_)+cpuJiffies.at(kSteal_);
}

// TODO: Read and return CPU utilization
std::vector<long int> CpuUtilization() {
  std::vector<long int>cpu{};
  std::string test, line;
  std::ifstream stream(kProcDirectory+kStatFilename);
  std::size_t i;
  long int jiffiesCpu;
  /* read of /pid/stat */
  if (stream.is_open()) {
    stream>>test;
    if (test != "cpu") {
      /* no valid entry detected, return without summing the rest of the values */
      return cpu;
    }
    std::cout<<"Read: "<<test<<" ";
    /* store numeric data in vector */
    for (i = CPUStates::kUser_; i != CPUStates::kLast_; ++i) {
      stream>>jiffiesCpu;
      std::cout<<jiffiesCpu<<" ";
      cpu.emplace_back(jiffiesCpu);
    }
    std::cout<<std::endl;
  }
  /* return vector cpu filled */
  return cpu;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function TODO
long ActiveJiffies(int pid) {
  std::string aux{};
  std::size_t i;
  long int activeJiffiesVal{};
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);
  if (stream.is_open()) {
    for (i = 0; i < 13; ++i) {
      stream >> aux;
    }
    /* read data, sum #14 utime, #15 stime, #16 cutime, #17 cstime */
    std::cout<<"(";
    for (i = 0; i < 4; ++i) {
      stream >> aux;
      std::cout<<std::atol(aux.c_str())<<" ";
      activeJiffiesVal+=std::atol(aux.c_str());
    }
    std::cout<<") = ";
  }
  /* return final value after calculations */
  return activeJiffiesVal;
}

int main () {
  long int actJiff = ActiveJiffies(), idleJiff = IdleJiffies();
  std::cout<<"Active Jiffies (Hz) = "<<actJiff<<" Ticks/s."<<std::endl;
  std::cout<<"Idle Jiffies (Hz) = "<<idleJiff<<" Ticks/s."<<std::endl;
  std::cout<<"Active Jiffies (Hz) pid 1 = "<<ActiveJiffies(1)<<std::endl;
  return 0;
}
