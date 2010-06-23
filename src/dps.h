#ifndef DPS_H
#define DPS_H


#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fstream> 
#include "dps_types.h"



namespace dps
{
  class DPS
  {
    public: 
      char prevChar;
      char currChar;
      bool receivedFirstTimeStamp;
      bool receivedSecondTimeStamp;
      std::string readBuffer;
      std::ofstream the_file_stream;
      
      int openComPort(char *name);
      char getCharFromPort();
      std::string getOneFullLineFromString(std::string &s, int timeout_msecs);
      bool getPressureFromString(std::string& s, PressureReading &pr);
      std::string getLineIdentifier(std::string line);
      void printPressure(PressureReading pr);
      bool closeComPort();
      void flushPort(int timeout_msecs);

      int comPort;

     


    private:
  };

} // end namespace DummyProject

#endif