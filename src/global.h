#ifndef GLOBAL_H
#define GLOBAL_H

#define DEPTH 19
#define LOGGING		//to log the progress of the program.

#ifdef LOGGING
#include <fstream>
#include <string>
extern std::string logFileName;
extern std::ofstream logFileObj;
#endif

//#define DEBUG
#ifdef DEBUG
extern int debugLevel;
#endif

#endif
