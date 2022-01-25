#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <regex>

// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

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

int TotalProcesses() ;
int RunningProcesses();
std::string Command(int pid);

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

// TODO: Read and return the total number of processes
int TotalProcesses() {
  std::ifstream stream(kProcDirectory+kStatFilename);
  return getNumberOfOccurences<int>(stream, "processes");
}

// TODO: Read and return the number of running processes
int RunningProcesses() {
  std::ifstream stream(kProcDirectory+kStatFilename);
  return getNumberOfOccurences<int>(stream, "procs_running");
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string Command(int pid) {
  std::string cmd{};
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kCmdlineFilename);
  /* read of /proc/pid/stat */
  if (stream.is_open()) {
    stream>>cmd;
  }
  /* final calculations */
  return cmd;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
std::string Ram(int pid) {
  long int ramMB;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  /* read of /proc/pid/status */
  ramMB = getNumberOfOccurences<long int>(stream, "VmSize:")/1024;
  return std::to_string(ramMB);
}

std::string Uid(int pid) {
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  /* read of /proc/pid/status */
  return getNumberOfOccurences<std::string>(stream, "Uid:");
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string User(int pid) {
  std::string user, field2, uidField, line, uid = Uid(pid);
  if (uid == "") {
    return "";
  }
  std::ifstream stream(kPasswordPath);
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
long UpTime(int pid) {
  std::string aux{};
  std::size_t i;
  long int upTimeVal{};
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);
  if (stream.is_open()) {
    for (i = 0; i < 22; ++i) {
      stream >> aux;
    }
    upTimeVal = atol(aux.c_str())/sysconf(_SC_CLK_TCK);
  }
  /* return final value after calculations */
  return upTimeVal;
}

// BONUS: Update this to use std::filesystem
std::vector<int> Pids() {
  std::vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      std::string filename(file->d_name);
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
float MemoryUtilization() {
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  long int memTotal, memFree;
  memTotal = getNumberOfOccurences<long int>(stream, "MemTotal:");
  memFree = getNumberOfOccurences<long int>(stream, "MemFree:");
  return (memTotal-memFree)/static_cast<float>(memTotal);
}

int main () {
  std::cout<<"Total processes: "<<TotalProcesses()<<"."<<std::endl;
  std::cout<<"Running processes: "<<RunningProcesses()<<"."<<std::endl;
  std::cout<<"Command for process pid=1: "<<Command(1)<<"."<<std::endl;
  std::cout<<"Ram (MB) for pid=1: "<<Ram(1)<<"."<<std::endl;
  std::cout<<"Uid for pid=1: "<<Uid(1)<<"."<<std::endl;
  std::cout<<"User for pid=1: "<<User(1)<<"."<<std::endl;
  std::cout<<"UpTime (s) for pid=1: "<<UpTime(1)<<"."<<std::endl;
  /* test pids */
  std::vector<int> pids = Pids();
  /* print pids */
  std::cout<<"\nPids: ";
  for (std::size_t i=0; i < pids.size(); ++i) {
    std::cout<<pids.at(i)<<" ";
  }
  std::cout<<"\n"<<std::endl;
  /* Memory utilization calculations */
  std::cout<<"Memory Utilization (%) = "<<MemoryUtilization()<<std::endl;
  return 0;
}
