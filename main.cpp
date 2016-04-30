#include "defines.h"
#include "processGenerator.h"
#include "part1.h"
#include "memoryManager.h"

int main(){
   vector<Process> set;
   createProcessSet(&set);
   startPart1Processes(set);
   MemoryManager p2(BLOCKSIZE);
   p2.startMemoryManager(set);

   return 0;
}
