#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

/* constructor */
Process::Process (const int pid): pid_(pid) {
  this->command_ = LinuxParser::Command(this->pid_);
  this->user_ = LinuxParser::User(this->pid_);
  return;
}

// TODO: Return this process's ID
int Process::Pid() {
  return this->pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  this->cpuUtilization_ = (LinuxParser::ActiveJiffies(this->pid_)/static_cast<float>(LinuxParser::Jiffies())) / (LinuxParser::UpTime()-LinuxParser::UpTime(this->pid_));
  return this->cpuUtilization_;
}

// TODO: Return the command that generated this process
string Process::Command() {
  return this->command_;
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  this->ram_ = LinuxParser::Ram(this->pid_);
  return this->ram_;
}

// TODO: Return the user (name) that generated this process
string Process::User() {
  return this->user_;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
  this->upTime_ = LinuxParser::UpTime()-LinuxParser::UpTime(this->pid_);
  return this->upTime_;
}

// TODO: Overload the "great than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator>(Process const& a) const {
  return atol(this->ram_.c_str()) > atol(a.ram_.c_str());
}
