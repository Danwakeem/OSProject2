#include "memoryManager.h"

//Initalize with block size
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

//Delete resources
MemoryManager::~MemoryManager(){
   waitQueue.clear();
   runningQueue.clear();
   delete [] this->memBlock;
   delete [] this->toggleBlock;
   //free(memBlock);
   //free(toggleBlock);
}

//Measure the runtime withe set
DataStore MemoryManager::startMemoryManager(vector<Process> set){
   timespec begin;
   timespec end;
   clock_gettime(CLOCK_REALTIME, &begin); //Start clock time

   runMemoryManager(set); //Run on set

   clock_gettime(CLOCK_REALTIME, &end); //End clock time
   
   //Pass back CSV friendly data
   DataStore d;
   d.totalCycles = totalCycles;
   d.runtime = end.tv_nsec - begin.tv_nsec;
   d.progName = programName;
   return d;

}

//Run the processes set
void MemoryManager::runMemoryManager(vector<Process> set){
   int setCounter = 0; //Index for the set
   //Loop until no more processes are avalible
   while(setCounter < set.size() || waitQueue.size() > 0){
       //Find expired processes that should be removed
       map<int,LoadedProcesses>::iterator expiredProcess = findExpiredProcess();

       //If expired process was found remove it
       if(expiredProcess != runningQueue.end()){
          LoadedProcesses p = expiredProcess->second;
          runningQueue.erase(expiredProcess);
          my_free(p);
       }

       //Add new process from wait queue
       if(setCounter >= set.size() || waitQueue.size() > 0){
          Process p = waitQueue[0];
          int index = findEmptySlot(int(p.mem));
          if(index != -1){
             LoadedProcesses l = createLoadedProcess(p,index);
             my_malloc(l);
             waitQueue.erase(waitQueue.begin()); //Remove from waitqueue
          }
       } else {
          //Add new process from the original set of processes
          Process p = set[setCounter++];
          int index = findEmptySlot(int(p.mem));
          //If empty slot load it else put in wait queue
          if(index != -1){
             LoadedProcesses l = createLoadedProcess(p,index);
             my_malloc(l);
          } else {
             waitQueue.push_back(p);
          }
       }       
       currCycles += SPAWNPROCESS; //Increment the current cycle by 50
   }
}

//Convience function
LoadedProcesses MemoryManager::createLoadedProcess(Process p, int startIndex){
   LoadedProcesses l;
   l.p = p;
   l.startIndex = startIndex;
   l.removeCycleTime = currCycles + p.cycles;
   return l;
}

//Load a process into memory block
bool MemoryManager::my_malloc(LoadedProcesses l){
   //Load blocks
   for(int i = 0; i < l.p.mem; i++){
      memBlock[l.startIndex+i] = l.p.pid;
   }
   totalMem -= l.p.mem;
   runningQueue.insert(pair<int,LoadedProcesses>(l.p.pid,l));
   totalCycles += currCycles + l.p.cycles; //updateTotalCycleCount
   return true;
}

//Remove from memory
void MemoryManager::my_free(LoadedProcesses p){
   for(int i = 0; i < p.p.mem; i++){
      memBlock[i+p.startIndex] = 0;
   }
   totalMem += p.p.mem;
   //We could reshuffle the memory here to make our funciton a little more efficent
}

//Find an empty slot in the block of memory
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

   //Double check that a block size large enough was found
   if(blockCount == size){
      return startIndex;
   } else {
      return -1;
   }
}

//Find processes in the map that are expired
map<int,LoadedProcesses>::iterator MemoryManager::findExpiredProcess(){
   if(runningQueue.size() > 0){
      for(map<int,LoadedProcesses>::iterator i = runningQueue.begin(); i != runningQueue.end(); i++){
         if(i->second.removeCycleTime <= currCycles)
            return i; 
      }
   }
   return runningQueue.find(-1);
}
