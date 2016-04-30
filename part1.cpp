#include "part1.h"

void startPart1Processes(vector<Process> set){
   timespec begin;
   timespec end;
   clock_gettime(CLOCK_REALTIME, &begin);

   int runTimeInCycles = runProcesses(set);

   clock_gettime(CLOCK_REALTIME, &end);
   cout << "Part 1 runtime was : " << runTimeInCycles << " cycles" << endl;
   cout << "Time for Part 1 took : " << end.tv_nsec - begin.tv_nsec << " nano seconds" << endl << endl;
}

int runProcesses(vector<Process> set){
   int cycleOffSet = 0;
   int totalCycleCount = 0;

   for(int i = 0; i < set.size(); i++){
      Process p = set[i];
      totalCycleCount += p.cycles + cycleOffSet;       

      //Allocating then deallocating memeory
      //I used a char because it is one byte insted of 32 or more like int or any other data type
      char *memAlloc = (char *)malloc(sizeof(char) * p.mem);
      free(memAlloc);

      cycleOffSet += SPAWNPROCESS;
   }

   return totalCycleCount;
}

