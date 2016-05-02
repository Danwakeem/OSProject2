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

void CSVHeader(){
   cout << ",Cycles,Nanoseconds" << endl;
}

void printAsCSV(vector<DataStore> data){
   for(vector<DataStore>::iterator i = data.begin(); i != data.end(); i++){
      cout << i->progName << "," << i->totalCycles << "," << i->runtime << endl; 
   }
   cout << ",,," << endl;
}

int main(){
   CSVHeader();
   for(int i = 0; i < 5; i++){
      vector<DataStore> CSVData;
      vector<Process> set;
      createProcessSet(&set);
      CSVData.push_back(startPart1Processes(set));

      MemoryManager *p2 = new MemoryManager(BLOCKSIZE,"Part 2");
      CSVData.push_back(p2->startMemoryManager(set));
      delete p2;

      int totalMem = getTotalMem(set);
      int fiftyPercent = totalMemoryPercent(0.5,totalMem);
      MemoryManager *p3a = new MemoryManager(fiftyPercent,"Part 3 a");
      CSVData.push_back(p3a->startMemoryManager(set));
      delete p3a;

      int tenPercent = totalMemoryPercent(0.1,totalMem);
      MemoryManager *p3b = new MemoryManager(tenPercent,"Part 3 b");
      CSVData.push_back(p3b->startMemoryManager(set));
      delete p3b;   

      printAsCSV(CSVData); 
   }

   return 0;
}


