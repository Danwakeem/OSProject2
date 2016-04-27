#include "defines.h"
#include "processGenerator.h"
#include "part1.h"
#include "part2.h"

int main(){
   vector<Process> set;
   createProcessSet(&set);
   startPart1Processes(set);
   Part2 p2;
   p2.startPart2Processes(set);

   return 0;
}
