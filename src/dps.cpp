#include "dps.h"
#include "dps_types.h"
#include <termios.h>

namespace dps
{

  int DPS::openComPort(char *name)
  {
    
    char sys_stty_cmd[100];
    
    sprintf(sys_stty_cmd,"stty -F %s 4800 cs8", name);
    
    system(sys_stty_cmd);

    comPort = open(name, O_RDWR);


    return comPort;
  }
  
  char DPS::getCharFromPort()
  {
    char c;
    read(comPort, &c, 1);
    return c;
  }
  
  void DPS::flushPort(int timeout_msecs)
{
  
  tcflush(comPort, TCIOFLUSH);
  
}
  
  std::string DPS::getOneFullLineFromString(std::string &s, int timeout_msecs)
  {
    char response[2000]; /* receive buffer */
    char c = 0;
    int readCharCount =  0;
    int writeCharCount = 0;
   
    c = s.at(readCharCount);
    s.erase(readCharCount,1);
    
    while(c==13 || c==10)
    {
      c = s.at(readCharCount);
      s.erase(readCharCount,1);
    }
    
    while(c!=13 && c!=10 && readCharCount < 1999 && readCharCount < s.size())
    {
    if(readCharCount == 2000)
      std::cout << "count = 2000" << std::endl;
        
    c = s.at(readCharCount);
    s.erase(readCharCount,1);
    response[writeCharCount] = c;
    writeCharCount++;
    }
    
    response[writeCharCount] = 0;
    return response;
  }
  
  
  bool DPS::getPressureFromString(std::string &s, PressureReading &pr)
  {
    std::string::size_type start, end;

    //std::cerr << "now getting a line..." << std::endl;
    std::string currentLine = getOneFullLineFromString(s,0);
    //std::cerr << "done\n";
    
    //std::cerr << "curr Line before while: " << currentLine << std::endl;
    
    while(getLineIdentifier(currentLine).compare("YXDPT") != 0)
    {
      //std::cerr << "line ID is " << getLineIdentifier(currentLine) << std::endl;
      currentLine = getOneFullLineFromString(s,0);
      //std::cerr << "got this line: " << currentLine << std::endl;
      //std::cerr << "from this string:\n" << s << std::endl;
    }
      //std::cerr << "curr Line after while: " << currentLine << std::endl;

    
    timeval tim;
    gettimeofday(&tim, NULL);
    
    
    
    std::cout << "secs: " << tim.tv_sec << " , usecs: " << tim.tv_usec << std::endl;
    
    start = currentLine.find_first_of(",");
    end = currentLine.find_first_of(",",start+1);
    
  // std::cout << "ts =" << currentLine.substr(start+1,end-start-1) << ".\n";
  // sscanf(currentLine.substr(start+1,end-start-1).c_str(), "%Lu", &speeds.timestamp);
    
    pr.pressure = atof(currentLine.substr(start+1,end-start-1).c_str());
    pr.timestamp = tim.tv_sec * 1000 + tim.tv_usec / 1000;
    
    printPressure(pr);
    
    
    return true;
  }

  void DPS::printPressure(PressureReading pr)
  {
      std::cout << "\n===== begin pressure output =====\n";
      std::cout << "pressure = " << pr.pressure << "\n";
      std::cout << "===== end pressure output =======\n";
  }



  std::string DPS::getLineIdentifier(std::string line)
  {
    std::string identifier;
    identifier = line.substr(0,5);
    return identifier;
  }


  bool DPS::closeComPort()
  {
    close(comPort);
  }

}
