#ifndef MEMMAN_H
#define MEMMAN_H
#include "defines.h"

class MemoryManager {
   private:
      int *memBlock;
      int *toggleBlock;
      int totalBlocks;
      int totalMem;
      string programName;
      unsigned long long totalCycles;
      unsigned long long currCycles;
      int processesLoaded;
      vector<Process> waitQueue;
      map<int,LoadedProcesses> runningQueue; //Key is the pid
   public:
      MemoryManager(int blockSize,string name);
      ~MemoryManager();
      void runMemoryManager(vector<Process> set);
      DataStore startMemoryManager(vector<Process> set);
      LoadedProcesses createLoadedProcess(Process p, int startIndex);
      bool my_malloc(LoadedProcesses p);
      void my_free(LoadedProcesses p);
      int findEmptySlot(int size);
      map<int,LoadedProcesses>::iterator findExpiredProcess();
};

#endif
