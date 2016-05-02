#include "memoryManager.h"

MemoryManager::MemoryManager(int blockSize,string name){
   programName = name;
   memBlock = new int[blockSize];
   toggleBlock = new int[blockSize];
   for(int i = 0; i < blockSize; i++){ memBlock[i] = 0; toggleBlock[i] = 0; }
   totalBlocks = blockSize;
   totalMem = blockSize;
   totalCycles = 0;
   currCycles = 0;
   processesLoaded = 0;
}

MemoryManager::~MemoryManager(){
   waitQueue.clear();
   runningQueue.clear();
   delete [] this->memBlock;
   delete [] this->toggleBlock;
   //free(memBlock);
   //free(toggleBlock);
}

DataStore MemoryManager::startMemoryManager(vector<Process> set){
   timespec begin;
   timespec end;
   clock_gettime(CLOCK_REALTIME, &begin);

   runMemoryManager(set);

   clock_gettime(CLOCK_REALTIME, &end);
   
   DataStore d;
   d.totalCycles = totalCycles;
   d.runtime = end.tv_nsec - begin.tv_nsec;
   d.progName = programName;
   return d;

   /*
   cout << programName << " runtime was : " << totalCycles << " cycles" << endl;
   cout << "Time for " << programName << " took : " << end.tv_nsec - begin.tv_nsec << " nano seconds" << endl << endl;
   */
}

void MemoryManager::runMemoryManager(vector<Process> set){
   int setCounter = 0;
   while(setCounter < set.size() || waitQueue.size() > 0){
       map<int,LoadedProcesses>::iterator expiredProcess = findExpiredProcess();
       if(expiredProcess != runningQueue.end()){
          LoadedProcesses p = expiredProcess->second;
          runningQueue.erase(expiredProcess);
          my_free(p);
       }

       //Add new process
       if(setCounter >= set.size() || waitQueue.size() > 0){
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
   //cout << "Process Loading with currCycles = " << currCycles << endl;
   for(int i = 0; i < l.p.mem; i++){
      memBlock[l.startIndex+i] = l.p.pid;
   }
   totalMem -= l.p.mem;
   runningQueue.insert(pair<int,LoadedProcesses>(l.p.pid,l));
   totalCycles += currCycles + l.p.cycles; //updateTotalCycleCount
   return true;
}

void MemoryManager::my_free(LoadedProcesses p){
   for(int i = 0; i < p.p.mem; i++){
      memBlock[i+p.startIndex] = 0;
   }
   totalMem += p.p.mem;
   //Re shuffle memory
   //shiffleMemory();     
   //We could reshuffle the memory here to make our funciton a little more efficent
}

void MemoryManager::shuffleMemory(){
   int memBlockIndex = 0;
   for(int i = 0; i < totalBlocks; i++){
      if(memBlockIndex < totalBlocks){
         int currId = -1;
         while(memBlockIndex < totalBlocks && memBlock[memBlockIndex] == 0) memBlockIndex++;
         if(memBlockIndex < totalBlocks) currId = memBlock[memBlockIndex];
         while(memBlockIndex < totalBlocks && memBlock[memBlockIndex] != 0){
            
         }
      }
   } 
}

int MemoryManager::findEmptySlot(int size){
   int startIndex = -1;
   int blockCount = 0;
   if(totalMem >= size){
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
   }
   if(blockCount == size){
      return startIndex;
   } else {
      return -1;
   }
}

map<int,LoadedProcesses>::iterator MemoryManager::findExpiredProcess(){
   if(runningQueue.size() > 0){
      for(map<int,LoadedProcesses>::iterator i = runningQueue.begin(); i != runningQueue.end(); i++){
         if(i->second.removeCycleTime <= currCycles)
            return i; 
      }
   }
   return runningQueue.find(-1);
}
