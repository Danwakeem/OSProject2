#include "Part2.h"

Part2::Part2(){
   totalMem = BLOCKSIZE;
   currOffSet = 0;
   totalCycleTime = 0;
}

void Part2::startPart2Processes(vector<Process> set){
   this->runProcesses(set);
}

void Part2::runProcesses(vector<Process> set){
   this->memBlock = (int*) malloc(sizeof(int) * BLOCKSIZE);
   for(int i = 0; i < set.size(); i++){
      int expiredIndex = this->findExpiredProcess();
      if(expiredIndex != -1){
         Process p = this->lp[expiredIndex].p;
         this->lp.erase(this->lp.begin() + expiredIndex);
         this->my_free(p);
      } 
   }
}

bool Part2::my_malloc(Process p){
   int index = findEmptySlot(p.memSize);
   if(index != -1){
      //Insert
      for(int i = 0; i < p.size; i++){
         this->memBlock[index+i] = 1;
      }
      loadedProcess l;
      l.p = p;
      totalMem -= p.mem;
      this->lp.push_back(l);
      return true;
   }
   return false;
}

void Part2::my_free(Process p){
   for(int i = 0; i < p.memSize(); i++){
      this->memBlock[i+p.startIndex] = 0;
   }
}

int Part2::findEmptySlot(int size){
   int startIndex = -1;
   int blockCount = 0;
   for(int i = 0; i < BLOCKSIZE; i++){
      if(this->memBlock[i] == 0){
         if(blockCount == 0) startIndex = i;
         blockCount++;
      } else {
         blockCount = 0;
         startIndex = 0;
      }
      if(blockCount == size-1){
         return startIndex;
      } 
   }
   return -1;
}

int Part2::findExpiredProcess(){
   int removeIndex = -1;
   if(this->lp.size() > 0){
      for(int i = 0; i < this->lp.size(); i++){
         if(this->lp[i].removeCycleTime <= currOffSet){
            removeIndex = i;
         }
      }
   }
   return removeIndex; 
}
