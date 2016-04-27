#include "part2.h"

Part2::Part2(){
   this->totalMem = BLOCKSIZE;
   this->currOffSet = 0;
   this->totalCycleTime = 0;
}

void Part2::startPart2Processes(vector<Process> set) {
   this->runProcesses(set); 
   cout << "Total cycle time for part 2 was : " << this->totalCycleTime << " cycle" << endl;

}

void Part2::runProcesses(vector<Process> set){
   int *memBlock = (int*)malloc(sizeof(int)*BLOCKSIZE);
   for(int i = 0; i < set.size(); i++){
      int expiredIndex = this->findExpiredProcess();
      if(expiredIndex != -1) this->my_free(expiredIndex);
      Process p = set[i];
      if(this->my_malloc(p))
         this->totalCycleTime += p.cycles + currOffSet;
      currOffSet += SPAWNPROCESS;
   }
}

int Part2::findExpiredProcess(){
   int removeIndex = -1;
   if(this->lp.size() > 0){
      for(int i = 0; i < lp.size(); i++){
         if(this->lp[i].removeCycleTime <= currOffSet){
            removeIndex = i;
         }
      }
      return removeIndex;
   } else {
      return removeIndex;
   }
}

bool Part2::my_malloc(Process p){
   if(this->totalMem != 0 && this->totalMem >= p.mem){
      LoadedProcesses l;
      l.removeCycleTime = p.cycles + currOffSet;
      l.p = p;
      totalMem -= p.mem;
      this->lp.push_back(l);
      return true;
   } else {
      return false;
   }
}

void Part2::my_free(int index){
   totalMem += this->lp[index].p.mem;
   this->lp.erase(this->lp.begin() + index);
}
