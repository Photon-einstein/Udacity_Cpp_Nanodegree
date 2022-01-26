#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

template <typename T>
T getNumberOfOccurences(std::ifstream &stream, const std::string key) {
  T count{};
  std::string test, line;
  /* read of /pid/stat */
  if (stream.is_open()) {
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> test;
      if (test == key) {
        linestream >> count;
        return count;
      }
    }
  }
  /* if it reaches here then it was not found */
  return count;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(LinuxParser::kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        /* empty value case handling */
        if (value == "") {
          value = "Linux";
        }
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(LinuxParser::kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  long int memTotal, memFree;
  memTotal = getNumberOfOccurences<long int>(stream, "MemTotal:");
  memFree = getNumberOfOccurences<long int>(stream, "MemFree:");
  return (memTotal-memFree)/static_cast<float>(memTotal);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  long int systemUpTime=0;
  std::string line, systemUpTimeS;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename);
  /* read of /proc/uptime */
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> systemUpTimeS;
    systemUpTime = atol(systemUpTimeS.c_str());
  }
  /* return final value in seconds */
  return systemUpTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  return sysconf(_SC_CLK_TCK);
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function TODO
long LinuxParser::ActiveJiffies(int pid) {
  std::string aux{};
  std::size_t i;
  long int activeJiffiesVal{};
  std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kStatFilename);
  if (stream.is_open()) {
    for (i = 0; i < 13; ++i) {
      stream >> aux;
    }
    /* read data, sum #14 utime, #15 stime, #16 cutime, #17 cstime */
    for (i = 0; i < 4; ++i) {
      stream >> aux;
      activeJiffiesVal+=std::atol(aux.c_str());
    }
  }
  /* return final value after calculations */
  return activeJiffiesVal;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  long activeJiffies{};
  std::vector<long>cpuJiffiesUtilization = LinuxParser::CpuUtilization();
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
long LinuxParser::IdleJiffies() {
  std::vector<long>cpuJiffies = LinuxParser::CpuUtilization();
  return cpuJiffies.at(CPUStates::kIdle_)+cpuJiffies.at(kIOwait_)+cpuJiffies.at(kSteal_);
}

// TODO: Read and return CPU utilization
vector<long int> LinuxParser::CpuUtilization() {
  std::vector<long int>cpu{};
  std::string test, line;
  std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
  std::size_t i;
  long int jiffiesCpu;
  /* read of /proc/pid/stat */
  if (stream.is_open()) {
    stream>>test;
    if (test != "cpu") {
      /* no valid entry detected, return without summing the rest of the values */
      return cpu;
    }
    /* store numeric data in vector */
    for (i = CPUStates::kUser_; i != CPUStates::kLast_; ++i) {
      stream>>jiffiesCpu;
      cpu.emplace_back(jiffiesCpu);
    }
  }
  /* return vector cpu filled */
  return cpu;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
  /* read of /proc/stat */
  return getNumberOfOccurences<int>(stream, "processes");
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
  /* read of /proc/stat */
  return getNumberOfOccurences<int>(stream, "procs_running");
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  std::string cmd{};
  std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kCmdlineFilename);
  /* read of /proc/pid/cmdline */
  if (stream.is_open()) {
    stream>>cmd;
  }
  /* final calculations, handling cases of to long commands */
  if (cmd.size() > 40) {
    cmd = cmd.substr(0,40)+"...";
  }
  return cmd;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Ram(int pid) {
  long int ramMB;
  std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kStatusFilename);
  /* read of /proc/pid/status */
  /* changed from VmSize to VmRSS to reflect the actual size of memory used instead of virtual memory */
  ramMB = getNumberOfOccurences<long int>(stream, "VmRSS:")/1024;
  return std::to_string(ramMB);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Uid(int pid) {
  std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kStatusFilename);
  /* read of /proc/pid/status */
  return getNumberOfOccurences<std::string>(stream, "Uid:");
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::User(int pid) {
  std::string user, field2, uidField, line, uid;
  uid = LinuxParser::Uid(pid);
  if (uid == "") {
    return "";
  }
  std::ifstream stream(LinuxParser::kPasswordPath);
  /* read of proc/pid/status */
  if (stream.is_open()) {
    while(std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> field2 >> uidField;
      if (uidField == uid) {
        return user;
      }
    }
  }
  /* if it reaches here then it was not found */
  return user;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  std::string aux{};
  std::size_t i;
  long int upTimeVal{};
  std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kStatFilename);
  if (stream.is_open()) {
    for (i = 0; i < 22; ++i) {
      stream >> aux;
    }
    upTimeVal = std::atol(aux.c_str())/sysconf(_SC_CLK_TCK);
  }
  /* return final value after calculations */
  return upTimeVal;
}
