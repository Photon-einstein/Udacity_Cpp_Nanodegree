#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
   /* constructor */
   Processor();
   /* other methods */
   float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
  private:
  float utilization_{};
  long prevIdle_{};
  long prevNonIdle_{};
  long prevTotal_{};
};

#endif
