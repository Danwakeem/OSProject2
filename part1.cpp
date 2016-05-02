#include "part1.h"

DataStore startPart1Processes(vector<Process> set){
   timespec begin;
   timespec end;
   clock_gettime(CLOCK_REALTIME, &begin); //Start clock

   int runTimeInCycles = runProcesses(set); //Run on set

   clock_gettime(CLOCK_REALTIME, &end); //End clock

   //Pass back CSV friendly info
   DataStore d;
   d.totalCycles = runTimeInCycles;
   d.runtime = end.tv_nsec - begin.tv_nsec;
   d.progName = "Part 1";
   return d;

}

//Run on set
int runProcesses(vector<Process> set){
   int cycleOffSet = 0;
   int totalCycleCount = 0;
   int processCount = 0;

   //Loop through all processes
   for(int i = 0; i < set.size(); i++){
      Process p = set[i];
      totalCycleCount += p.cycles + cycleOffSet;       

      //Allocating then deallocating memeory
      //I used a char because it is one byte insted of 32 or more like int or other data types
      char *memAlloc = (char *)malloc(sizeof(char) * p.mem);
      free(memAlloc); // free mem

      cycleOffSet += SPAWNPROCESS; //incrment cycle off set by 50
   }

   return totalCycleCount; //return cycles performed
}

