#include "defines.h"
#include "processGenerator.h"
#include "part1.h"

int main(){
   vector<Process> set;
   createProcessSet(&set);

   startProcesses(set);

   return 0;
}
