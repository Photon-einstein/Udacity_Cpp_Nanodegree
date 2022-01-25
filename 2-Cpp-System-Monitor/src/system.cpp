#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

/* constructor */
System::System () {
  this->operatingSystem_ = LinuxParser::OperatingSystem();
  this->kernel_ = LinuxParser::Kernel();
  return;
}

// TODO: Return the system's CPU
Processor& System::Cpu() {
  return this->cpu_;
}

// TODO: Return a container composed of the system's processes TODO
vector<Process>& System::Processes() {
  set<int>setPids{};
  vector<int> vPids{};
  /* population of setPids from the processes already in the vector of processes */
  for (Process& p : this->processes_) {
    setPids.insert(p.Pid());
  }
  /* population of the vector vPids from the LinuxParser::Pids function */
  vPids = LinuxParser::Pids();
  for (int& pid:  vPids) {
    /* check if the pid is not in the vector this->processes_ */
    if (setPids.find(pid) == setPids.end()) {
        /* not present, must update the vector */
        this->processes_.emplace_back(Process(pid));
    }
  }
  /* recalculation of cpu utilization, upTime and ram */
  for (Process& p:this->processes_) {
    p.CpuUtilization();
    p.UpTime();
    p.Ram();
  }
  /* sort of the vector in descending order of ram utilization */
  std::sort(this->processes_.begin(), this->processes_.end(), std::greater<Process>());
  return this->processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
  return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
  return LinuxParser::OperatingSystem();
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {
  return LinuxParser::UpTime();
}
