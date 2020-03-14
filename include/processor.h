#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  double Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 long prevIdle_;
 long prevIoWait_ ;
 long prevUser_ ;
 long prevNice_ ;
 long prevSystem_;
 long prevIrq_ ;
 long prevSoftIrq_ ;
 long prevSteal_ ;

 void assignPreviousValues(double idle, double iowait, double user, double nice, double system, double irq, double softirq, double steal);

};

#endif