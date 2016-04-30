#include "memoryManager.h"

MemoryManager::MemoryManager(int blockSize){
   memBlock = (int*)malloc(sizeof(int)*blockSize);
   for(int i = 0; i < blockSize; i++) memBlock[i] = 0;
   totalBlocks = blockSize;
   totalMem = blockSize;
   totalCycles = 0;
   currCycles = 0;
   processesLoaded = 0;
}

MemoryManager::~MemoryManager(){
   free(memBlock);
}

void MemoryManager::startMemoryManager(vector<Process> set){
   runMemoryManager(set);
   cout << "Total cycles were : " << totalCycles << " cycles" << endl;
}

void MemoryManager::runMemoryManager(vector<Process> set){
   int setCounter = 0;
   while(setCounter < set.size() || waitQueue.size() > 0){
       //int expiredIndex = findExpiredProcess();
       map<int,LoadedProcesses>::iterator expiredProcess = findExpiredProcess();
       if(expiredProcess != runningQueue.end()){
          LoadedProcesses p = expiredProcess->second;
          //LoadedProcesses p = runningQueue[expiredIndex].p;
          runningQueue.erase(expiredProcess);
          my_free(p);
       }
       
       //Add new process
       if(setCounter >= set.size()){
          Process p = waitQueue[0];
          int index = findEmptySlot(int(p.mem));
          if(index != -1){
             LoadedProcesses l = createLoadedProcess(p,index);
             my_malloc(l);
             waitQueue.erase(waitQueue.begin()); //Remove from waitqueue
          }
       } else {
          Process p = set[setCounter++];
          int index = findEmptySlot(int(p.mem));
          if(index != -1){
             LoadedProcesses l = createLoadedProcess(p,index);
             my_malloc(l);
          } else {
             waitQueue.push_back(p);
          }
       }       
       currCycles += SPAWNPROCESS;
   }
}

LoadedProcesses MemoryManager::createLoadedProcess(Process p, int startIndex){
   LoadedProcesses l;
   l.p = p;
   l.startIndex = startIndex;
   l.removeCycleTime = currCycles + p.cycles;
   return l;
}

bool MemoryManager::my_malloc(LoadedProcesses l){
   cout << "Process Loading with currCycles = " << currCycles << endl;
   for(int i = 0; i < l.p.mem; i++){
      memBlock[l.startIndex+i] = l.p.pid;
   }
   totalMem -= l.p.mem;
   runningQueue.insert(pair<int,LoadedProcesses>(l.p.pid,l));
   //runningQueue.push_back(l);
   totalCycles += currCycles + l.p.cycles; //updateTotalCycleCount
   return true;
}

void MemoryManager::my_free(LoadedProcesses p){
   for(int i = 0; i < p.p.mem; i++){
      memBlock[i+p.startIndex] = 0;
   }
   //Re shuffle memory
}

int MemoryManager::findEmptySlot(int size){
   int startIndex = -1;
   int blockCount = 0;
   for(int i = 0; i < totalBlocks; i++){
      if(memBlock[i] == 0){
         if(blockCount == 0) 
            startIndex = i;
         blockCount++;
      } else {
         blockCount = 0;
         startIndex = -1;
      }
      if(blockCount == size){
         return startIndex;
      }
   }
   return startIndex;
}

map<int,LoadedProcesses>::iterator MemoryManager::findExpiredProcess(){
   if(runningQueue.size() > 0){
      for(map<int,LoadedProcesses>::iterator i = runningQueue.begin(); i != runningQueue.end(); i++){
         if(i->second.removeCycleTime <= currCycles)
            return i; 
      }
      /*
      for(int i = 0; i < runningQueue.size(); i++){
         if(runningQueue[i].removeCycleTime <= curroffSet)
            return i;
      }
      */
   }
   return runningQueue.find(-1);
}
