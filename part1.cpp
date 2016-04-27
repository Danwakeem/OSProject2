#include "part1.h"

/*
I am not sure if we are supposed to be reading real time but if we are then we can
just use this function instead of the other. Also we will have to compile to project differently
with this

void startProcesses(vector<Process> set){
   timespec begin;
   timespec end;

   clock_gettime(CLOCK_REALTIME, &begin);

   runProcesses(set);

   clock_gettime(CLOCK_REALTIME, &end);

   long runtime = end.tv_nsec - begin.tv_nsec;
   cout << "Time for Part 1 took : " << runtime << endl;
}
*/

void startPart1Processes(vector<Process> set){
   int runTimeInCycles = runProcesses(set);
   cout << "Part 1 runtime was : " << runTimeInCycles << " cycles" << endl << endl;
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

