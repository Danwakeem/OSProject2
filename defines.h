#ifndef DEFINES_H
#define DEFINES_H

#include<iostream>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<vector>
#include<iomanip>
#include <sys/types.h>
//#include<sys/time.h>
#include <signal.h>
#include <algorithm>
#include <map>
#include<math.h>

using namespace std;

#define NUMPROCESSES 64
#define SPAWNPROCESS 50
#define MEANCYCLES 6000
#define MEANMEM 20
#define BLOCKSIZE 20000


//Structure for my processe information
typedef struct Process {
   int pid;
   float cycles;
   float mem;
}Process;

//Structure for my random number I will be generating
typedef struct RandomNumbers {
   int cycles;
   int mem;
}RandomNumbers;

typedef struct loadedProcesses {
   int removeCycleTime;
   int startIndex;
   Process p;
}LoadedProcesses;

#endif
