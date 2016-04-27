#ifndef PART2_H
#define PART2_H
#include "defines.h"

class Part2 {
   private:
      int totalMem;
      int currOffSet;
      int totalCycleTime;
      vector<LoadedProcesses> lp;
   public: 
      Part2();
      void startPart2Processes(vector<Process>set);
      void runProcesses(vector<Process>set);
      int findExpiredProcess();
      bool my_malloc(Process p);
      void my_free(int index);
};

#endif
