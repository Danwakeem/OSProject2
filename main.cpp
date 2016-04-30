#include "defines.h"
#include "processGenerator.h"
#include "part1.h"
#include "memoryManager.h"

int getTotalMem(vector<Process> set){
   int totalMem = 0;
   for(vector<Process>::iterator i = set.begin(); i != set.end(); i++) 
      totalMem += i->mem;
   return totalMem;
}

int totalMemoryPercent(float percent,int totalMem){
   return totalMem * percent;
}

int main(){
   vector<Process> set;
   createProcessSet(&set);
   startPart1Processes(set);

   MemoryManager *p2 = new MemoryManager(BLOCKSIZE,"Part 2");
   p2->startMemoryManager(set);
   delete p2;

   int totalMem = getTotalMem(set);
   int fiftyPercent = totalMemoryPercent(0.5,totalMem);
   MemoryManager *p3a = new MemoryManager(fiftyPercent,"Part 3 a");
   p3a->startMemoryManager(set);
   delete p3a;

   int tenPercent = totalMemoryPercent(0.1,totalMem);
   MemoryManager *p3b = new MemoryManager(tenPercent,"Part 3 b");
   p3b->startMemoryManager(set);
   delete p3b;   


   return 0;
}


