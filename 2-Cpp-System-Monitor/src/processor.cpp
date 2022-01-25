#include "processor.h"
#include "linux_parser.h"

Processor::Processor() {
  this->utilization_ = Processor::Utilization();
  this->prevIdle_ = LinuxParser::IdleJiffies();
  this->prevNonIdle_ = LinuxParser::ActiveJiffies();
  this->prevTotal_ = this->prevIdle_+this->prevNonIdle_;
  return;
}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  long int idle{}, nonIdle{}, total{}, totalDelta{}, idleDelta{};
  /* pos-calculations */
  /* idle calculations */
  idle = LinuxParser::IdleJiffies();
  /* active calculations */
  nonIdle = LinuxParser::ActiveJiffies();
  /* total time calculations */
  total = idle+nonIdle;
  /* delta calculation */
  totalDelta = total - this->prevTotal_;
  idleDelta = idle - this->prevIdle_;
  /* final calculation */
  if (totalDelta == 0) {
    this->utilization_ = 0;
  } else {
    this->utilization_ = (totalDelta-idleDelta)/static_cast<float>(totalDelta);
  }
  return this->utilization_;
}
