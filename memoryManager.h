#ifndef MEMMAN_H
#define MEMMAN_H
#include "defines.h"

class MemoryManager {
   private:
      int *memBlock;
      int *toggleBlock;
      int totalBlocks;
      int totalMem;
      unsigned long long totalCycles;
      unsigned long long currCycles;
      int processesLoaded;
      vector<Process> waitQueue;
      map<int,LoadedProcesses> runningQueue; //Key is the pid
   public:
      MemoryManager(int blockSize);
      ~MemoryManager();
      void runMemoryManager(vector<Process> set);
      void startMemoryManager(vector<Process> set);
      LoadedProcesses createLoadedProcess(Process p, int startIndex);
      bool my_malloc(LoadedProcesses p);
      void my_free(LoadedProcesses p);
      void shuffleMemory();
      int findEmptySlot(int size);
      map<int,LoadedProcesses>::iterator findExpiredProcess();
};

#endif