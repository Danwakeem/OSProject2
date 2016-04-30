#ifndef PART2_H
#define PART2_H
#include "defines.h"

class Part2 {
   private:
      int *memBlock; //0 means empty 1 means full
      int totalMem;
      int currOffSet;
      int totalCycleTime;
      vector<LoadedProcesses> lp;
   public: 
      Part2();
      ~Part2();
      void startPart2Processes(vector<Process>set);
      void runProcesses(vector<Process>set);
      int findExpiredProcess();
      bool my_malloc(Process p);
      void my_free(int index);
};

#endif
